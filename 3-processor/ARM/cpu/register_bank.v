/*
* 0..15: r0..r15
* 16: cpsr
* 17, 18, 19: r13_svc, r14_svc, spsr_svc (banked)
* 20, 21, 22: r13_abt, r14_abt, spsr_abt (banked)
* 23, 24, 25: r13_irq, r14_irq, spsr_irq (banked)
* 26, 27, 28: r13_und, r14_und, spsr_und (banked)
*/
module register_bank(
    input wire clk,
    input wire reset,
    input wire write_enable,        // write/read register?
    input wire [4:0] write_index,     // which register to write to
    input wire [31:0] data_in,       // what to write to register
    input wire [4:0] read_index_1,       // which register to read from
    input wire [4:0] read_index_2,       // which register to read from
    output logic [31:0] data_out_1,
    output logic [31:0] data_out_2
);
    localparam N = 29;

    logic [31:0] reg_data_in  [0:N - 1];
    logic [31:0] reg_data_out [0:N - 1];

    genvar i;
    generate
        for (i = 0; i < N; i++)
            register registers(
                .clk            (clk),
                .reset          (reset),
                .write_enable   (write_enable),
                .data_in        (reg_data_in[i]),
                .data_out       (reg_data_out[i])
            );
    endgenerate

    always_comb begin
        data_out_1 = reg_data_out[read_index_1];
    end

    always_comb begin
        data_out_2 = reg_data_out[read_index_2];
    end

    always_comb begin
        if (write_enable)
            reg_data_in[write_index] = data_in;
    end

endmodule
