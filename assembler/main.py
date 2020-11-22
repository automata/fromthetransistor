#!/usr/bin/python3

import struct

'''
TODO parse example.s

Useful resources:

# https://www.csie.ntu.edu.tw/~cyy/courses/assembly/10fall/lectures/handouts/lec09_ARMisa.pdf
# https://iitd-plos.github.io/col718/ref/arm-instructionset.pdf

'''

if __name__ == "__main__":
  data = [0.1111,0.31313]
  obj = struct.pack('ff', *data)

  with open('binary', 'w+b') as f:
      f.write(obj)

  print(f"Hey! {f.closed}")
