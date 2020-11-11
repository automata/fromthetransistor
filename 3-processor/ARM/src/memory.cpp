#include "verilated.h"
#include "Vmemory.h"
#include "testbench.h"

#include <cstdio>
#include <cstdlib>

Testbench<Vmemory>* tb;

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    tb = new Testbench<Vmemory>;

    tb->reset();

    exit(EXIT_SUCCESS);
}
