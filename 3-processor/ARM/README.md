# ARM7 CPU
## What is ARM?
- ARM == Advanced RISC Machine
- RISC = Reduced Instruction Set Computer
- ARM the company licenses the design of CPUs to manufacturers and makes money on royalties and possibly, consulting.

## What is this?
- this is an [ARM7TDMI](https://developer.arm.com/documentation/ddi0210/c/) based 32-bit ARM CPU, with some differences:
    - **no T** (T = **Thumb**): no Thumb instruction set
        - ARM processor have 2 instruction sets: **ARM** and **Thumb**
        - **Thumb** is a reduced instruction set in which less registers are accessible and all instructions are 16-bit encoded (... and extended to 32-bit)
        - all instructions in **Thumb** can be executed in **ARM**
        - only the branch instruction is conditionally executed in **Thumb**, while **ARM** allows all instructions to be conditionally executed
    - **no M** (M = fast **M**ultiplier): there is no support for 64-bit multiplications
    - no fast interrupts ([FIQs](https://stackoverflow.com/questions/13777229/fiq-irq-handler-arm))
    - User mode has full privileges
        - ... which means that any OS will be running in full userspace, so all user programs will have full access to system resources
        - ... this also renders the **Supervisor** mode obsolete, as now there is no need for an interrupt from User mode to increase access privilege)
    - no support for **LDM**/**STM** (store/load multiple values at once)
- D: JTAG **D**ebug
- I: [enhanced **I**CE](https://en.wikipedia.org/wiki/In-circuit_emulation), together with JTAG provides system-wide debug capabilities from a serial port
- a bit old, but relatively easy to implement since the docs are concise and explain the concepts well
    - easy to make sure it works since all the timings and logic are provided as IP by ARM
    - we make the RTL and synthesize it based on the manual implementation, then run the image on the FPGA
        - not sure yet how much SRAM I'll need for this
    - pipelined, so much faster than the 8-bit one
    - ARM7 does not have a MMU, which means there is no support for any levels of cache, which in turns means that all fetches are made directly from memory to the registers. However we will implement an MMU similar to the one in ARM9, otherwise there is no way to run an OS on it

### Details
This is a soft-core CPU that's supposed to run directly on any FPGA fabric (given the adequate clock and memory requirements). Combined with the goal of being a simple and clear implementation for educational purposes only, this is not a full and complete implementation of the ARM standard.

- 32-bit address space, registers, shifters + ALU, bus
    - each address refers to 8-bits (1 byte) in memory
    - ... hence an instruction at address A is comprised of the bytes at A, A + 1, A + 2, A + 3
- single 2-way 32-bit data bus carrying both instructions and data to memory
- 3 stage pipeline: fetch, decode execute
    - pipelined: while an instruction is executed, another is decoded and a third is fetched
- only load, store and swap instructions can access data from memory
- data can be: 8-bit (bytes), 16-bit (half-words), 32-bit (words)
- words aligned to 4-byte boundaries, half-words to 2-byte
- supports JTAG for easy processor state inspection
- full debug support through TAP (so you can have breakpoints, watchpoints + external debug requests)
- supports exceptions and exception handling
- memory seen as a linear collection of bytes numbered in ascending order starting from zero
- endian format: little-endian (least significant byte at the smallest address in a word)
- all memory accesses are word-aligned
- no support for unaligned memory accesses
- no support for (S)DRAM
    - ... because DRAM chips have their own clock speed, so allowing DRAM in this ARM CPU means we would need to cross clock domains whenever the CPU --> memory address bus is taken, and that is too much work for a simple ARM implementation
    - as such, the address bus is depipelined, which works fine with SRAMs and ROMs (since there is no need to refresh these types of memory)

#### Buses
- **address** bus: depipelined, 32-bits, 4GB max addressable space, all addresses are byte addresses, all sent on this bus is word-aligned
- **data** bus: 

#### Operating modes
- user: executes most application programs + kernel since OS will be full user mode
- fast interrupt **FIQ**: data transfer or channel process
- interrupt **IRQ**: general-purpose interrupt handling
- supervisor: protected mode for the OS
- abort: entered after data or instruction pre-fetch abort
- undefined: entered when an undefined instruction is executed

#### Registers
- 31 general purpose 32-bit registers
- 6 status registers
- a **CPSR** program status register, carrying NZVC flags + some other state bits (like interrupt modes + states)
- a **SPSR** saved program status register used to save and then restore state on exceptions

- r0-r15: general purpose
    - a1-a4: synonyms to r0-r3; argument, result or scratch registers
    - v1-v8: synonyms to r4-r11; variable registers
    - sb: synonym to r9; static base register
    - ip: synonym to r12; intra procedure call scratch register
    - sp: synonym to r13; stack pointer
    - lr: synonym to r14; link register
        - used when executing subroutines
        - receives a copy of pc when a branch with link (**bl**) instruction is executed
    - pc: synonym to r15; program counter

# Resources
- [Staged pipeline](https://www.sciencedirect.com/topics/computer-science/stage-pipeline)

