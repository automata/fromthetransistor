#include "Vblinking.h"
#include "verilated.h"

int main(int argc, char** argv, char** env)
{
  Verilated::commandArgs(argc, argv);
  Vblinking* top = new Vblinking;
  while (!Verilated::gotFinish())
  {
    top->eval();
  }
  delete top;
  exit(0);
}