// rotates <data_in> right by <shift> logics
module barrel_shifter(
    input wire [31:0] data_in,
    input wire [4:0] shift,
    output logic [31:0] data_out
);
    logic [63:0] double_data_in = {data_in, data_in};

    // hack: equivalent to double_in[select + 31:select]
    assign data_out = double_data_in[shift + 31-:32];
endmodule
