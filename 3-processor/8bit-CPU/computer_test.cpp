#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <iostream>
#include <vector>

#include "verilated.h"
#include "testbench.h"
#include "Vcomputer.h"

Testbench<Vcomputer> *tb;

void tick() {
  tb->tick();
  printf("\n");
}

void ldx_imm() {  // lda or ldb (7 states, so 8 cycles needed to arrive into init <S_FETCH_0> state)
  tick();
  tick();
  tick();
  tick();
  tick();
  tick();
  tick();
  tick();
}

void ldx_dir() { // lda or ldb (8 states, so 9 cycles needed to arrive into init <S_FETCH_0> state)
  tick();
  tick();
  tick();
  tick();
  tick();
  tick();
  tick();
  tick();
  tick();
}

void stx_dir() { // sta or stb (8 states, so 9 cycles needed to arrive into init <S_FETCH_0> state)
  tick();
  tick();
  tick();
  tick();
  tick();
  tick();
  tick();
  tick();
  tick();
}


int main(int argc, char** argv) {
  // program is in ROM
  Verilated::commandArgs(argc, argv);

  tb = new Testbench<Vcomputer>;

  tb->reset();

  ldx_dir();
  stx_dir();

  exit(EXIT_SUCCESS);
}
