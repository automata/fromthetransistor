module encoder (input wire [3:0] in, output wire [1:0] out); // 4 to 2 decoder
    // following the table
    assign out[0] = in[3] | in[1];
    assign out[1] = in[3] | in[2];
endmodule

/* One hot decoder/encoder
A B | F3 F2 F1 F0
0 0 |  0  0  0  1
0 1 |  0  0  1  0
1 0 |  0  1  0  0
1 1 |  1  0  0  0
*/
