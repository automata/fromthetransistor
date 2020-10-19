#include "verilated.h"
#include "Vserial.h"

#include <verilated_vcd_c.h>

#include <cstdio>
#include <cstdlib>

VerilatedVcdC* trace;
Vserial* serial;

int tick = 0;

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);
    trace = new VerilatedVcdC;

    serial = new Vserial;
    serial->trace(trace, 99);
    trace->open("serial_trace.vcd");

    // *** start logic
    constexpr int N = 15;
    int arr[N] = {
        0, 1, 1,
        0, 1, 0,
        1, 1, 1, // err
        0, 0, 1, // err wrapped below
        1, 1, 0
    };

    for (int i = 0; i < N; i++) {
        serial->Din = arr[i];
        serial->eval();

        tick++;

        // settle
        serial->clk = 0;
        serial->eval();
        trace->dump(10 * tick - 2);

        // rising edge
        serial->clk = 1;
        serial->eval();
        trace->dump(10 * tick);

        // falling edge
        serial->clk = 0;
        serial->eval();
        trace->dump(10 * tick + 5);
        trace->flush();

        for (int j = 0; j < i; j++) printf("%d", arr[j]);
        for (int j = i; j < N; j++) printf(" ");
        printf(" ::: err = %d\n", serial->error);

        tick++;
    }
    // settle
    serial->clk = 0;
    serial->eval();
    trace->dump(10 * tick - 2);
    trace->flush();
    // *** end logic

    trace->close();
    printf("ticks = %d\n", tick);

    // cleanup
    delete serial;
    delete trace;
    serial = NULL;
    trace = NULL;

    exit(EXIT_SUCCESS);
}
