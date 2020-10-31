module cpu(
    input wire clk, reset,
    input wire [7:0] from_memory,   // data bus from memory
    output reg [7:0] to_memory,     // data bus to memory
    output reg [7:0] address,       // address bus to memory (index into memory)
    output reg write                // can write to memory?
);

    // nets through which the data_path and control_unit communicate
    reg [7:0] IR;
    reg [3:0] CCR;
    reg IR_LOAD;
    reg CCR_LOAD;
    reg MAR_LOAD;
    reg PC_LOAD;
    reg PC_INC;
    reg A_LOAD;
    reg B_LOAD;
    reg [2:0] ALU_SEL;
    reg [1:0] FROM_MEMORY_BUS_SEL;
    reg [1:0] TO_MEMORY_BUS_SEL;

    // the control unit is called directly from the data_path
    // as it is the main FSM that controls the flow of data in the cpu
    data_path dp(
        .clk                    (clk),
        .reset                  (reset),
        .from_memory            (from_memory),
        .IR_LOAD                (IR_LOAD),              // input
        .CCR_LOAD               (CCR_LOAD),             // input
        .MAR_LOAD               (MAR_LOAD),             // input
        .PC_LOAD                (PC_LOAD),              // input
        .PC_INC                 (PC_INC),               // input
        .A_LOAD                 (A_LOAD),               // input
        .B_LOAD                 (B_LOAD),               // input
        .ALU_SEL                (ALU_SEL),              // input
        .FROM_MEMORY_BUS_SEL    (FROM_MEMORY_BUS_SEL),  // input
        .TO_MEMORY_BUS_SEL      (TO_MEMORY_BUS_SEL),    // input
        .IR                     (IR),                   // output
        .CCR                    (CCR),                  // output
        .to_memory              (to_memory),            // output
        .address                (address)               // output
    );

    // the control unit contains a bunch of Moore FSMs that control the data path
    control_unit _control(
        .clk                    (clk),                  // input
        .reset                  (reset),                // input
        .IR                     (IR),                   // input
        .CCR                    (CCR),                  // input
        .IR_LOAD                (IR_LOAD),              // output
        .CCR_LOAD               (CCR_LOAD),             // output
        .MAR_LOAD               (MAR_LOAD),             // output
        .PC_LOAD                (PC_LOAD),              // output
        .PC_INC                 (PC_INC),               // output
        .A_LOAD                 (A_LOAD),               // output
        .B_LOAD                 (B_LOAD),               // output
        .ALU_SEL                (ALU_SEL),              // output
        .FROM_MEMORY_BUS_SEL    (FROM_MEMORY_BUS_SEL),  // output
        .TO_MEMORY_BUS_SEL      (TO_MEMORY_BUS_SEL),    // output
        .write                  (write)                 // output
    );

endmodule;
