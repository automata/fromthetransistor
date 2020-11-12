module barrel_shifter( // rotates right by **select** bits
    input wire [31:0] in,
    input wire [4:0] select,
    output reg [31:0] out
);

    wire [63:0] double_in = {in, in};

    assign out = double_in[select + 31-:32];

endmodule
