module cpu(
    input wire clk, reset,
    input wire [7:0] from_memory,   // data bus from memory
    output reg [7:0] to_memory,     // data bus to memory
    output reg [7:0] address,       // address bus to memory (index into memory)
    output reg write                // can write to memory?
);

    always @ (posedge clk or negedge reset)
    begin
        // the control unit is called directly from the data_path
        // as it is the main FSM that controls the flow of data in the cpu
        data_path dp(
            .clk            (clk),
            .reset          (reset),
            .from_memory    (from_memory),
            .to_memory      (to_memory)
            .address        (address)
        );

        // the control unit contains a bunch of Moore FSMs that control the data path
        control_unit _control(
            .clk                    (clk),                  // input (from cpu)
            .reset                  (reset),                // input (from cpu)
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
    end

endmodule;
