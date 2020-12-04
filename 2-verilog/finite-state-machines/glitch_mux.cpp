#include "verilated.h"
#include "Vglitch_mux.h"

#include <verilated_vcd_c.h>

#include <cstdio>
#include <cstdlib>
#include <cassert>

Vglitch_mux* tb;
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
    tb = new Vglitch_mux;

    tb->trace(trace, 99);
    trace->open("glitch_mux_trace.vcd");

    tick();

    tb->sel = 0;
    tb->in0 = 0;
    tb->in1 = 0;

    tick();

    tb->sel = 0;
    tb->in0 = 1;
    tb->in1 = 0;

    tick();

    tb->sel = 1;
    tb->in0 = 1;
    tb->in1 = 0;

    tick();

    tb->sel = 1;
    tb->in0 = 1;
    tb->in1 = 1;

    tick();

    tb->sel = 0;
    tb->in0 = 0;
    tb->in1 = 0;

    tick();


    trace->close();

    exit(EXIT_SUCCESS);
}
