/* verilator lint_off UNUSED */
// simple pipeline: decode, fetch, execute
// no instruction pipelining (so 1 instruction per ~10 clock cycles) - not
// sure if ARM also does it
module control_unit(
    input wire clk, reset,
    input reg [7:0] IR,
    input reg [3:0] CCR,
    output reg IR_LOAD,
    output reg CCR_LOAD,
    output reg MAR_LOAD,
    output reg PC_LOAD,
    output reg PC_INC,
    output reg A_LOAD,
    output reg B_LOAD,
    output reg [2:0] ALU_SEL,
    output reg [1:0] FROM_MEMORY_BUS_SEL,
    output reg [1:0] TO_MEMORY_BUS_SEL,
    output reg write
);
    // ------------------------ INSTRUCTION SET -----------------------------
    // load and stores
    parameter LDA_IMM = 8'h10; // <data> load register A using immediate addressing with <data>
    parameter LDA_DIR = 8'h11; // <addr> load register A using direct addressing from <addr>
    parameter LDB_IMM = 8'h12; // <data> load register B using immediate addressing with <data>
    parameter LDB_DIR = 8'h13; // <addr> load register B using direct addressing from <addr>
    parameter STA_DIR = 8'h14; // <addr> store register A in memory to <addr> (direct addressing)
    parameter STB_DIR = 8'h15; // <addr> store register B in memory to <addr> (direct addressing)
    // data manipulations (ALU stuff)
    parameter ADD_AB  = 8'h20; // A = A + B
    parameter SUB_AB  = 8'h21; // A = A - B
    parameter AND_AB  = 8'h22; // A = A & B
    parameter OR_AB   = 8'h23; // A = A | B
    parameter INCA    = 8'h24; // A = A + 1
    parameter INCB    = 8'h25; // B = B + 1
    parameter DECA    = 8'h26; // A = A - 1
    parameter DECB    = 8'h27; // B = B - 1
    // branches
    parameter BRA     = 8'h30; // <addr> branch always to <address>
    parameter BNU     = 8'h31; // <addr> branch to <addr> if N=1 (negative flag)
    parameter BND     = 8'h32; // <addr> branch to <addr> if N=0 (negative flag
    parameter BZU     = 8'h33; // <addr> branch to <addr> if Z=1 (zero flag)
    parameter BZD     = 8'h34; // <addr> branch to <addr> if Z=0 (zero flag)
    parameter BVU     = 8'h35; // <addr> branch to <addr> if V=1 (two's complement overflow flag)
    parameter BVD     = 8'h36; // <addr> branch to <addr> if V=0 (two's complement overflow flag)
    parameter BCU     = 8'h37; // <addr> branch to <addr> if C=1 (carry flag)
    parameter BCD     = 8'h38; // <addr> branch to <addr> if C=0 (carry flag)

    // fetch: (LDA_IMM)
    //      init: PC register contains the memory address of the first opcode
    //         1. place PC value into MAR (MAR_LOAD)
    //         2. wait 1 clock cycle for the memory to provide the opcode, PC++ while waiting
    //         3. opcode available on FROM_MEMORY_BUS, latch it in IR with IR_LOAD
    // decode: if (IR == LDA_IMM) ...
    // execute:
    //         1. put PC onto MAR to fetch the content to be loaded in A
    //         2. MAR holds the address of the operand, PC++ while waiting for the memory
    //         3. operand available on FROM_MEMORY_BUS, latch memory content into A with A_LOAD
    //         4. register writeback (hold 1 clock cycle)

    // states
    parameter   S_FETCH_0 = 0,
                S_FETCH_1 = 1,
                S_FETCH_2 = 2,

                S_DECODE = 3,

                S_LDA_IMM_0 = 4,
                S_LDA_IMM_1 = 5,
                S_LDA_IMM_2 = 6,
                S_LDA_IMM_3 = 7;


    reg [7:0] current_state, next_state;

    always @ (posedge clk or negedge reset)
    begin: STATE_MEMORY
        if (!reset) current_state <= S_FETCH_0;
        else        current_state <= next_state;
    end

    always @ (current_state, IR) // transition function between states
    begin: NEXT_STATE_LOGIC
        case (current_state)
            S_FETCH_0:  next_state = S_FETCH_1;
            S_FETCH_1:  next_state = S_FETCH_2;
            S_FETCH_2:  next_state = S_DECODE;
            S_DECODE:   begin
                            if (IR == LDA_IMM) next_state = S_LDA_IMM_0;
                            // else if (IR == ...)
                        end
            S_LDA_IMM_0: next_state = S_LDA_IMM_1;
            S_LDA_IMM_1: next_state = S_LDA_IMM_2;
            S_LDA_IMM_2: next_state = S_FETCH_0;
        endcase
    end

    always @ (current_state) // Moore machine so output logic depends solely on current_state
    begin: OUTPUT_LOGIC
        // ------------------------- PIPELINE -------------------------
        case (current_state)
            // ------------------------- FETCH -------------------------
            S_FETCH_0:  begin // one clock cycle to load MAR with PC
                            IR_LOAD         = 0;
                            CCR_LOAD        = 0;
                            MAR_LOAD        = 1;
                            PC_LOAD         = 0;
                            PC_INC          = 0;
                            A_LOAD          = 0;
                            B_LOAD          = 0;
                            ALU_SEL         = 0;
                            TO_MEMORY_BUS_SEL   = 2'b00; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b01; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
            S_FETCH_1:  begin
                            // MAR contains the opcode to be fetched at <address>;
                            // memory[MAR] will take 1 clock cycle to fetch;
                            // data will be available in the next clock cycle, so increment PC while waiting
                            IR_LOAD         = 0;
                            CCR_LOAD        = 0;
                            MAR_LOAD        = 0;
                            PC_LOAD         = 0;
                            PC_INC          = 1;
                            A_LOAD          = 0;
                            B_LOAD          = 0;
                            ALU_SEL         = 0;
                            TO_MEMORY_BUS_SEL   = 2'b00; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b00; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
            S_FETCH_2:  begin
                            // memory[MAR] available, we put it into the FROM_MEMORY BUS and instruct IR to load it
                            // after this, IR is loaded with the opcode, so we can decode the current instruction
                            IR_LOAD         = 1;
                            CCR_LOAD        = 0;
                            MAR_LOAD        = 0;
                            PC_LOAD         = 0;
                            PC_INC          = 0;
                            A_LOAD          = 0;
                            B_LOAD          = 0;
                            ALU_SEL         = 0;
                            TO_MEMORY_BUS_SEL   = 2'b00; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b10; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
            // ------------------------- DECODE -------------------------
            S_DECODE:   begin
                            IR_LOAD         = 0;
                            CCR_LOAD        = 0;
                            MAR_LOAD        = 0;
                            PC_LOAD         = 0;
                            PC_INC          = 0;
                            A_LOAD          = 0;
                            B_LOAD          = 0;
                            ALU_SEL         = 0;
                            TO_MEMORY_BUS_SEL   = 2'bXX;
                            FROM_MEMORY_BUS_SEL = 2'bXX;
                            write = 0;
                        end
            // ------------------------- EXECUTE -------------------------
            // LDA_IMM: Load Register A with immediate addressing
            S_LDA_IMM_0:begin
                            // load A with immediate addressing i.e. directly with <operand>
                            // first, fetch the operand from memory, will take 1 clock cycle, available at next clock cycle (same as S_FETCH_0)
                            IR_LOAD         = 0;
                            CCR_LOAD        = 0;
                            MAR_LOAD        = 1;
                            PC_LOAD         = 0;
                            PC_INC          = 0;
                            A_LOAD          = 0;
                            B_LOAD          = 0;
                            ALU_SEL         = 0;
                            TO_MEMORY_BUS_SEL   = 2'b00; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b01; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
            S_LDA_IMM_1:begin
                            // increment PC while waiting for operand from memory
                            IR_LOAD         = 0;
                            CCR_LOAD        = 0;
                            MAR_LOAD        = 0;
                            PC_LOAD         = 0;
                            PC_INC          = 0;
                            A_LOAD          = 0;
                            B_LOAD          = 0;
                            ALU_SEL         = 0;
                            TO_MEMORY_BUS_SEL   = 2'b00; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b00; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
            S_LDA_IMM_2:begin
                            // operand memory[MAR] is available on the bus, so
                            // we load it into register A
                            IR_LOAD         = 0;
                            CCR_LOAD        = 0;
                            MAR_LOAD        = 0;
                            PC_LOAD         = 0;
                            PC_INC          = 0;
                            A_LOAD          = 1;
                            B_LOAD          = 0;
                            ALU_SEL         = 0;
                            TO_MEMORY_BUS_SEL   = 2'b00; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b10; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
        endcase
    end

endmodule
