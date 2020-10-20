#include "verilated.h"
#include "Vserial.h"
#include "testbench.h"

#include <cstdio>
#include <cstdlib>
#include <vector>

int tick = 1;

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Testbench<Vserial>* tb = new Testbench<Vserial>;

    std::vector<int> arr = { 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 };
    std::vector<int> sofar;

    tb->set_trace("serial_trace.vcd");

    tb->reset();
    for (auto i : arr) {
        tb->m_core->Din = i;
        sofar.push_back(i);
        tb->tick();
        for (auto j : sofar) printf("%d", j);
        printf("::: %d\n", tb->m_core->error);
    }

    exit(EXIT_SUCCESS);
}
