Contains 2 CPUs:
- simple 8bit one coded fully in verilog, with no assembler (tiny instruction set); this was made to get the basics right
    - no logic to load custom program. All preloaded into ROM, cannot flash new stuff into it
    - no pipelined execution
    - not fully synthesizable
    - no MMU, so no cache
    - no interrupts
    - no debug mode, so no JTAG + TAP
    - shitty untested timings, but seems to work
- 32-bit ARM7 with an ARM9 MMU
