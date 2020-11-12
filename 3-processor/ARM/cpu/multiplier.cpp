#include "verilated.h"
#include "Vmultiplier.h"

#include <cstdio>
#include <cstdlib>
#include <cassert>

Vmultiplier* tb;

void tick() {
    tb->clk = 0;
    tb->eval();

    tb->clk = 1;
    tb->eval();

    tb->clk = 0;
}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    tb = new Vmultiplier;

    tick();

    tb->a = 2;
    tb->b = 3;

    tick();
    tick();

    long long result = tb->result;
    printf("%lld\n", result);

    delete tb;
    tb = NULL;

    exit(EXIT_SUCCESS);
}
