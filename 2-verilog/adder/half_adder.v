`timescale 1ns/1ps
module half_adder(output Sum, Cout, input wire A, B);
    xor U1 (Sum, A, B);
    and U2 (Cout, A, B);
endmodule

/*
a b | s c
0 0 | 0 0
0 1 | 1 0
1 0 | 1 0
1 1 | 0 1
*/
