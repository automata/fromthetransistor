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
#include "Valu.h"

bool is_negative(int byte) {
  char res = byte & 0b01000;
  if (res == 0) return false;
  return true;
}

bool is_zero(unsigned char byte) {
  char res = byte & 0b00100;
  if (res == 0) return false;
  return true;
}

bool is_overflow(unsigned char byte) {
  char res = byte & 0b00010;
  if (res == 0) return false;
  return true;
}

bool is_carry(unsigned char byte) {
  char res = byte & 0b00001;
  if (res == 0) return false;
  return true;
}

char to_twoc(int num) { // convert to two's complement
  bool negative = num < 0;
  if (negative) num = -num;


  char res = 0;
  unsigned char shift = 0;
  while (num > 0) {
    if (num % 2 == 1) res |= ((unsigned char) 1 << shift);
    num /= 2;
    shift++;
  }

  if (negative) res = ~res + 1;

  return res;
}

Valu* alu;

typedef void (*optest)();
static std::vector<optest> tests = {
  [] () {
    int A = 1;
    int B = 1;

    printf("\033[0;33m");
    printf("test:::: %d + %d\n", A, B);
    printf("\033[0m");

    char tA = to_twoc(A);
    char tB = to_twoc(B);
    char expected = to_twoc(A + B);

    alu->A = tA;
    alu->B = tB;
    alu->SEL = 0b000;

    alu->eval();

    char nzvc = alu->NZVC;
    char result = alu->RESULT;

    assert(expected == result);
    assert(is_negative(nzvc) == false);
    assert(is_zero(nzvc) == false);
    assert(is_overflow(nzvc) == false);
    assert(is_carry(nzvc) == false);
  },
  [] () {
    int A = -127;
    int B = 1;

    printf("\033[0;33m");
    printf("test:::: %d + %d\n", A, B);
    printf("\033[0m");

    char tA = to_twoc(A);
    char tB = to_twoc(B);
    char expected = to_twoc(A + B);

    alu->A = tA;
    alu->B = tB;
    alu->SEL = 0b000;

    alu->eval();

    char nzvc = alu->NZVC;
    char result = alu->RESULT;

    assert(expected == result);
    assert(is_negative(nzvc) == true);
    assert(is_zero(nzvc) == false);
    assert(is_overflow(nzvc) == false);
    assert(is_carry(nzvc) == false);
  },
  [] () {
    int A = 127;
    int B = -127;

    printf("\033[0;33m");
    printf("test:::: %d + %d\n", A, B);
    printf("\033[0m");

    char tA = to_twoc(A);
    char tB = to_twoc(B);
    char expected = to_twoc(A + B);

    alu->A = tA;
    alu->B = tB;
    alu->SEL = 0b000;

    alu->eval();

    char nzvc = alu->NZVC;
    char result = alu->RESULT;

    assert(expected == result);
    assert(is_negative(nzvc) == false);
    assert(is_zero(nzvc) == true);
    assert(is_overflow(nzvc) == false);
    assert(is_carry(nzvc) == true);
  },
  [] () {
    int A = 127;
    int B = 127;

    printf("\033[0;33m");
    printf("test:::: %d + %d\n", A, B);
    printf("\033[0m");

    char tA = to_twoc(A);
    char tB = to_twoc(B);
    char expected = to_twoc(A + B);

    alu->A = tA;
    alu->B = tB;
    alu->SEL = 0b000;

    alu->eval();

    char nzvc = alu->NZVC;
    char result = alu->RESULT;

    assert(is_overflow(nzvc) == true);
  },
  [] () {
    int A = 127;
    int B = 127;

    printf("\033[0;33m");
    printf("test:::: %d - %d\n", A, B);
    printf("\033[0m");

    char tA = to_twoc(A);
    char tB = to_twoc(B);
    char expected = to_twoc(A - B);

    alu->A = tA;
    alu->B = tB;
    alu->SEL = 0b001;

    alu->eval();

    char nzvc = alu->NZVC;
    char result = alu->RESULT;

    assert(expected == result);
    assert(is_negative(nzvc) == false);
    assert(is_zero(nzvc) == true);
    assert(is_overflow(nzvc) == false);
    assert(is_carry(nzvc) == false);
  },
  [] () {
    int A = -128;
    int B = 1;

    printf("\033[0;33m");
    printf("test:::: %d - %d\n", A, B);
    printf("\033[0m");

    char tA = to_twoc(A);
    char tB = to_twoc(B);
    char expected = to_twoc(A - B);

    alu->A = tA;
    alu->B = tB;
    alu->SEL = 0b001;

    alu->eval();

    char nzvc = alu->NZVC;
    char result = alu->RESULT;

    assert(is_overflow(nzvc) == true);
  },
  [] () {
    int A = 1;
    int B = -127;

    printf("\033[0;33m");
    printf("test:::: %d - %d\n", A, B);
    printf("\033[0m");

    char tA = to_twoc(A);
    char tB = to_twoc(B);
    char expected = to_twoc(A - B);

    alu->A = tA;
    alu->B = tB;
    alu->SEL = 0b001;

    alu->eval();

    char nzvc = alu->NZVC;
    char result = alu->RESULT;

    assert(is_overflow(nzvc) == true);
  },
  [] () {
    int A = -123;
    int B = -3;

    printf("\033[0;33m");
    printf("test:::: %d - %d\n", A, B);
    printf("\033[0m");

    char tA = to_twoc(A);
    char tB = to_twoc(B);
    char expected = to_twoc(A - B);

    alu->A = tA;
    alu->B = tB;
    alu->SEL = 0b001;

    alu->eval();

    char nzvc = alu->NZVC;
    char result = alu->RESULT;

    assert(expected == result);
    assert(is_negative(nzvc) == true);
    assert(is_zero(nzvc) == false);
    assert(is_overflow(nzvc) == false);
    assert(is_carry(nzvc) == true); // don't really get why
  },
  [] () {
    int A = 0;

    printf("\033[0;33m");
    printf("test:::: %d++\n", A);
    printf("\033[0m");

    char tA = to_twoc(A);
    char expected = to_twoc(A + 1);

    alu->A = tA;
    alu->SEL = 0b100;

    alu->eval();

    char nzvc = alu->NZVC;
    char result = alu->RESULT;

    assert(expected == result);
    assert(is_negative(nzvc) == false);
    assert(is_zero(nzvc) == false);
    assert(is_overflow(nzvc) == false);
    assert(is_carry(nzvc) == false);
  },
  [] () {
    int A = 127;

    printf("\033[0;33m");
    printf("test:::: %d++\n", A);
    printf("\033[0m");

    char tA = to_twoc(A);
    char expected = to_twoc(A + 1);

    alu->A = tA;
    alu->SEL = 0b100;

    alu->eval();

    char nzvc = alu->NZVC;
    char result = alu->RESULT;

    assert(is_overflow(nzvc) == true);
  },
  [] () {
    int B = 0;

    printf("\033[0;33m");
    printf("test:::: %d++\n", B);
    printf("\033[0m");

    char tB = to_twoc(B);
    char expected = to_twoc(B + 1);

    alu->B = tB;
    alu->SEL = 0b101;

    alu->eval();

    char nzvc = alu->NZVC;
    char result = alu->RESULT;

    assert(expected == result);
    assert(is_negative(nzvc) == false);
    assert(is_zero(nzvc) == false);
    assert(is_overflow(nzvc) == false);
    assert(is_carry(nzvc) == false);
  },
  [] () {
    int B = 127;

    printf("\033[0;33m");
    printf("test:::: %d++\n", B);
    printf("\033[0m");

    char tB = to_twoc(B);
    char expected = to_twoc(B + 1);

    alu->B = tB;
    alu->SEL = 0b101;

    alu->eval();

    char nzvc = alu->NZVC;
    char result = alu->RESULT;

    assert(is_overflow(nzvc) == true);
  },
  [] () {
    int A = 0;

    printf("\033[0;33m");
    printf("test:::: %d--\n", A);
    printf("\033[0m");

    char tA = to_twoc(A);
    char expected = to_twoc(A - 1);

    alu->A = tA;
    alu->SEL = 0b110;

    alu->eval();

    char nzvc = alu->NZVC;
    char result = alu->RESULT;

    assert(expected == result);
    assert(is_negative(nzvc) == true);
    assert(is_zero(nzvc) == false);
    assert(is_overflow(nzvc) == false);
    assert(is_carry(nzvc) == true);
  },
  [] () {
    int A = -128;

    printf("\033[0;33m");
    printf("test:::: %d--\n", A);
    printf("\033[0m");

    char tA = to_twoc(A);
    char expected = to_twoc(A - 1);

    alu->A = tA;
    alu->SEL = 0b110;

    alu->eval();

    char nzvc = alu->NZVC;
    char result = alu->RESULT;

    assert(is_overflow(nzvc) == true);
  },
  [] () {
    int B = 0;

    printf("\033[0;33m");
    printf("test:::: %d--\n", B);
    printf("\033[0m");

    char tB = to_twoc(B);
    char expected = to_twoc(B - 1);

    alu->B = tB;
    alu->SEL = 0b111;

    alu->eval();

    char nzvc = alu->NZVC;
    char result = alu->RESULT;

    assert(expected == result);
    assert(is_negative(nzvc) == true);
    assert(is_zero(nzvc) == false);
    assert(is_overflow(nzvc) == false);
    assert(is_carry(nzvc) == true); // all 0s are negated
  },
  [] () {
    int B = -128;

    printf("\033[0;33m");
    printf("test:::: %d--\n", B);
    printf("\033[0m");

    char tB = to_twoc(B);
    char expected = to_twoc(B - 1);

    alu->B = tB;
    alu->SEL = 0b111;

    alu->eval();

    char nzvc = alu->NZVC;
    char result = alu->RESULT;

    assert(is_overflow(nzvc) == true);
  },
};

int main(int argc, char** argv) {
  Verilated::commandArgs(argc, argv);
  alu = new Valu;

  for (auto& test : tests) test();

  delete alu;
  alu = NULL;

  exit(EXIT_SUCCESS);
}
