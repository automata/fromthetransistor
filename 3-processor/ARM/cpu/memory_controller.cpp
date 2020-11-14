#include "verilated.h"
#include "Vmemory_controller.h"

#include <cstdio>
#include <cstdlib>

Vmemory_controller* tb;

void tick() {
    tb->mclk = 0;
    tb->eval();

    tb->mclk = 1;
    tb->eval();

    printf("address = %d\n lock = %d\n mas = %d\n nrw = %d\n nopc = %d\n", tb->memory_controller__DOT__reg_address_bus, tb->memory_controller__DOT__reg_lock, tb->memory_controller__DOT__reg_mas, tb->memory_controller__DOT__reg_nrw, tb->memory_controller__DOT__reg_nopc);

    printf("reg_din = %d din = %d\n", tb->memory_controller__DOT__reg_din, tb->din);
}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    tb = new Vmemory_controller;

    tb->address_bus = 0;
    tb->lock = 1;
    tb->mas = 0; // byte
    tb->nrw = 0; // read
    tb->nopc = 0; // nopcode
    tb->dout = 0; // dont care

    tb->ale = 0;
    tick();

    tb->ale = 1;
    tick();

    tick();
    tick();

    exit(EXIT_SUCCESS);
}
