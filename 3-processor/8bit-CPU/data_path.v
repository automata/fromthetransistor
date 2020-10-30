module data_path(
    input wire clk, reset,
    input wire [7:0] from_memory,
    input wire IR_LOAD,     // IR is loading; fetch next program instruction from ROM
    input wire CCR_LOAD,    // CCR is loading; sets CCR flags depending on ALU operation output
    input reg MAR_LOAD,     // MAR is loading; fetch from memory at the address in MAR, content put into FROM_MEMORY_BUS (data_out in memory.v)
    input reg PC_LOAD,      // PC is loading; loads the PC register with contents from the FROM_MEMORY_BUS
    input reg PC_INC,       // PC incrementing; increments the PC register to continue execution of program
    input reg A_LOAD,       // A is loading with contents FROM_MEMORY_BUS
    input reg B_LOAD,       // B is loading with contents FROM_MEMORY_BUS
    input reg ALU_SEL,      // instruct ALU which operation to perform
    input reg FROM_MEMORY_SEL, // multiplexer selector of what gets into FROM_MEMORY_BUS
    input reg TO_MEMORY_SEL,    // multiplexer selector of what gets into TO_MEMORY_BUS
    output reg [7:0] IR,        // IR register; contains content of IR -- input into control_unit (needed for decoding the current instruction)
    output reg [7:0] CCR,       // condition coder register (NZVC, Negative, Zero, Overflow, Carry) -- input into control unit
    output wire [7:0] address,  // address to fetch stuff from in memory (contents of MAR)
    output reg [7:0] to_memory  // stuff to put into memory at <address>
);
    reg [7:0] ALU_RESULT;
    reg [3:0] NZVC;

    // -------------------------------------------
    // ---------------- REGISTERS ----------------
    // -------------------------------------------
    // IR and CCR are already defined in the ouput list
    reg [7:0] MAR; // memory address register
    reg [7:0] PC; // program counter register
    reg [7:0] A;    // A register
    reg [7:0] B;    // B register

    // -------------------------------------------
    // ------------------ BUSES ------------------
    // -------------------------------------------
    reg [7:0] FROM_MEMORY_BUS;
    reg [7:0] TO_MEMORY_BUS;

    // -------------------------------------------
    // ------------------ LOGIC ------------------
    // -------------------------------------------

    // buses
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

    // registers
    always @ (posedge clk or negedge reset) // IR flip flops
        if (!reset)         IR <= 8'h00;
        else if (IR_LOAD)   IR <= FROM_MEMORY_BUS;

    always @ (posedge clk or negedge reset) // MAR flip flops
        if (!reset)         MAR <= 8'h00;
        else if (MAR_LOAD)   MAR <= FROM_MEMORY_BUS;

    always @ (posedge clk or negedge reset) // PC flip flops
        if (!reset)         PC <= 8'h00;
        else if (PC_LOAD)   PC <= FROM_MEMORY_BUS;
        else if (PC_INC)    PC <= MAR + 1;

    always @ (posedge clk or negedge reset) // A and B flip flops
        if (!reset)         A <= 8'h00;
        else if (A_LOAD)    A <= FROM_MEMORY_BUS;

    always @ (posedge clk or negedge reset)
        if (!reset)         B <= 8'h00;
        else if (B_LOAD)    B <= FROM_MEMORY_BUS;

    always @ (posedge clk or negedge reset) // CCR flip flops (latches directly from ALU)
        if (!reset)         CCR <= 8'h00;
        else if (CCR_LOAD)  CCR <= NZVC; // output from ALU

    // ------------------ ALU -------------------
    alu _alu(
        .A      (A),            // input
        .B      (B),            // input
        .SEL    (ALU_SEL),      // input
        .NZVC   (NZVC),         // output (flags)
        .RESULT (ALU_RESULT)    // output
    );

endmodule;
