`timescale 1ns/1ps
module full_adder(output wire Sum, Cout, input wire A, B, Cin);
    /* this whole things works without any delays on the second
    * call of half_adder (U2) since the half_adder itself uses gate-level
    * primitives which in themselves are just circuits. So here
    * you simply connect these two circuits with their wires and get a bigger
    * circuit which is again synthesizable since it is made from all
    * gate-level primitives.
    */
    wire HA1_Sum, HA1_Cout, HA2_Cout;
    half_adder U1 (.Sum(HA1_Sum), .Cout(HA1_Cout), .A(A), .B(B));
    half_adder U2 (.Sum(Sum), .Cout(HA2_Cout), .A(HA1_Sum), .B(Cin));

    // this needs to be delayed since everything is concurrent
    or U3 (Cout, HA1_Cout, HA2_Cout);
endmodule

/*
A B C | s c
0 0 0 | 0 0
0 0 1 | 1 0
0 1 0 | 1 0
0 1 1 | 0 1
1 0 0 | 1 0
1 0 1 | 0 1
1 1 0 | 0 1
1 1 1 | 1 1
*/
