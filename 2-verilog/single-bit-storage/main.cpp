#include "verilated.h"
#include "Vdlatch.h"
#include "Vdflipflop.h"

#include <verilated_vcd_c.h>

#include <cstdio>
#include <cstdlib>

VerilatedVcdC* trace;

//Vdlatch* dlatch;
Vdflipflop* dff;

int ticks = 0;

/*
void dlatch_onerun(int clk, int d) {
    dlatch->clk = clk;
    dlatch->D = d;

    dlatch->eval();

    printf("clk=%d d=%d :: q=%d qn=%d\n", clk, d, dlatch->Q, dlatch->Qn);

    ticks++;
}
*/

void dff_onerun(int clk, int reset, int preset, int enable, int d) {
    dff->clk = clk;
    dff->reset = reset;
    dff->preset = preset;
    dff->enable = enable;
    dff->D = d;

    dff->eval();

    printf("clk=%d reset=%d preset=%d enable=%d d=%d :: q=%d qn=%d\n", clk, reset, preset, enable, d, dff->Q, dff->Qn);

    ticks++;
}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);
    trace = new VerilatedVcdC;

    //dlatch = new Vdlatch;
    //dlatch->trace(trace, 99);
    //trace->open("dlatch_trace.vcd");
    //dlatch_onerun(0, 0);
    //dlatch_onerun(0, 1);
    //dlatch_onerun(1, 0);
    //dlatch_onerun(1, 1);
    //dlatch_onerun(1, 1);

    dff = new Vdflipflop;
    dff->trace(trace, 99);
    trace->open("dff_trace.vcd");
    
    for (int clocks = 20, clock = 1; clocks > 0; clocks--, clock = 1 - clock) {
        printf("%s\n", (clock == 1 ? "high" : "low"));
        if (clocks == 20 || clocks == 0) {
            dff_onerun(clock, 1, 0, 0, 0);
        }
        // enabled
        dff_onerun(clock, 0, 0, 1, 0);
        dff_onerun(clock, 0, 0, 1, 1);

        // not enabled
        dff_onerun(clock, 0, 0, 0, 0);
        dff_onerun(clock, 0, 0, 0, 1);

        printf("\n");
    }

    //delete dlatch;
    delete dff;

    printf("%d ticks elapsed\n", ticks);

    trace->close();
    exit(EXIT_SUCCESS);
}
