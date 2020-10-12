#include "verilated.h"

#include "Vfull_adder.h"

#include <verilated_vcd_c.h> // for tracing

#include <cstdio>
#include <cstdlib>

Vfull_adder *fa;
VerilatedVcdC *trace;

int tick = 0;

void onerun(int a, int b, int c) {
    // set inputs
    fa->A = a;
    fa->B = b;
    fa->Cin = c;

    fa->eval();

    printf("%d %d %d ::: sum=%d cout=%d\n", a, b, c, fa->Sum, fa->Cout);

    // write trace
    trace->dump(tick);
    trace->flush();

    tick++;
}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true); // turn on trace

    fa = new Vfull_adder;
    trace = new VerilatedVcdC;

    fa->trace(trace, 99);
    trace->open("full_adder_trace.vcd");

    int arg = 0;
    while (arg < 8) {
        int a = arg & 1;
        int b = arg & 2;
        int c = arg & 4;

        b >>= 1;
        c >>= 2;

        onerun(a, b, c);
        arg++;
    }
    onerun(1, 1, 1); // one more for a nice wave

    printf("%d ticks elapsed\n", tick);

    trace->close();

    delete fa;
    delete trace;

    exit(EXIT_SUCCESS);
}
