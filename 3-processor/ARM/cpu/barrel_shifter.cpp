#include "verilated.h"
#include "Vbarrel_shifter.h"

#include <cstdio>
#include <cstdlib>
#include <cassert>

Vbarrel_shifter* tb;


int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    tb = new Vbarrel_shifter;

    tb->in = 4;
    tb->select = 2;
    tb->eval();
    assert(tb->out == 1);

    tb->in = 4;
    tb->select = 3;
    tb->eval();
    int temp = tb->out;
    assert(temp == -2147483648);

    puts("DONE BARREL.");

    delete tb;
    tb = NULL;

    exit(EXIT_SUCCESS);
}
