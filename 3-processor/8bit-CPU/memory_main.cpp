#include "verilated.h"
#include "Vmemory.h"
#include "testbench.h"

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <random>

// rng
std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> dist(0, 255);

uint8_t get_rand() { return static_cast<uint8_t>(dist(rng)); }

Testbench<Vmemory>* tb;

uint8_t get_rw(uint8_t address) {
    if (address < 128 || address > 223) {
        puts("invalid address");
        exit(1);
    }

    tb->m_core->address = address;
    tb->m_core->write = 0;
    tb->tick();
    return tb->m_core->data_out;
}

void set_rw(uint8_t address, uint8_t value) {
    if (address < 128 || address > 223) {
        puts("invalid address");
        exit(1);
    }

    tb->m_core->address = address;
    tb->m_core->data_in = value;
    tb->m_core->write = 1;
    tb->tick();
}

void test_rw() {
    for (int i = 128; i < 224; i++) {
        int value = get_rw(i);
        assert(value == 0);
    }

    for (int i = 128; i < 224; i++) {
        uint8_t value = get_rand();
        set_rw(i, value);
        auto ret = get_rw(i);
        assert(ret == value);
    }
    puts("done testing RW memory");
}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    tb = new Testbench<Vmemory>;

    tb->reset();
    test_rw();

    tb->set_trace("memory_trace.vcd");
    tb->reset();

    exit(EXIT_SUCCESS);
}
