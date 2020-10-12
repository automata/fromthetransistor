module decoder (input wire A, B, output wire F3, F2, F1, F0);
    assign F0 = ~A & ~B;
    assign F1 = ~A & B;
    assign F2 = A & ~B;
    assign F3 = A & B;
endmodule

/* One hot decoder
A B | F3 F2 F1 F0
0 0 |  0  0  0  1
0 1 |  0  0  1  0
1 0 |  0  1  0  0
1 1 |  1  0  0  0
*/
