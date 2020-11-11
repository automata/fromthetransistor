#pragma once

#include "verilated.h"
#include <verilated_vcd_c.h>

template<class Module>
class Testbench {
 public:
    unsigned long m_tickcount;
    Module* m_core;
    VerilatedVcdC* m_trace;

    Testbench(): m_tickcount(1l) {
        m_core = new Module;
        Verilated::traceEverOn(true); // enable wave tracing
    }

    ~Testbench() {
        if (m_trace) {
            m_trace->close();
            m_trace = NULL;
        }

        delete m_core;
        m_core = NULL;
    }

    void set_trace(const char* vcdname) {
        if (!m_trace) {
            m_trace = new VerilatedVcdC;
            m_core->trace(m_trace, 99); // LAAARGE tracing depth
            m_trace->open(vcdname);
        }
    }

    void reset() {
        m_core->reset = 0;
        m_core->eval();
        m_core->reset = 1;
    }

    void tick() {
        m_tickcount++;

        // make sure any combinatorial logic depending on inputs
        // that may have changed before we called tick() has settled
        // before the rising edge of the clock
        m_core->clk = 0;
        m_core->eval();
        if (m_trace) {
            m_trace->dump(10 * m_tickcount - 2);
        }

        // toggle the clock
        // rising edge
        m_core->clk = 1;
        m_core->eval();
        if (m_trace) {
            m_trace->dump(10 * m_tickcount);
        }

        // falling edge
        m_core->clk = 0;
        m_core->eval();
        if (m_trace) {
            m_trace->dump(10 * m_tickcount + 5); // write on cycle of dump data; give ui time
            m_trace->flush(); // flush to file
        }
    }

    bool done() {
        return Verilated::gotFinish();
    }
};
