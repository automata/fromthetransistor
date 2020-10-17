#include "verilated.h"
#include "Vshift.h"

#include <verilated_vcd_c.h>

#include <cstdio>
#include <cstdlib>

VerilatedVcdC* trace;
Vshift* reg;

int tick = 0;

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);
    trace = new VerilatedVcdC;

    reg = new Vshift;
    reg->trace(trace, 99);
    trace->open("shift_trace.vcd");

    // allow signals to settle
    reg->clk = 0;
    reg->enable = 1;
    reg->eval();
    trace->dump(tick++);

    for (int store = 1; store < 5; store++) {
        reg->clk = 0;
        reg->eval();
        trace->dump(tick++);

        reg->Din = store;
        reg->clk = 1;
        reg->eval();
        trace->dump(tick++);

        printf("%d | %d | %d | %d\n", reg->Dout0, reg->Dout1, reg->Dout2, reg->Dout3);
    }

    delete reg;

    trace->close();
    trace = NULL;
    exit(EXIT_SUCCESS);
}
