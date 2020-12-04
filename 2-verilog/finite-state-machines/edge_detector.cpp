#include "verilated.h"
#include "Vedge_detector.h"
#include "testbench.h"

#include <cstdio>
#include <cstdlib>
#include <cassert>

Testbench<Vedge_detector>* tb;

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    tb = new Testbench<Vedge_detector>;

    tb->set_trace("edge_detector_trace.vcd");

    tb->m_core->level = 0;
    tb->m_core->reset = 0;
    tb->reset();

    tb->m_core->reset = 1;

    tb->m_core->level = 0;
    tb->tick();
    tb->tick();

    tb->m_core->level = 1;
    tb->tick();

    tb->m_core->level = 0;
    tb->tick();

    exit(EXIT_SUCCESS);
}
