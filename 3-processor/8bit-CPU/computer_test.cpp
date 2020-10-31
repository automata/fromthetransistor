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

int main(int argc, char** argv) {
  Verilated::commandArgs(argc, argv);

  tb = new Testbench<Vcomputer>;

  exit(EXIT_SUCCESS);
}
