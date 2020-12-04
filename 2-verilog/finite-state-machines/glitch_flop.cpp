#include "verilated.h"
#include "Vglitch_flop.h"

#include <verilated_vcd_c.h>

#include <cstdio>
#include <cstdlib>
#include <cassert>

Vglitch_flop* tb;
VerilatedVcdC* trace;

int ticks = 0;

void tick() {
    ticks++;
    tb->eval();
    trace->dump(10 * ticks);
    trace->flush();
}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    trace = new VerilatedVcdC;
    tb = new Vglitch_flop;

    tb->trace(trace, 99);
    trace->open("glitch_flop_trace.vcd");

    tb->clk = 0;
    tb->din = 0;
    tick();

    tb->clk = 1;
    tb->din = 1;
    tick();

    tb->clk = 0;
    tb->din = 1;
    tick();

    tb->clk = 1;
    tb->din = 0;
    tick();

    tb->clk = 0;
    tb->din = 0;
    tick();

    trace->close();

    exit(EXIT_SUCCESS);
}
