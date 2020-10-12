#include "verilated.h"
#include "Vhello.h"
#include "testbench.h"

#include <cstdio>
#include <cstdlib>

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    Testbench<Vhello> *tb = new Testbench<Vhello>();
    while (!tb->done()) {
        tb->tick();
    }
    delete tb;

    exit(EXIT_SUCCESS);
}
