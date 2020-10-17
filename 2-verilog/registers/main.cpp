#include "verilated.h"
#include "Vregister.h"

#include <verilated_vcd_c.h>

#include <cstdio>
#include <cstdlib>

VerilatedVcdC* trace;
Vregister* reg;

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);
    trace = new VerilatedVcdC;

    reg = new Vregister;
    reg->trace(trace, 99);
    trace->open("register_trace.vcd");

    // allow signals to settle
    reg->clk = 0;
    reg->eval();
    trace->dump(0);

    reg->enable = 1;

    // store all 1s
    reg->clk = 0;
    reg->eval();
    trace->dump(1);

    reg->signals = 255;

    reg->clk = 1;
    reg->eval();
    trace->dump(2);

    reg->clk = 0;
    reg->eval();
    trace->dump(3);

    // should all be 1
    printf("%d\n", reg->bits);

    delete reg;

    trace->close();
    trace = NULL;
    exit(EXIT_SUCCESS);
}
