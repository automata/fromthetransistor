#include "verilated.h"
#include "Valu.h"

#include <cstdio>
#include <cstdlib>
#include <cassert>

Valu* tb;

void test_and() {
    tb->opcode = 0b0000;
    tb->carry_in = 0;

    tb->a = 1;
    tb->b = 1;
    tb->eval();
    assert(tb->res == 1);
    assert(tb->nzvc == 0b0000);

    tb->a = 2;
    tb->b = 1;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b0100);

    tb->a = -1;
    tb->b = 3;
    tb->eval();
    assert(tb->res == 3);
    assert(tb->nzvc == 0b0000);

    tb->a = -3;
    tb->b = -5;
    tb->eval();
    assert(tb->res == -7);
    assert(tb->nzvc == 0b1000);

    puts("AND PASSED.");
}

void test_eor() {
    tb->opcode = 0b0001;
    tb->carry_in = 0;

    tb->a = 1;
    tb->b = 1;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b0100);

    tb->a = -1;
    tb->b = 1;
    tb->eval();
    assert(tb->res == -2);
    assert(tb->nzvc == 0b1000);

    tb->a = -1;
    tb->b = -6;
    tb->eval();
    assert(tb->res == 5);
    assert(tb->nzvc == 0b0000);

    puts("EOR PASSED.");
}

void test_sub() {
    tb->opcode = 0b0010;
    tb->carry_in = 0;

    tb->a = -1;
    tb->b = -1;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b0101);

    tb->a = -3;
    tb->b = 4;
    tb->eval();
    assert(tb->res == -7);
    assert(tb->nzvc == 0b1001);

    tb->a = -2147483648;
    tb->b = 0;
    tb->eval();
    assert(tb->nzvc == 0b1000);

    tb->a = -2147483648;
    tb->b = 1;
    tb->eval();
    assert(tb->nzvc == 0b0011);

    puts("SUB PASSED.");
}

void test_rsb() {
    tb->opcode = 0b0011;
    tb->carry_in = 0;

    tb->a = -1;
    tb->b = -1;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b0101);

    tb->a = -3;
    tb->b = 4;
    tb->eval();
    assert(tb->res == 7);
    assert(tb->nzvc == 0b0000);

    puts("RSB PASSED.");
}

void test_add() {
    tb->opcode = 0b0100;
    tb->carry_in = 0;

    tb->a = -1;
    tb->b = -1;
    tb->eval();
    assert(tb->res == -2);
    assert(tb->nzvc == 0b1001);

    tb->a = -3;
    tb->b = 4;
    tb->eval();
    assert(tb->res == 1);
    assert(tb->nzvc == 0b0001);

    tb->a = 3;
    tb->b = 4;
    tb->eval();
    assert(tb->res == 7);
    assert(tb->nzvc == 0b0000);

    tb->a = -1;
    tb->b = 1;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b0101);

    tb->a = 2147483647;
    tb->b = 1;
    tb->eval();
    assert(tb->nzvc == 0b1010);

    puts("ADD PASSED.");
}

void test_cmp() {
    tb->opcode = 0b1010;
    tb->carry_in = 0;

    tb->a = -1;
    tb->b = -1;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b0101);

    tb->a = -3;
    tb->b = 4;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b1001);

    tb->a = -2147483648;
    tb->b = 0;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b1000);

    tb->a = -2147483648;
    tb->b = 1;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b0011);

    puts("CMP PASSED.");
}

void test_cmn() {
    tb->opcode = 0b1011;
    tb->carry_in = 0;

    tb->a = -1;
    tb->b = -1;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b1001);

    tb->a = -3;
    tb->b = 4;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b0001);

    tb->a = 3;
    tb->b = 4;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b0000);

    tb->a = -1;
    tb->b = 1;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b0101);

    tb->a = 2147483647;
    tb->b = 1;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b1010);

    puts("CMN PASSED.");
}

void test_adc() {
    tb->opcode = 0b0101;
    tb->carry_in = 1;

    tb->a = 1;
    tb->b = 1;
    tb->eval();
    assert(tb->res == 3);
    assert(tb->nzvc == 0b0000);

    puts("ADC PASSED.");
}

void test_sbc() {
    tb->opcode = 0b0110;
    tb->carry_in = 0;

    tb->a = 1;
    tb->b = 1;
    tb->eval();
    assert(tb->res == -1);
    assert(tb->nzvc == 0b1000);

    puts("SBC PASSED.");
}

void test_tst() {
    tb->opcode = 0b1000;
    tb->carry_in = 0;
    tb->res = 0;

    tb->a = 1;
    tb->b = 1;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b0000);

    tb->a = 2;
    tb->b = 1;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b0100);

    tb->a = -1;
    tb->b = 3;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b0000);

    tb->a = -3;
    tb->b = -5;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b1000);

    puts("TST PASSED.");
}

void test_teq() {
    tb->opcode = 0b1001;
    tb->carry_in = 0;

    tb->a = 1;
    tb->b = 1;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b0100);

    tb->a = -1;
    tb->b = 1;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b1000);

    tb->a = -1;
    tb->b = -6;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b0000);

    puts("TEQ PASSED.");
}

void test_orr() {
    tb->opcode = 0b1100;
    tb->carry_in = 0;

    tb->a = 1;
    tb->b = 1;
    tb->eval();
    assert(tb->res == 1);
    assert(tb->nzvc == 0b0000);

    tb->a = 2;
    tb->b = 1;
    tb->eval();
    assert(tb->res == 3);
    assert(tb->nzvc == 0b0000);

    tb->a = -1;
    tb->b = 3;
    tb->eval();
    assert(tb->res == -1);
    assert(tb->nzvc == 0b1000);

    tb->a = 0;
    tb->b = 0;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b0100);

    puts("ORR PASSED.");
}

void test_mov() {
    tb->opcode = 0b1101;
    tb->carry_in = 0;

    tb->b = 45;
    tb->eval();
    assert(tb->res == 45);
    assert(tb->nzvc == 0b0000);

    tb->b = 0;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b0100);

    tb->b = -1;
    tb->eval();
    assert(tb->nzvc == 0b1000);

    puts("MOV PASSED.");
}

void test_bic() {
    tb->opcode = 0b1110;
    tb->carry_in = 0;

    tb->a = 3;
    tb->b = 0;
    tb->eval();
    assert(tb->res == 3);
    assert(tb->nzvc == 0b0000);

    tb->a = -1;
    tb->b = -1;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b0100);

    puts("BIC PASSED.");
}

void test_mvn() {
    tb->opcode = 0b1111;
    tb->carry_in = 0;

    tb->b = -1;
    tb->eval();
    assert(tb->res == 0);
    assert(tb->nzvc == 0b0100);

    puts("MVN PASSED.");
}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    tb = new Valu;

    test_and();
    test_eor();
    test_sub();
    test_rsb();
    test_add();
    test_cmp();
    test_cmn();
    test_adc();
    test_sbc();
    test_tst();
    test_teq();
    test_orr();
    test_mov();
    test_bic();
    test_mvn();

    delete tb;
    tb = NULL;

    exit(EXIT_SUCCESS);
}
