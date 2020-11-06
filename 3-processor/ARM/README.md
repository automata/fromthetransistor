# ARM7 CPU
ARM == Advanced RISC Machine, RISC = Reduced Instruction Set Computer

ARM the company licenses the design of CPUs to manufacturers and makes money on royalties.

- this is based on ARM7TDMI, without the T though, so without the Thumb ISA implemented.
    - D: JTAG **D**ebug
    - M: fast **M**ultiplier
    - I: [enhanced **I**CE](https://en.wikipedia.org/wiki/In-circuit_emulation), works together with JTAG for system-wide debug
- a bit old, but relatively easy to implement since the docs are concise and explain the concepts well
    - easy to make sure it works since all the timings and logic are provided as IP by ARM
    - we make the RTL and synthesize it based on the manual implementation, then run the image on the FPGA
        - not sure yet how much SRAM I'll need for this
    - pipelined, so much faster than the 8-bit one
    - ARM7 does not have a MMU, which means there is no support for any levels of cache, which in turns means that all fetches are made directly from memory to the registers. However we will implement a MMU similar to the one in ARM9, otherwise this whole thing will be terribly slow
    - still, this has a lot more stuff than the 8-bit one, so do that first
- 32-bit address space, registers, shifters + ALU, bus
- single 2-way 32-bit data bus carrying both instructions and data to memory
- 3 stage pipeline: fetch, decode execute
- pipelined processor: while an instruction is executed, its successor is being decoded and a third instruction is fetched
- only load, store and swap instructions can access data from memory
- data can be: 8-bit (bytes), 16-bit (half-words), 32-bit (words)
- words aligned to 4-byte boundaries, half-words to 2-byte
- supports fast burst access to memory (memory given full acccess to bus, CPU suspending interrupts while that happens)
- supports JTAG for easy processor state inspection
- full debug support through TAP (so you can have breakpoints, watchpoints + external debug requests)
- supports exceptions and exception handling
- memory seen as a linear collection of bytes numbered in ascending order starting from zero
- endian format: little-endian (least significant byte at smallest address in word)
- extend functionality by supporting coprocessors
    - CP14 is the internal debug coprocessor already baked into the chip
- 2 clocks:
    - **MCLK**: memory clock, during normal operation, core is clocked by this one
    - **DCLK**: debug clock, core is clocked by this one only in debug state under the control of the TAP state machine, **MCLK** can free run here and you can output either through **ECLK**

Operating modes:
- user: executes most application programs + kernel since OS will be full user mode
- fast interrupt **FIQ**: data transfer or channel process
- interrupt **IRQ**: general-purpose interrupt handling
- supervisor: protected mode for the OS
- abort: entered after data or instruction pre-fetch abort
- undefined: entered when an undefined instruction is executed

Registers:
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

