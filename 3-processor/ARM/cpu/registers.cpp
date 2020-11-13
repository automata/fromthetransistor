#include "verilated.h"
#include "Vregister_bank.h"
#include "testbench.h"

#include <cstdio>
#include <cstdlib>

Testbench<Vregister_bank>* tb;

void set_value(int index, int value) {
    tb->m_core->write_enable = 1;
    tb->m_core->write_index = index;
    tb->m_core->data_in = value;
    tb->tick();
}

int get_value_1(int index) {
    tb->m_core->write_enable = 0;
    tb->m_core->read_index_1 = index;
    tb->tick();
    return tb->m_core->data_out_1;
}

int get_value_2(int index) {
    tb->m_core->write_enable = 0;
    tb->m_core->read_index_2 = index;
    tb->tick();
    return tb->m_core->data_out_2;
}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    tb = new Testbench<Vregister_bank>;

    tb->reset();

    int value = 1;
    set_value(0, value);
    for (int i = 1; i < 29; i++, value += 10) {
        set_value(i, value);
        printf("r1 = %d :: r2 = %d\n", get_value_1(i - 1), get_value_2(i));
    }

    delete tb;
    tb = NULL;

    exit(EXIT_SUCCESS);
}
