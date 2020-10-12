#include "verilated.h"
#include "Vhello.h"

int main(int argc, char** argv, char** env) {
    Verilated::commandArgs(argc, argv);
    Vhello* v = new Vhello;
    while (!Verilated::gotFinish()) { // gotFinish() check for $finish directive in verilog module
        v->eval();
    }
    delete v;
    exit(0);
}
