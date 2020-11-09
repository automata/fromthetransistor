#!/usr/bin/python
import asm
import struct

def pack(num):
    return struct.pack('<I', num)

def unpack(num):
    return struct.unpack('<I', num)

def test(table):
    instructions = asm.first_pass(list(table.keys()))
    encodings = asm.second_pass(instructions)

    for i, (instr, valid_encoding) in enumerate(table.items()):
        print(instr)
        assert unpack(encodings[i]) == unpack(valid_encoding)

def test_encode_load_store():
    print('Testing encode_load_store ...')

    table = {
        # regular loads
        ' ldr r0, [r1]': b'\x00\x00\x91\xE5',
        ' ldrb r0, [r1]': b'\x00\x00\xD1\xE5',
        ' ldreq r0, [r1]': b'\x00\x00\x91\x05',
        ' ldrne r0, [r1]': b'\x00\x00\x91\x15',
        ' ldreqb r0, [r1]': b'\x00\x00\xD1\x05',
        ' ldrneb r0, [r1]': b'\x00\x00\xD1\x15',
        ' str r0, [r1]': b'\x00\x00\x81\xE5',
        ' strb r0, [r1]': b'\x00\x00\xC1\xE5',
        ' streq r0, [r1]': b'\x00\x00\x81\x05',
        ' strne r0, [r1]': b'\x00\x00\x81\x15',
        ' streqb r0, [r1]': b'\x00\x00\xC1\x05',
        ' strneb r0, [r1]': b'\x00\x00\xC1\x15',
        ' ldr r0, [r1, #+4]': b'\x04\x00\x91\xE5',
        ' ldr r0, [r1, #-4]': b'\x04\x00\x11\xE5',
        ' ldr r0, [r1, r2]': b'\x02\x00\x91\xE7',
        ' ldr r0, [r1, -r2]': b'\x02\x00\x11\xE7',
        ' ldr r0, [r1, r2, LSL #4]': b'\x02\x02\x91\xE7',
        ' ldr r0, [r1, r2, LSR #4]': b'\x22\x02\x91\xE7',
        ' ldr r0, [r1, r2, ASR #4]': b'\x42\x02\x91\xE7',
        ' ldr r0, [r1, r2, ROR #4]': b'\x62\x02\x91\xE7',
        ' ldr r0, [r1, r2, RRX]': b'\x62\x00\x91\xE7',
        # pre-indexed loads
        ' ldr r0, [r1]!': b'\x00\x00\xB1\xE5',
        ' ldr r0, [r1, #+4]!': b'\x04\x00\xB1\xE5',
        ' ldr r0, [r1, #-4]!': b'\x04\x00\x31\xE5',
        ' ldr r0, [r1, r2]!': b'\x02\x00\xB1\xE7',
        ' ldr r0, [r1, -r2]!': b'\x02\x00\x31\xE7',
        ' ldr r0, [r1, r2, LSL #4]!': b'\x02\x02\xB1\xE7',
        ' ldr r0, [r1, r2, LSR #4]!': b'\x22\x02\xB1\xE7',
        ' ldr r0, [r1, r2, ASR #4]!': b'\x42\x02\xB1\xE7',
        ' ldr r0, [r1, r2, ROR #4]!': b'\x62\x02\xB1\xE7',
        ' ldr r0, [r1, r2, RRX]!': b'\x62\x00\xB1\xE7',
        ' ldr r0, [r1, -r2, LSL #4]!': b'\x02\x02\x31\xE7',
        ' ldr r0, [r1, -r2, LSR #4]!': b'\x22\x02\x31\xE7',
        ' ldr r0, [r1, -r2, ASR #4]!': b'\x42\x02\x31\xE7',
        ' ldr r0, [r1, -r2, ROR #4]!': b'\x62\x02\x31\xE7',
        ' ldr r0, [r1, -r2, RRX]!': b'\x62\x00\x31\xE7',
        # post-indexed loads
        ' ldr r0, [r1], #+4': b'\x04\x00\x91\xE4',
        ' ldr r0, [r1], #-4': b'\x04\x00\x11\xE4',
        ' ldr r0, [r1], r2': b'\x02\x00\x91\xE6',
        ' ldr r0, [r1], -r2': b'\x02\x00\x11\xE6',
        ' ldr r0, [r1], r2, LSL #4': b'\x02\x02\x91\xE6',
        ' ldr r0, [r1], r2, LSR #4': b'\x22\x02\x91\xE6',
        ' ldr r0, [r1], r2, ASR #4': b'\x42\x02\x91\xE6',
        ' ldr r0, [r1], r2, ROR #4': b'\x62\x02\x91\xE6',
        ' ldr r0, [r1], r2, RRX': b'\x62\x00\x91\xE6',
        ' ldr r0, [r1], -r2, LSL #4': b'\x02\x02\x11\xE6',
        ' ldr r0, [r1], -r2, LSR #4': b'\x22\x02\x11\xE6',
        ' ldr r0, [r1], -r2, ASR #4': b'\x42\x02\x11\xE6',
        ' ldr r0, [r1], -r2, ROR #4': b'\x62\x02\x11\xE6',
        ' ldr r0, [r1], -r2, RRX': b'\x62\x00\x11\xE6',
    }

    print('Done testing encode_load_store')


def test_encode_move():
    print('Testing encode_move ...')

    table = {
        ' mov r0, #10': b'\x0A\x00\xA0\xE3',
        ' mvn r0, #10': b'\x0A\x00\xE0\xE3', # just the opcode differs
        ' mvn r4, #10': b'\x0A\x40\xE0\xE3',
        ' movs r0, #10': b'\x0A\x00\xB0\xE3',
        ' moveq r0, #10': b'\x0A\x00\xA0\x03',
        ' moveqs r0, #10': b'\x0A\x00\xB0\x03',
        ' mov r0, r1': b'\x01\x00\xA0\xE1',
        ' mov r0, r1, LSL #10': b'\x01\x05\xA0\xE1',
        ' mov r0, r1, LSL r4': b'\x11\x04\xA0\xE1',
        ' mov r0, r1, LSR #10': b'\x21\x05\xA0\xE1',
        ' mov r0, r1, LSR r4': b'\x31\x04\xA0\xE1',
        ' mov r0, r1, ASR #10': b'\x41\x05\xA0\xE1',
        ' mov r0, r1, ASR r4': b'\x51\x04\xA0\xE1',
        ' mov r0, r1, ROR #10': b'\x61\x05\xA0\xE1',
        ' mov r0, r1, ROR r4': b'\x71\x04\xA0\xE1',
        ' mov r0, r1, RRX': b'\x61\x00\xA0\xE1',
    }

    test(table)

    print('Done testing encode_move')


def test_encode_compare():
    print('Testing encode_compare ...')

    table = {
        ' cmp r0, #10': b'\x0A\x00\x50\xE3',
        ' cmp r3, #10': b'\x0A\x00\x53\xE3',
        ' cmpeq r3, #10': b'\x0A\x00\x53\x03',
        ' cmn r3, #10': b'\x0A\x00\x73\xE3',
        ' cmneq r3, #10': b'\x0A\x00\x73\x03',
        ' teq r3, #10': b'\x0A\x00\x33\xE3',
        ' teqeq r3, #10': b'\x0A\x00\x33\x03',
        ' tst r3, #10': b'\x0A\x00\x13\xE3',
        ' tsteq r3, #10': b'\x0A\x00\x13\x03',
        ' cmp r0, r1': b'\x01\x00\x50\xE1',
        ' cmp r0, r1, LSL #10': b'\x01\x05\x50\xE1',
        ' cmp r0, r1, LSL r4': b'\x11\x04\x50\xE1',
        ' cmp r0, r1, LSR #10': b'\x21\x05\x50\xE1',
        ' cmp r0, r1, LSR r4': b'\x31\x04\x50\xE1',
        ' cmp r0, r1, ASR #10': b'\x41\x05\x50\xE1',
        ' cmp r0, r1, ASR r4': b'\x51\x04\x50\xE1',
        ' cmp r0, r1, ROR #10': b'\x61\x05\x50\xE1',
        ' cmp r0, r1, ROR r4': b'\x71\x04\x50\xE1',
        ' cmp r0, r1, RRX': b'\x61\x00\x50\xE1',
    }

    test(table)

    print('Done testing encode_compare')


def test_encode_alu():
    print('Testing encode_compare ...')

    table = {
        ' add r4, r2, #10': b'\x0A\x40\x82\xE2',
        ' sub r4, r2, #10': b'\x0A\x40\x42\xE2',
        ' rsb r4, r2, #10': b'\x0A\x40\x62\xE2',
        ' sbc r4, r2, #10': b'\x0A\x40\xC2\xE2',
        ' rsc r4, r2, #10': b'\x0A\x40\xE2\xE2',
        ' and r4, r2, #10': b'\x0A\x40\x02\xE2',
        ' bic r4, r2, #10': b'\x0A\x40\xC2\xE3',
        ' eor r4, r2, #10': b'\x0A\x40\x22\xE2',
        ' orr r4, r2, #10': b'\x0A\x40\x82\xE3',
        ' adc r4, r2, #10': b'\x0A\x40\xA2\xE2',
        ' adcs r4, r2, #10': b'\x0A\x40\xB2\xE2',
        ' adceqs r4, r2, #10': b'\x0A\x40\xB2\x02',
        ' adc r4, r1, r7': b'\x07\x40\xA1\xE0',
        ' adc r4, r7, r3, LSL #10': b'\x03\x45\xA7\xE0',
        ' adc r4, r7, r3, LSL r5': b'\x13\x45\xA7\xE0',
        ' adc r4, r7, r3, LSR #10': b'\x23\x45\xA7\xE0',
        ' adc r4, r7, r3, LSR r5': b'\x33\x45\xA7\xE0',
        ' adc r4, r7, r3, ASR #10': b'\x43\x45\xA7\xE0',
        ' adc r4, r7, r3, ASR r5': b'\x53\x45\xA7\xE0',
        ' adc r4, r7, r3, ROR #10': b'\x63\x45\xA7\xE0',
        ' adc r4, r7, r3, ROR r5': b'\x73\x45\xA7\xE0',
        ' adc r4, r7, r3, RRX': b'\x63\x40\xA7\xE0',
    }

    test(table)

    print('Done testing encode_compare')


def test_encode_multiply():
    print('Testing encode_multiply...')

    table = {
        ' mul r2, r3, r4': b'\x93\x04\x02\xE0',
        ' muls r2, r3, r4': b'\x93\x04\x12\xE0',
        ' muleq r2, r3, r4': b'\x93\x04\x02\x00',
        ' muleqs r2, r3, r4': b'\x93\x04\x12\x00',
        ' mla r2, r3, r4, r5': b'\x93\x54\x22\xE0',
        ' mlas r2, r3, r4, r5': b'\x93\x54\x32\xE0',
        ' mlaeq r2, r3, r4, r5': b'\x93\x54\x22\x00',
        ' mlaeqs r2, r3, r4, r5': b'\x93\x54\x32\x00',
    }

    test(table)

    print('Done testing encode_multiply...')


def test_encode_swap():
    print('Testing swap...')

    table = {
        ' swp r1, r2, [r3]': b'\x92\x10\x03\xE1',
        ' swpeq r1, r2, [r3]': b'\x92\x10\x03\x01',
        ' swpb r1, r2, [r3]': b'\x92\x10\x43\xE1',
        ' swpeqb r1, r2, [r3]': b'\x92\x10\x43\x01',
    }

    test(table)

    print('Done testing swap...')


def test_swi():
    print('Testing swi...')

    table = {
        ' swi 43': b'\x2B\x00\x00\xEF',
        ' swieq 43': b'\x2B\x00\x00\x0F',
    }

    test(table)

    print('Done testing swi...')


test_encode_load_store()
test_encode_move()
test_encode_compare()
test_encode_alu()
test_encode_multiply()
test_encode_swap()
test_swi()
