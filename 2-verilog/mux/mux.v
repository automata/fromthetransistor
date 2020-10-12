// 4 to 1 mux
module mux (input wire [3:0] in, input wire [1:0] sel, output wire out);
    assign out =
        (sel == 2'b00) ? in[0] :
        (sel == 2'b01) ? in[1] :
        (sel == 2'b10) ? in[2] :
        (sel == 2'b11) ? in[3] :
        1'bX; // high impedance output i.e. no current running through this wire
endmodule

/* One hot decoder
A B | F3 F2 F1 F0
0 0 |  0  0  0  1
0 1 |  0  0  1  0
1 0 |  0  1  0  0
1 1 |  1  0  0  0
*/
