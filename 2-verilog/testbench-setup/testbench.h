#pragma once

#include "verilated.h"

template<class Module>
class Testbench {
 public:
    unsigned long m_tickcount;
    Module* m_core;

    Testbench(): m_tickcount(0l) {
        m_core = new Module();

        // make sure any combinatorial logic depending on inputs
        // that may have changed before we called tick() has settled
        // before the rising edge of the clock
        m_core->i_clk = 0;
        m_core->eval();
    }

    ~Testbench() {
        delete m_core;
        m_core = NULL;
    }

    void reset() {
        m_core->i_reset = 1;
        m_core->eval();
        m_core->i_reset = 0;
    }
    
    void tick() {
        m_tickcount++;

        // toggle the clock
        // rising edge
        m_core->i_clk = 1;
        m_core->eval();

        // falling edge
        m_core->i_clk = 0;
        m_core->eval();
    }

    bool done() {
        return Verilated::gotFinish();
    }
};
