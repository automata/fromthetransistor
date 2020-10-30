module control_unit(
    input wire clk, reset,
    input reg [7:0] IR,
    input reg [7:0] CCR,
    output reg IR_LOAD,
    output reg CCR_LOAD,
    output reg MAR_LOAD,
    output reg PC_LOAD,
    output reg PC_INC,
    output reg A_LOAD,
    output reg B_LOAD,
    output reg ALU_SEL,
    output reg FROM_MEMORY_SEL,
    output reg TO_MEMORY_SEL,
    output reg write
);
endmodule
