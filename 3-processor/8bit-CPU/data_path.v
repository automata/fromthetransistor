module data_path(
    input wire clk, reset,
    input wire [7:0] from_memory,
    output wire [7:0] address, // address to fetch stuff from in memory (contents of MAR)
    output reg [7:0] to_memory // stuff to put into memory at <address>
);
    reg [7:0] ALU_RESULT;
    reg [3:0] NZVC;

    reg [7:0] A;    // A register
    reg [7:0] B;    // B register

    // data path 8-bit buses
    wire [7:0] FROM_MEMORY_BUS;
    wire [7:0] TO_MEMORY_BUS;

    // control_unit contains the FSMs (Moore machines, output encoded in state) that instruct the data path to do stuff
    // inputs: IR, CCR
    // outputs: IR_LOAD, MAR_LOAD, PC_LOAD, PC_INC, A_LOAD, B_LOAD, ALU_SEL, CCR_LOAD, FROM_MEMORY_BUS_SEL, TO_MEMORY_BUS_SEL
    reg [7:0] IR; // IR register; contains content of IR -- input into control_unit (needed for decoding the current instruction)
    wire IR_LOAD; // IR is loading; fetch next program instruction from ROM

    reg [7:0] MAR; // memory address register
    wire MAR_LOAD; // MAR is loading; fetch from memory at the address in MAR, content put into FROM_MEMORY_BUS (data_out in memory.v)

    reg [7:0] PC; // program counter register
    wire PC_LOAD; // PC is loading; loads the PC register with contents from the FROM_MEMORY_BUS
    wire PC_INC; // PC incrementing; increments the PC register to continue execution of program

    wire A_LOAD; // A is loading with contents FROM_MEMORY_BUS
    wire B_LOAD; // B is loading with contents FROM_MEMORY_BUS

    wire [2:0] ALU_SEL; // instruct ALU which operation to perform

    reg [3:0] CCR; // condition coder register (NZVC, Negative, Zero, Overflow, Carry) -- input into control unit
    wire CCR_LOAD; // CCR is loading; sets CCR flags depending on ALU operation output

    wire FROM_MEMORY_BUS_SEL; // multiplexer selector of what gets into FROM_MEMORY_BUS

    wire TO_MEMORY_BUS_SEL; // multiplexer selector of what gets into TO_MEMORY_BUS

    control_unit _control(
        .clk                    (clk),                  // input (from cpu)
        .reset                  (reset),                // input (from cpu)
        .IR                     (IR),                   // input
        .IR_LOAD                (IR_LOAD),              // output
        .MAR_LOAD               (MAR_LOAD),             // output
        .PC_LOAD                (PC_LOAD),              // output
        .PC_INC                 (PC_INC),               // output
        .A_LOAD                 (A_LOAD),               // output
        .B_LOAD                 (B_LOAD),               // output
        .ALU_SEL                (ALU_SEL),              // output
        .CCR                    (CCR),                  // input
        .CCR_LOAD               (CCR_LOAD),             // output
        .FROM_MEMORY_BUS_SEL    (FROM_MEMORY_BUS_SEL),  // output
        .TO_MEMORY_BUS_SEL      (TO_MEMORY_BUS_SEL),    // output
    );


    // -------------------------------------------
    // ------------------ LOGIC ------------------
    // -------------------------------------------

    // ------------------ BUSES ------------------
    always @ (FROM_MEMORY_BUS_SEL, ALU_RESULT, TO_MEMORY_BUS, from_memory)
    begin: __FROM_MEMORY_BUS_MUX
        case (FROM_MEMORY_BUS_SEL)
            2'b00:      FROM_MEMORY_BUS = ALU_RESULT;
            2'b01:      FROM_MEMORY_BUS = TO_MEMORY_BUS;
            2'b10:      FROM_MEMORY_BUS = from_memory;
            default:    FROM_MEMORY_BUS = 8'hXX; // high impedance
        endcase
    end

    always @ (TO_MEMORY_BUS_SEL, PC, A, B)
    begin: __TO_MEMORY_BUS_MUX
        case (TO_MEMORY_BUS_SEL)
            2'b00:      TO_MEMORY_BUS = PC;
            2'b01:      TO_MEMORY_BUS = A;
            2'b10:      TO_MEMORY_BUS = B;
            default:    TO_MEMORY_BUS = 8'hXX; // high impedance
        endcase
    end

    always @ (TO_MEMORY_BUS_SEL, address)
    begin: __TO_MEMORY_OUTPUT
        to_memory = TO_MEMORY_BUS;
        address = MAR;
    end

    // ---------------- REGISTERS ----------------
    // IR flip flops
    always @ (posedge clk or negedge reset)
        if (!reset)         IR <= 8'h00;
        else if (IR_LOAD)   IR <= FROM_MEMORY_BUS;

    // MAR flip flops
    always @ (posedge clk or negedge reset)
        if (!reset)         MAR <= 8'h00;
        else if (MAR_LOAD)   MAR <= FROM_MEMORY_BUS;

    // PC flip flops
    always @ (posedge clk or negedge reset)
        if (!reset)         PC <= 8'h00;
        else if (PC_LOAD)   PC <= FROM_MEMORY_BUS;
        else if (PC_INC)    PC <= MAR + 1;

    // A and B flip flops
    always @ (posedge clk or negedge reset)
        if (!reset)         A <= 8'h00;
        else if (A_LOAD)    A <= FROM_MEMORY_BUS;

    always @ (posedge clk or negedge reset)
        if (!reset)         B <= 8'h00;
        else if (B_LOAD)    B <= FROM_MEMORY_BUS;

    // CCR flip flops (latches directly from ALU)
    always @ (posedge clk or negedge reset)
        if (!reset)         CCR <= 8'h00;
        else if (CCR_LOAD)  CCR <= NZVC; // output from ALU

    // ------------------ ALU -------------------
    alu _alu(
        .A      (A),            // input
        .B      (B),            // input
        .NZVC   (NZVC),         // output (flags)
        .RESULT (ALU_RESULT)    // output
    );

endmodule;
