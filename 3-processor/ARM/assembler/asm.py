#!/usr/bin/python
import re
import sys
import struct


VALID_MNEMONICS = [
    'ldr{}', 'ldr{}b',
    'str{}', 'str{}b',
    'b{}', 'bl{}',
    # moves
    'mov{}', 'mvn{}',
    'mov{}s', 'mvn{}s',
    # alus
    'add{}', 'sub{}', 'rsb{}', 'adc{}', 'sbc{}', 'rsc{}', 'and{}', 'bic{}', 'eor{}', 'orr{}',
    'add{}s', 'sub{}s', 'rsb{}s', 'adc{}s', 'sbc{}s', 'rsc{}s', 'and{}s', 'bic{}s', 'eor{}s', 'orr{}s',
    # compares
    'cmp{}', 'cmn{}', 'tst{}', 'teq{}',
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
    '':   0b1110, # use only for parsing the instruction, not in CPU
}

DATA_PROCESSING_OPCODE = {
    'and': 0b0000,
    'eor': 0b0001,
    'sub': 0b0010,
    'rsb': 0b0011,
    'add': 0b0100,
    'adc': 0b0101,
    'sbc': 0b0110,
    'rsc': 0b0111,
    'tst': 0b1000,
    'teq': 0b1001,
    'cmp': 0b1010,
    'cmn': 0b1011,
    'orr': 0b1100,
    'mov': 0b1101,
    'bic': 0b1110,
    'mvn': 0b1111,
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

                cond = CONDITIONS[condition]

                if cond != CONDITIONS['al']:
                    ix = valid_mnemonic.index('}')
                    dtype = formatted_mnemonic[ix+1:]
                else:
                    dtype = formatted_mnemonic[3:]

    if not itype:
        raise Exception('Invalid instruction: {}'.format(instruction))

    return itype, cond, dtype, args


def sign_extend(value, bits):
    sign_bit = 1 << (bits - 1)
    return (value & (sign_bit - 1)) - (value & sign_bit)


def encode_load_store(args, cond, L, B):
    encoding = 0

    encoding |= cond << 28
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
        tokens = [a.strip() for a in src.strip('[]').split(',', 1)]
        if len(tokens) == 1:
            Rn = tokens[0]
        elif len(tokens) == 2:
            Rn, addr_mode = tokens[0], tokens[1]
    elif src[-1] == '!': # pre-indexed
        W = 0b01
        P = 0b01
        tokens = [a.strip() for a in src.strip('![]').split(',', 1)]
        if len(tokens) == 1:
            Rn = tokens[0]
        elif len(tokens) == 2:
            Rn, addr_mode = tokens[0], tokens[1]
    else: # post-indexed
        W = 0b00
        P = 0b00
        Rn, addr_mode = [a.strip('[] ') for a in src.split(',', 1)]

    if Rn is None:
        raise Exception('Invalid type for {}'.format(args))

    encoding |= REGISTERS[Rn] << 16
    encoding |= P << 24
    encoding |= W << 21

    if addr_mode is None:
        U = 0b01
        encoding |= U << 23
        return encoding

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
                U, offset_12 = 0b00, int(token[2:])
            else:
                raise Exception('Invalid addressing mode in {}'.format(args))

            assert offset_12 < 1 << 12
            encoding |= offset_12
        else:
            I = 0b01
            Rm = 0b00
            if token[0] == '+':
                U, Rm = 0b01, token[1:]
            elif token[0] == '-':
                U, Rm = 0b00, token[1:]
            elif token[0].isalpha():
                U, Rm = 0b01, token
            else:
                raise Exception('Invalid addressing mode in {}'.format(args))
            encoding |= REGISTERS[Rm]
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

        encoding |= shift_imm << 7
        encoding |= shift << 5
        encoding |= REGISTERS[Rm]
    else:
        raise Exception('Invalid addressing mode in {}'.format(args))

    encoding |= I << 25
    encoding |= U << 23

    return encoding


def encode_branch(args, cond, L):
    encoding = 0

    encoding |= cond << 28
    encoding |= 0b01 << 27
    encoding |= 0b01 << 25
    encoding |= L << 24

    signed_imm = int(args[0].strip())
    assert signed_imm < 1 << 24

    # TODO might need to change this once you work out how to do the prefetch
    encoding |= sign_extend(signed_imm, 32) << 2

    return encoding

def encode_data_processing_shifter(shifter):
    encoding = 0
    shifter_operand = 0b00
    I = 0b00

    tokens = [i.strip() for i in shifter.split(',')]
    if len(tokens) == 1:
        if tokens[0][0] == '#': # immediate
            I = 0b01
            shifter_operand |= int(tokens[0][1:])
        elif tokens[0][0] == 'r': # register
            shifter_operand |= REGISTERS[tokens[0]]
    elif len(tokens) == 2:
        Rm = REGISTERS[tokens[0]]

        move = tokens[1].split()
        if move[0] == 'LSL':
            if move[1][0] == '#': # immediate
                shift_imm = int(move[1][1:])
                shifter_operand |= shift_imm << 7
                shifter_operand |= Rm
            else:
                Rs = REGISTERS[move[1]]
                shifter_operand |= Rs << 8
                shifter_operand |= 1 << 4
                shifter_operand |= Rm
        elif move[0] == 'LSR':
            if move[1][0] == '#': # immediate
                shift_imm = int(move[1][1:])
                shifter_operand |= shift_imm << 7
                shifter_operand |= 1 << 5
                shifter_operand |= Rm
            else:
                Rs = REGISTERS[move[1]]
                shifter_operand |= Rs << 8
                shifter_operand |= 1 << 5
                shifter_operand |= 1 << 4
                shifter_operand |= Rm
        elif move[0] == 'ASR':
            if move[1][0] == '#': # immediate
                shift_imm = int(move[1][1:])
                shifter_operand |= shift_imm << 7
                shifter_operand |= 1 << 6
                shifter_operand |= Rm
            else:
                Rs = REGISTERS[move[1]]
                shifter_operand |= Rs << 8
                shifter_operand |= 1 << 6
                shifter_operand |= 1 << 4
                shifter_operand |= Rm
        elif move[0] == 'ROR':
            if move[1][0] == '#': # immediate
                shift_imm = int(move[1][1:])
                shifter_operand |= shift_imm << 7
                shifter_operand |= 1 << 6
                shifter_operand |= 1 << 5
                shifter_operand |= Rm
            else:
                Rs = REGISTERS[move[1]]
                shifter_operand |= Rs << 8
                shifter_operand |= 1 << 6
                shifter_operand |= 1 << 5
                shifter_operand |= 1 << 4
                shifter_operand |= Rm
        elif move[0] == 'RRX':
            shifter_operand |= 1 << 6
            shifter_operand |= 1 << 5
            shifter_operand |= Rm
    else:
        raise Exception('Invalid arguments: {}'.format(args))

    encoding |= I << 25
    encoding |= shifter_operand

    return encoding


def encode_move(cond, mnemonic, S, args):
    encoding = 0

    Rd, shifter = [i.strip() for i in args.split(',', 1)]

    opcode = DATA_PROCESSING_OPCODE[mnemonic]

    encoding |= cond << 28
    encoding |= opcode << 21
    encoding |= S << 20
    encoding |= REGISTERS[Rd] << 12
    encoding |= encode_data_processing_shifter(shifter)

    return encoding


def encode_compare(cond, mnemonic, args):
    encoding = 0

    Rn, shifter = [i.strip() for i in args.split(',', 1)]

    opcode = DATA_PROCESSING_OPCODE[mnemonic]

    encoding |= cond << 28
    encoding |= opcode << 21
    encoding |= 0b01 << 20
    encoding |= REGISTERS[Rn] << 16
    encoding |= encode_data_processing_shifter(shifter)

    return encoding

def encode_alu(cond, mnemonic, S, args):
    encoding = 0

    Rd, Rn, shifter = [i.strip() for i in args.split(',', 2)]

    opcode = DATA_PROCESSING_OPCODE[mnemonic]

    encoding |= cond << 28
    encoding |= opcode << 21
    encoding |= S << 20
    encoding |= REGISTERS[Rn] << 16
    encoding |= REGISTERS[Rd] << 12
    encoding |= encode_data_processing_shifter(shifter)

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
        elif itype == 'b':
            encoding = encode_branch(args, cond, L = 0b00)
        elif itype == 'bl':
            encoding = encode_branch(args, cond, L = 0b01)
        elif itype == 'add' or itype == 'sub' or itype == 'rsb' or itype == 'adc' or itype == 'sbc'\
            or itype == 'rsc' or itype == 'and' or itype == 'bic' or itype == 'eor' or itype == 'orr':
            encoding = encode_alu(cond, itype, S = 0b01 if dtype == 's' else 0b00, args = args)
        elif itype == 'cmp' or itype == 'cmn' or itype == 'tst' or itype == 'teq':
            encoding = encode_compare(cond, itype, args = args)
        elif itype == 'mov' or itype == 'mvn':
            encoding = encode_move(cond, itype, S = 0b01 if dtype == 's' else 0b00, args = args)

        if encoding: encodings.append(encoding)

    packed_encodings = []
    for encoding in encodings:
        packed = struct.pack('<I', encoding)
        packed_encodings.append(packed)

    return packed_encodings


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Error: no input file to assemble. Usage: ./asm.py <file>.s')
        exit(1)

    filename = sys.argv[1]
    fin = open(filename, 'r')
    source_lines = fin.readlines()
    fin.close()

    instructions = first_pass(source_lines)
    encodings = second_pass(instructions)

    fout = open(''.join([filename.split('.')[0], '.o']), 'wb')
    for encoding in encodings:
        print(encoding)
        fout.write(encoding)
    fout.close()


