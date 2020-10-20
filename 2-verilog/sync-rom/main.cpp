#include "verilated.h"
#include "Vrom.h"

#include <verilated_vcd_c.h>

#include <cstdio>
#include <cstdlib>

VerilatedVcdC* trace;
Vrom* rom;

int tick = 0;

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);
    trace = new VerilatedVcdC;

    rom = new Vrom;
    rom->trace(trace, 99);
    trace->open("rom_trace.vcd");

    // *** start logic
    rom->clk = 0;
    rom->eval();

    rom->clk = 0;
    rom->address = 2;
    rom->eval();

    rom->clk = 1;
    rom->eval();

    printf("fetched = %d\n", rom->data_out);
    // *** end logic

    trace->close();
    printf("ticks = %d\n", tick);

    // cleanup
    delete rom;
    delete trace;
    rom = NULL;
    trace = NULL;

    exit(EXIT_SUCCESS);
}
