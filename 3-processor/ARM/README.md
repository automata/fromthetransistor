# ARM
## What is ARM?
ARM == Advanced RISC Machine, RISC = Reduced Instruction Set Computer

ARM is a reduced instruction set CPU:
- large uniform register file (implemented as static RAM with multiple ports)
- a load/store architecture, data processing operations only operate on register, not directly on memory
- simple addressing modes, with all load/store addresses being determined from registers and instruction fields only

ARM the company licenses the design of CPUs to manufacturers and makes money on royalties.

## What is this?
This is a 32-bit CPU based on ARMv7-A (other are: ARMv7-R for real-time systems, ARMv7-M for MCUs which is similar to the 8-bit one):
- traditional ARM architecture with multiple addressing modes
- full support for ARM ISA
- supports virtual addressing system through a MMU (in OS)
- flat address space of 2^32 8-bit bytes
- suports multiple levels of caches
    - L1 and L2 as SRAM living in the processor
    - L3 reachable throgh a bus (SRAM, DRAM or flashed ROM)
- endianness: little-endian, so least significant byte at the smallest address

ISA is standard, with no extensions, specifically:
- no floating point module, supports only signed and unsigned integers
- no SIMD
- no protected memory mode
- no support for privileged execution

## Architecture
### Memory Model
- flat address space of 2^32 8-bit bytes, covering 4GBytes
- instructions have a 32-bit width and are word aligned
    - the word (32-bit) at address A comprises the bytes at addresses A, A + 1, A + 2, A + 3
    - the doubleword (64-bit) at address A comprises the bytes at addresses A, A + 1, A + 2, A + 3, A + 4, A + 5, A + 6, A + 7
- there is support for unaligned data access for some instructions, for others you get **Unaligned Fault**
### Memory types
3 main types:
- Normal (programmed flash ROM, ROM, SRAM, DRAM or DDR memory)
- Device
- Strongly Ordered

### Registers
- 16 core 32-bit registers
    - 13 general purpose 32-bit registers, R0 to R12
    - 3 32-bit special registers (R13 to R15):
        - **SP**: stack pointer
        - **LR**: link register
        - **PC**: program counter
            - writing an address to PC causes a branch to that address
- program status reported in the 32-bit Application Program Status Register **APSR**
    - status as **N** (negative), **Z** (zero), **C** (carry) and **V** (overflow)
### Data Types
- types:
    - 32-bit pointers
    - unsigned or signed 32-bit integers
    - unsigned 16-bit or 8-bit integers, held in zero-extended form
    - signed 16-bit or 8-bit integers, held in sign extended form
    - two 16-bit integers packed into a register
    - four 8-bit integers packed into a register
    - unsigned or signed 64-bit integers held in two registers
- integers range:
    - signed: -2^31 to 2^31 - 1 in two's complement
    - unsigned: 0 to 2^32 - 1
