#include "verilated.h"
#include "Vbarrel_shifter.h"

#include <cstdio>
#include <cstdlib>
#include <cassert>

Vbarrel_shifter* tb;
int temp = 0;

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    tb = new Vbarrel_shifter;

    tb->data_in = 4;
    tb->shift = 2;
    tb->eval();
    temp = tb->data_out;
    assert(temp == 1);

    tb->data_in = 4;
    tb->shift = 3;
    tb->eval();
    temp = tb->data_out;
    assert(temp == -2147483648);

    puts("DONE BARREL.");

    delete tb;
    tb = NULL;

    exit(EXIT_SUCCESS);
}
