#!/usr/bin/python
import asm
import struct

def pack(num):
    return struct.pack('<I', num)

def unpack(num):
    return struct.unpack('<I', num)

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

    instructions = asm.first_pass(list(table.keys()))
    encodings = asm.second_pass(instructions)

    for i, (_, valid_encoding) in enumerate(table.items()):
        assert unpack(encodings[i]) == unpack(valid_encoding)


    # pre-indexed loads
    # post-indexed loads

    print('Done testing encode_load_store')

test_encode_load_store()
