module glitch_mux(
    input wire in0, in1, sel,
    output wire out
);
    wire not_sel;
    wire and_out1, and_out2;

    assign not_sel = ~sel;
    assign and_out1 = not_sel & in0;
    assign and_out2 = sel & in1;

    assign out = and_out1 | and_out2;

endmodule
