module glitch_flop(
    input wire clk, din,
    output wire dout
);
    assign dout = clk ^ din;
endmodule
