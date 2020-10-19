#include "verilated.h"
#include "Vfsm.h"

#include <verilated_vcd_c.h>

#include <cstdio>
#include <cstdlib>

VerilatedVcdC* trace;
Vfsm* fsm;

int tick = 0;

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);
    trace = new VerilatedVcdC;

    fsm = new Vfsm;
    fsm->trace(trace, 99);
    trace->open("fsm_trace.vcd");

    // *** start logic
    while (tick < 100) {
        fsm->button = (tick % 3 == 0) ? 1 : 0;

        tick++;

        // let stuff settle
        fsm->clk = 0;
        fsm->eval();
        trace->dump(10 * tick - 2);

        fsm->clk = 1;
        fsm->eval();
        trace->dump(10 * tick);

        fsm->clk = 0;
        fsm->eval();
        trace->dump(10 * tick + 5);
        trace->flush(); // flush to file
   

    // *** end logic

    trace->close();
    printf("ticks = %d\n", tick);

    // cleanup
    delete fsm;
    delete trace;
    fsm = NULL;
    trace = NULL;

    exit(EXIT_SUCCESS);
}
