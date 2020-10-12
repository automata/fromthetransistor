#include "verilated.h"
#include "Vdecoder.h"

int main(int argc, char** argv, char** env) {
    Verilated::commandArgs(argc, argv);
    Vdecoder* v = new Vdecoder;
    unsigned short var = 0;
    while (!Verilated::gotFinish()) { // gotFinish() check for $finish directive in verilog module
        // set inputs
        v->A = var & 1;
        v->B = (var & 2) >> 1;
        printf("A=%d | B=%d\n", v->A, v->B);

        v->eval(); // eval

        // get outputs
        printf("%d%d%d%d\n", v->F3, v->F2, v->F1, v->F0);
        var += 1;
        var %= 4;
    }
    delete v;
    exit(0);
}
