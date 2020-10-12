#include "verilated.h"
#include "Vmux.h"

int main(int argc, char** argv, char** env) {
    Verilated::commandArgs(argc, argv);
    Vmux* v = new Vmux;
    while (!Verilated::gotFinish()) { // gotFinish() check for $finish directive in verilog module
        v->in = 7; // 8bit input, all 1s
        v->sel = 1; // 3bit input
        printf("in=%d\n", v->in);
        printf("in=%d\n", v->sel);

        v->eval();
        printf("out=%d\n", v->out);
    }
    delete v;
    exit(0);
}
