/*
* 0..15: r0..r15
* 16: cpsr
* 17, 18, 19: r13_svc, r14_svc, spsr_svc (banked)
* 20, 21, 22: r13_abt, r14_abt, spsr_abt (banked)
* 23, 24, 25: r13_irq, r14_irq, spsr_irq (banked)
* 26, 27, 28: r13_und, r14_und, spsr_und (banked)
*/
module register_bank #(parameter N = 29) (
    input wire clk,
    input wire reset,
    input wire write_enable,        // write/read register?
    input wire [4:0] write_sel,     // which register to write to
    input wire [31:0] reg_in,       // what to write to register
    input integer read_sel_1,       // which register to read from
    input integer read_sel_2,       // which register to read from
    output reg [31:0] reg_out_1,
    output reg [31:0] reg_out_2
);
    reg [31:0] data_in [0:N - 1], data_out [0:N - 1];

    genvar i;
    generate
        for (i = 0; i < N; i++)
            register registers(
                .clk(clk),
                .reset(reset),
                .write_enable(write_enable),
                .data_in(data_in[i]),
                .data_out(data_out[i])
            );
    endgenerate

    always @ (read_sel_1)
        for (int j = 0; j < N; j++)
            if (read_sel_1 == j)
                reg_out_1 = data_out[j];


    always @ (read_sel_2)
        for (int j = 0; j < N; j++)
            if (read_sel_2 == j)
                reg_out_2 = data_out[j];

    always @ (write_sel)
        if (write_enable)
            data_in[write_sel] = reg_in;

endmodule
