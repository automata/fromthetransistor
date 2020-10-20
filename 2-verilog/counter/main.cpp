#include "verilated.h"
#include "Vcounter.h"

#include <cstdio>
#include <cstdlib>

Vcounter* counter;

int tick = 0;

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    counter = new Vcounter;

    counter->clk = 0;
    counter->eval();

    for (int i = 0; i < 100; i++) {
        // tick
        counter->clk = 0;
        counter->eval();

        counter->clk = 1;
        counter->eval();

        printf("%d\n", counter->count);
    }

    // cleanup
    delete counter;
    counter = NULL;

    exit(EXIT_SUCCESS);
}
