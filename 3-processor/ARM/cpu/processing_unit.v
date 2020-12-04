module processing_unit(
    input wire clk,
    input wire reset,
    input wire pc_increment_trigger,
    input wire ir_latch_trigger,
    input wire address_latch_trigger,
    output logic ir_latch_result,
    input wire [31:0] din, // data from the memory to the processor
    output logic [31:0] dout, // data from the processor to the memory
);
    /* ************************************** */
    /* Processing Unit modules instantiations */
    /* ************************************** */
    logic [31:0] address_reg; // holds the address to fetch from in memory


    logic reg_write_enable;
    logic [4:0] reg_write_index, reg_read_index_1, reg_read_index_2;
    logic [31:0] reg_data_in, reg_data_out_1, reg_data_out_2;

    register_bank _register_bank(
        .clk            (clk),
        .reset          (reset),
        .write_enable   (reg_write_enable),
        .write_index    (reg_write_index),
        .data_in        (reg_data_in),
        .read_index_1   (reg_read_index_1),
        .read_index_2   (reg_read_index_2),
        .data_out_1     (reg_data_out_1),
        .data_out_2     (reg_data_out_2)
    );


    logic carry_in;
    logic [3:0] opcode, alu_nzvc;
    logic [31:0] alu_a, alu_b;
    logic signed [31:0] alu_result;

    alu _alu(
        .opcode     (opcode),
        .a          (alu_a),
        .b          (alu_b),
        .carry_in   (alu_carry_in),
        .result     (alu_result),
        .nzvc       (alu_nzvc)
    );


    logic [31:0] multiplier_a, multiplier_b;
    logic signed [31:0] multiplier_result;

    multiplier _multiplier(
        .clk    (clk),
        .a      (multiplier_a),
        .b      (multiplier_b),
        .result (multiplier_result)
    );


    logic [4:0] shifter_shift;
    logic [31:0] shifter_data_in, shifter_data_out;

    barrel_shifter _barrel_shifter(
        .data_in(shifter_data_in),
        .shift(shifter_shift),
        .data_out(shifter_data_out)
    );

endmodule
