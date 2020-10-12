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
        delete m_core;
        m_core = NULL;
    }

    void open_trace(const char* vcdname) {
        if (!m_trace) {
            m_trace = new VerilatedVcdC;
            m_core->trace(m_trace, 99); // LAAARGE tracing depth
            m_trace->open(vcdname);
        }
    }

    void close_trace() {
        if (m_trace) {
            m_trace->close();
            m_trace = NULL;
        }
    }

    void reset() {
        m_core->i_reset = 1;
        m_core->eval();
        m_core->i_reset = 0;
    }

    void tick() {
        m_tickcount++;

        // make sure any combinatorial logic depending on inputs
        // that may have changed before we called tick() has settled
        // before the rising edge of the clock
        m_core->i_clk = 0;
        m_core->eval();
        if (m_trace) {
            m_trace->dump(10 * m_tickcount - 2);
        }

        // toggle the clock
        // rising edge
        m_core->i_clk = 1;
        m_core->eval();
        if (m_trace) {
            m_trace->dump(10 * m_tickcount);
        }

        // falling edge
        m_core->i_clk = 0;
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
