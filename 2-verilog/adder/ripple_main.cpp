#include "verilated.h"

#include "Vripple.h"

#include <verilated_vcd_c.h> // for tracing

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

Vripple *ripple;

int tick = 0;

char* nice_binary(int num) {
    int nobits = floor(log2(num)) + 1; // fails for 0; dont't fall back on it, rather reverse

    char* cp = (char*) malloc(nobits + 1);

    int ix = 0;
    for (; num > 0; num /= 2) cp[ix++] = '0' + (num % 2);
    cp[ix] = '\0';

    for (int i = 0; i < ix / 2; i++) {
        int temp = cp[i];
        cp[i] = cp[ix - i - 1];
        cp[ix - i - 1] = temp;
    }

    return cp;
}

void onerun(int a, int b) {
    ripple->A = a;
    ripple->B = b;
    ripple->eval();
    printf("%s\n%s\n-------\n%s\n", nice_binary(a), nice_binary(b), nice_binary(ripple->Sum));
    printf("%d + %d = %d\n", a, b, ripple->Sum);
    tick++;
}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    ripple = new Vripple;

    int a = 0b001110;
    int b = 0b111111;
    onerun(a, b);

    printf("%d ticks elapsed\n", tick);

    delete ripple;

    exit(EXIT_SUCCESS);
}
