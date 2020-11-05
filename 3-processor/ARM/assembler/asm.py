#!/usr/bin/python
import re
import sys
import struct

VALID_MNEMONICS = [
    'ldr{}', 'ldr{}b',
    'str{}', 'str{}b',
]

CONDITIONS = {
    'eq': 0b0000, # Equal                   | Z set
    'ne': 0b0001, # Not equal               | Z clear
    'cs': 0b0010, # Unsigned higher, or same| C set
    'cc': 0b0011, # Unsigned lower          | C clear
    'mi': 0b0100, # Negative                | N set
    'pl': 0b0101, # Positive or zero        | N clear
    'vs': 0b0110, # Overflow                | V set
    'vc': 0b0111, # No overflow             | V clear
    'hi': 0b1000, # Unsigned higher         | C set, Z clear
    'ls': 0b1001, # Unsigned lower or same  | C clear, Z set
    'ge': 0b1010, # Greater or equal        | N == V
    'lt': 0b1011, # Less than               | N != V
    'gt': 0b1100, # Greater than            | Z clear, N == V
    'le': 0b1101, # Less than or equal      | Z set or N != V
    'al': 0b1110, # Always (unconditional)  | -
    'nv': 0b1111, # Never                   | leads to an unpredictable state
    '':   0b11111, # use only for parsing the instruction, not used in CPU
}

REGISTERS = {
    'r0':  0b0000, 'r1':  0b0001, 'r2':  0b0010, 'r3':  0b0011,
    'r4':  0b0100, 'r5':  0b0101, 'r6':  0b0110, 'r7':  0b0111,
    'r8':  0b1000, 'r9':  0b1001, 'r10': 0b1010, 'r11': 0b1011,
    'r12': 0b1100, 'r13': 0b1101, 'r14': 0b1110, 'r15': 0b1111,
}


lc = 0 # address of current instruction
symbol_table = {} # key: symbol, value: address

# source line format: {symbol} {instruction | directive | pseudo-instruction} {@ comment}
def parse_source_line(line):
    tokens = line.split('@')[0] # remove comment
    symbol, instruction = [i.strip(' :\n') for i in re.split('\s', tokens, 1)]
    return symbol, instruction

# builds symbol table and returns the instructions
def first_pass(source_lines):
    instructions = []

    for line in source_lines:
        if line.isspace(): continue

        symbol, instruction = parse_source_line(line)

        if symbol:
            global symbol_table, lc
            symbol_table[symbol] = lc

        if instruction:
            lc += 1
            instructions.append(instruction)

    return instructions

def parse_instruction(instruction):
    mnemonic, args = instruction.split(' ', 1)

    itype = ''
    cond = CONDITIONS['al']
    dtype = ''

    for valid_mnemonic in VALID_MNEMONICS:
        for condition in CONDITIONS:
            formatted_mnemonic = valid_mnemonic.format(condition)
            if mnemonic == formatted_mnemonic:
                ix = valid_mnemonic.index('{')
                itype = formatted_mnemonic[:ix]

                cond = condition

                ix = valid_mnemonic.index('}')
                dtype = formatted_mnemonic[ix+1:]

    if not itype:
        raise Exception('Invalid instruction: {}'.format(instruction))

    return itype, cond, dtype, args

# Load and Store word or unsigned byte instructions
# immediate:
#             |31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0|
#             |cond       | 0| 1| I| P| U| B| W| L|Rn         |Rd         |<a_mode2>                          |
# regular     |cond       | 0| 1| 0| 1| U| B| 0| L|Rn         |Rd         |offset_12                          |
# pre-indexed |cond       | 0| 1| 0| 1| U| B| 1| L|Rn         |Rd         |offset_12                          |
# post-indexed|cond       | 0| 1| 0| 0| U| B| 0| L|Rn         |Rd         |offset_12                          |
#
# register:
#             |31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0|
#             |cond       | 0| 1| I| P| U| B| W| L|Rn         |Rd         |<a_mode2>                          |
# regular     |cond       | 0| 1| 1| 1| U| B| 0| L|Rn         |Rd         | 0| 0| 0| 0| 0| 0| 0| 0|Rm         |
# pre-indexed |cond       | 0| 1| 1| 1| U| B| 1| L|Rn         |Rd         | 0| 0| 0| 0| 0| 0| 0| 0|Rm         |
# post-indexed|cond       | 0| 1| 1| 0| U| B| 0| L|Rn         |Rd         | 0| 0| 0| 0| 0| 0| 0| 0|Rm         |

# scaled register:
#             |31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0|
#             |cond       | 0| 1| I| P| U| B| W| L|Rn         |Rd         |<a_mode2>                          |
# regular     |cond       | 0| 1| 1| 1| U| B| 0| L|Rn         |Rd         |shift_imm     |shift| 0|Rm         |
# pre-indexed |cond       | 0| 1| 1| 1| U| B| 1| L|Rn         |Rd         |shift_imm     |shift| 0|Rm         |
# post-indexed|cond       | 0| 1| 1| 0| U| B| 0| L|Rn         |Rd         |shift_imm     |shift| 0|Rm         |
def encode_load_store(args, cond, L, B):
    encoding = 0

    encoding |= CONDITIONS[cond] << 28
    encoding |= 0b01 << 26
    encoding |= B << 22
    encoding |= L << 20

    Rd, src = [a.strip() for a in args.split(',', 1)]
    encoding |= REGISTERS[Rd] << 12

    # determine type
    Rn, addr_mode = None, None
    W, P = 0b00, 0b00
    if src[-1] == ']': # regular
        W = 0b00
        P = 0b01
        Rn, addr_mode = [a.strip() for a in src.strip('[]').split(',')]
    elif src[-1] == '!': # pre-indexed
        W = 0b01
        P = 0b01
        Rn, addr_mode = [a.strip() for a in src.strip('![]').split(',')]
    else: # post-indexed
        W = 0b00
        P = 0b00
        Rn, addr_mode = [a.strip('[] ') for a in src.split(',', 1)]

    if Rn is None or addr_mode is None:
        raise Exception('Invalid type for {}'.format(args))

    encoding |= REGISTERS[Rn] << 16
    encoding |= P << 24
    encoding |= W << 21

    # determine addressing mode
    addr_mode = [a.strip() for a in addr_mode.split(',')]
    I, U = 0b00, 0b00
    if len(addr_mode) == 1:
        offset_12 = 0b00
        token = addr_mode[0]

        if token[0] == '#': # immediate
            I = 0b00
            if token[1] == '+':
                U, offset_12 = 0b01, int(token[2:])
            elif token[1].isdigit():
                U, offset_12 = 0b01, int(token[1:])
            elif token[1] == '-':
                U, offset_12 = 0b00, int(token[1:])
            else:
                raise Exception('Invalid addressing mode in {}'.format(args))

            assert offset_12 < 1 << 12
            encoding |= offset_12 << 12
        elif token in REGISTERS: # register
            I = 0b01
            Rm = 0b00
            if token[0] == '+':
                U, Rm = 0b01, token[1:]
            elif token[0].isalpha():
                U, Rm = 0b01, token
            else:
                raise Exception('Invalid addressing mode in {}'.format(args))

            encoding |= REGISTERS[Rm] << 4
    elif len(addr_mode) >= 2: # scaled register
        I = 0b01
        if addr_mode[0][0] == '+' or addr_mode[0][0].isalpha():
            U = 0b01
        elif addr_mode[0][0] == '-':
            U = 0b00
        else:
            raise Exception('Invalid addressing mode in {}'.format(args))

        Rm, shift_offset = addr_mode[0].strip('+- '), addr_mode[1].strip('#')
        shift, shift_imm = 0b00, 0b00
        if shift_offset[:3] == 'LSL':
            shift, shift_imm = 0b00, int(shift_offset.split('#')[1].strip())
        elif shift_offset[:3] == 'LSR':
            shift, shift_imm = 0b01, int(shift_offset.split('#')[1].strip())
        elif shift_offset[:3] == 'ASR':
            shift, shift_imm = 0b10, int(shift_offset.split('#')[1].strip())
        elif shift_offset[:3] == 'ROR':
            shift, shift_imm = 0b11, int(shift_offset.split('#')[1].strip())
        elif shift_offset[:3] == 'RRX':
            shift, shift_imm = 0b11, 0b00
        else:
            raise Exception('Invalid addressing mode in {}'.format(args))

        encoding |= shift_imm << 12
        encoding |= shift << 7
        encoding |= REGISTERS[Rm] << 4
    else:
        raise Exception('Invalid addressing mode in {}'.format(args))

    encoding |= I << 25
    encoding |= U << 23

    return encoding

# encode instructions and write object file
def second_pass(instructions):
    encodings = []
    for instruction in instructions:
        itype, cond, dtype, args = parse_instruction(instruction)

        encoding = ''
        if itype == 'ldr':
            encoding = encode_load_store(args, cond, L = 0b01, B = 0b01 if dtype == 'b' else 0b00)
        elif itype == 'str':
            encoding = encode_load_store(args, cond, L = 0b00, B = 0b01 if dtype == 'b' else 0b00)
            pass

        if encoding: encodings.append(encoding)

    return encodings

if len(sys.argv) != 2:
    print('Error: no input file to assemble. Usage: ./asm.py <file>.s')
    exit(1)


with open(sys.argv[1], 'r') as fin:
    source_lines = fin.readlines()

    instructions = first_pass(source_lines)
    encodings = second_pass(instructions)

