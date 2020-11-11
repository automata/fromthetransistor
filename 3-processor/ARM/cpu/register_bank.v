module register_bank #(parameter n = 32) (
    input wire clk,
    input wire reset,
    input wire write, // write/read to register?
    input wire [4:0] write_sel,  // which register to write to
    input wire [31:0] write_register_in,
    input integer read_sel_1, // which register to read from
    input integer read_sel_2, // which register to read from
    output reg [31:0] read_register_out_1,
    output reg [31:0] read_register_out_2
);

    reg [31:0] register_data_in [0:n - 1];
    reg [31:0] register_data_out [0:n - 1];

    genvar i;
    generate
        for (i = 0; i < n; i++)
            register registers(
                .clk(clk),
                .reset(reset),
                .write(write),
                .data_in(register_data_in[i]),
                .data_out(register_data_out[i])
            );
    endgenerate

    always @ (read_sel_1)
        for (int j = 0; j < n; j++)
            if (read_sel_1 == j)
                read_register_out_1 = register_data_out[j];


    always @ (read_sel_2)
        for (int j = 0; j < n; j++)
            if (read_sel_2 == j)
                read_register_out_2 = register_data_out[j];

    always @ (write_sel)
        if (write)
            register_data_in[write_sel] = write_register_in;

endmodule
