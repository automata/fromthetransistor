#include "verilated.h"
#include "Vasync.h"

#include <verilated_vcd_c.h>

#include <cstdio>
#include <cstdlib>

VerilatedVcdC* trace;
Vasync* async;

int tick = 0;

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);
    trace = new VerilatedVcdC;

    async = new Vasync;
    async->trace(trace, 99);
    trace->open("async_trace.vcd");

    // *** start logic
    // write
    async->write = 1;
    async->address = 2;
    async->data_in = 15; // all 1s
    async->eval(); // settle

    // read
    async->write = 0;
    async->address = 2;
    async->eval();

    printf("data = %d\n", async->data_out);

    // *** end logic

    trace->close();
    printf("ticks = %d\n", tick);

    // cleanup
    delete async;
    delete trace;
    async = NULL;
    trace = NULL;

    exit(EXIT_SUCCESS);
}
