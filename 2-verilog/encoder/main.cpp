#include "verilated.h"
#include "Vencoder.h"

int main(int argc, char** argv, char** env) {
    Verilated::commandArgs(argc, argv);
    Vdecoder* v = new Vdecoder;
    while (!Verilated::gotFinish()) { // gotFinish() check for $finish directive in verilog module
        v->eval();
    }
    delete v;
    exit(0);
}
