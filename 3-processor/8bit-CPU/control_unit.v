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

                S_LDA_DIR_0 = 7,
                S_LDA_DIR_1 = 8,
                S_LDA_DIR_2 = 9,
                S_LDA_DIR_3 = 10,

                S_LDB_IMM_0 = 11,
                S_LDB_IMM_1 = 12,
                S_LDB_IMM_2 = 13,

                S_LDB_DIR_0 = 14,
                S_LDB_DIR_1 = 15,
                S_LDB_DIR_2 = 16,
                S_LDB_DIR_3 = 17,

                S_STA_DIR_0 = 18,
                S_STA_DIR_1 = 19,
                S_STA_DIR_2 = 20,
                S_STA_DIR_3 = 21,

                S_STB_DIR_0 = 18,
                S_STB_DIR_1 = 19,
                S_STB_DIR_2 = 20,
                S_STB_DIR_3 = 21,

                S_ADD_AB    = 22,
                S_SUB_AB    = 23,
                S_AND_AB    = 24,
                S_OR_AB     = 25,
                S_INCA      = 26,
                S_INCB      = 27,
                S_DECA      = 28,
                S_DECB      = 29;


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
                            if      (IR == LDA_IMM) next_state = S_LDA_IMM_0;
                            else if (IR == LDA_DIR) next_state = S_LDA_DIR_0;
                            else if (IR == LDB_IMM) next_state = S_LDB_IMM_0;
                            else if (IR == LDB_DIR) next_state = S_LDB_DIR_0;
                            else if (IR == STA_DIR) next_state = S_STA_DIR_0;
                            else if (IR == STB_DIR) next_state = S_STB_DIR_0;
                            else if (IR == ADD_AB)  next_state = S_ADD_AB;
                            else if (IR == SUB_AB)  next_state = S_SUB_AB;
                            else if (IR == AND_AB)  next_state = S_AND_AB;
                            else if (IR == OR_AB)   next_state = S_OR_AB;
                            else if (IR == INCA)    next_state = S_INCA;
                            else if (IR == INCB)    next_state = S_INCB;
                            else if (IR == DECA)    next_state = S_DECA;
                            else if (IR == DECB)    next_state = S_DECB;
                        end
            // LDA_IMM
            S_LDA_IMM_0: next_state = S_LDA_IMM_1;
            S_LDA_IMM_1: next_state = S_LDA_IMM_2;
            S_LDA_IMM_2: next_state = S_FETCH_0;
            // LDA_DIR
            S_LDA_DIR_0: next_state = S_LDA_DIR_1;
            S_LDA_DIR_1: next_state = S_LDA_DIR_2;
            S_LDA_DIR_2: next_state = S_LDA_DIR_3;
            S_LDA_DIR_3: next_state = S_FETCH_0;
            // LDB_IMM
            S_LDB_IMM_0: next_state = S_LDB_IMM_1;
            S_LDB_IMM_1: next_state = S_LDB_IMM_2;
            S_LDB_IMM_2: next_state = S_FETCH_0;
            // LDB_DIR
            S_LDB_DIR_0: next_state = S_LDB_DIR_1;
            S_LDB_DIR_1: next_state = S_LDB_DIR_2;
            S_LDB_DIR_2: next_state = S_LDB_DIR_3;
            S_LDB_DIR_3: next_state = S_FETCH_0;
            // STA_DIR
            S_STA_DIR_0: next_state = S_STA_DIR_1;
            S_STA_DIR_1: next_state = S_STA_DIR_2;
            S_STA_DIR_2: next_state = S_STA_DIR_3;
            S_STA_DIR_3: next_state = S_FETCH_0;
            // STB_DIR
            S_STB_DIR_0: next_state = S_STB_DIR_1;
            S_STB_DIR_1: next_state = S_STB_DIR_2;
            S_STB_DIR_2: next_state = S_STB_DIR_3;
            S_STB_DIR_3: next_state = S_FETCH_0;
            // ADD_AB
            S_ADD_AB: next_state    = S_FETCH_0;
            // SUB_AB
            S_SUB_AB: next_state    = S_FETCH_0;
            // AND_AB
            S_AND_AB: next_state    = S_FETCH_0;
            // OR_AB
            S_OR_AB: next_state     = S_FETCH_0;
            // INCA
            S_INCA: next_state      = S_FETCH_0;
            // INCB
            S_INCB: next_state      = S_FETCH_0;
            // DECA
            S_DECA: next_state      = S_FETCH_0;
            // DECB
            S_DECB: next_state      = S_FETCH_0;
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
                            TO_MEMORY_BUS_SEL   = 2'bXX; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'bXX; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
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
                            PC_INC          = 1;
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
            // LDA_DIR: Load Register A with direct addressing
            S_LDA_DIR_0:begin
                            // load A with direct addressing i.e. with memory[<operand>]
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
            S_LDA_DIR_1:begin
                            // increment PC while waiting for operand from memory
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
            S_LDA_DIR_2:begin
                            // operand memory[MAR] is available on the bus;
                            // we load operand into MAR to then fetch memory[operand]
                            // the load takes 1 clock cycle
                            IR_LOAD         = 0;
                            CCR_LOAD        = 0;
                            MAR_LOAD        = 1;
                            PC_LOAD         = 0;
                            PC_INC          = 0;
                            A_LOAD          = 0;
                            B_LOAD          = 0;
                            ALU_SEL         = 0;
                            TO_MEMORY_BUS_SEL   = 2'b00; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b10; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
            S_LDA_DIR_3:begin
                            // operand is in MAR, we now fetch memory[operand]
                            // while waiting for that, we increment the
                            // program counter
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
            // LDB_IMM: Load Register B with immediate addressing
            S_LDB_IMM_0:begin
                            // load B with immediate addressing i.e. directly with <operand>
                            // first, fetch the operand from memory, will take 1 clock cycle, available at next clock cycle (same as S_FETCH_0)
                            // (PC gets loaded into MAR through the buses)
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
            S_LDB_IMM_1:begin
                            // increment PC while waiting for operand from memory
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
            S_LDB_IMM_2:begin
                            // operand memory[MAR] is available on the bus, so
                            // we load it into register B
                            IR_LOAD         = 0;
                            CCR_LOAD        = 0;
                            MAR_LOAD        = 0;
                            PC_LOAD         = 0;
                            PC_INC          = 0;
                            A_LOAD          = 0;
                            B_LOAD          = 1;
                            ALU_SEL         = 0;
                            TO_MEMORY_BUS_SEL   = 2'b00; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b10; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
            // LDB_DIR: Load Register B with direct addressing
            S_LDB_DIR_0:begin
                            // load B with direct addressing i.e. with memory[<operand>]
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
            S_LDB_DIR_1:begin
                            // increment PC while waiting for operand from memory
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
            S_LDB_DIR_2:begin
                            // operand memory[MAR] is available on the bus;
                            // we load operand into MAR to then fetch memory[operand]
                            // the load takes 1 clock cycle
                            IR_LOAD         = 0;
                            CCR_LOAD        = 0;
                            MAR_LOAD        = 1;
                            PC_LOAD         = 0;
                            PC_INC          = 0;
                            A_LOAD          = 0;
                            B_LOAD          = 0;
                            ALU_SEL         = 0;
                            TO_MEMORY_BUS_SEL   = 2'b00; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b10; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
            S_LDB_DIR_3:begin
                            // operand is in MAR, we now fetch memory[operand]
                            // while waiting for that, we increment the
                            // program counter
                            IR_LOAD         = 0;
                            CCR_LOAD        = 0;
                            MAR_LOAD        = 0;
                            PC_LOAD         = 0;
                            PC_INC          = 0;
                            A_LOAD          = 0;
                            B_LOAD          = 1;
                            ALU_SEL         = 0;
                            TO_MEMORY_BUS_SEL   = 2'b00; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b10; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
            // STA_DIR: Store register A in memory with direct addressing
            S_STA_DIR_0:begin
                            // first, fetch the operand from memory, will take 1 clock cycle, available at next clock cycle
                            // memory[<operand>] will contain A
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
            S_STA_DIR_1:begin
                            // while waiting, increment PC
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
            S_STA_DIR_2:begin
                            // operand is on FROM_MEMORY_BUS, put it into MAR
                            IR_LOAD         = 0;
                            CCR_LOAD        = 0;
                            MAR_LOAD        = 1;
                            PC_LOAD         = 0;
                            PC_INC          = 0;
                            A_LOAD          = 0;
                            B_LOAD          = 0;
                            ALU_SEL         = 0;
                            TO_MEMORY_BUS_SEL   = 2'b00; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b10; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
            S_STA_DIR_3:begin
                            // trigger memory load; this is combinational so
                            // ROM should already provide it by the end of it
                            // (available in FETCH)
                            IR_LOAD         = 0;
                            CCR_LOAD        = 0;
                            MAR_LOAD        = 0;
                            PC_LOAD         = 0;
                            PC_INC          = 0;
                            A_LOAD          = 0;
                            B_LOAD          = 0;
                            ALU_SEL         = 0;
                            TO_MEMORY_BUS_SEL   = 2'b01; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'bXX; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 1;
                        end
            // STB_DIR: Store register B in memory with direct addressing
            S_STB_DIR_0:begin
                            // first, fetch the operand from memory, will take 1 clock cycle, available at next clock cycle
                            // memory[<operand>] will contain B
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
            S_STB_DIR_1:begin
                            // while waiting, increment PC
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
            S_STB_DIR_2:begin
                            // operand is on FROM_MEMORY_BUS, put it into MAR
                            IR_LOAD         = 0;
                            CCR_LOAD        = 0;
                            MAR_LOAD        = 1;
                            PC_LOAD         = 0;
                            PC_INC          = 0;
                            A_LOAD          = 0;
                            B_LOAD          = 0;
                            ALU_SEL         = 0;
                            TO_MEMORY_BUS_SEL   = 2'b00; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b10; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
            S_STB_DIR_3:begin
                            // trigger memory load; this is combinational so
                            // ROM should already provide it by the end of it
                            // (available in FETCH)
                            IR_LOAD         = 0;
                            CCR_LOAD        = 0;
                            MAR_LOAD        = 0;
                            PC_LOAD         = 0;
                            PC_INC          = 0;
                            A_LOAD          = 0;
                            B_LOAD          = 0;
                            ALU_SEL         = 0;
                            TO_MEMORY_BUS_SEL   = 2'b10; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'bXX; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 1;
                        end
            // ALU stuff
            S_ADD_AB:   begin
                            IR_LOAD         = 0;
                            CCR_LOAD        = 1;
                            MAR_LOAD        = 0;
                            PC_LOAD         = 0;
                            PC_INC          = 1;
                            A_LOAD          = 1;
                            B_LOAD          = 0;
                            ALU_SEL         = 3'b000;
                            TO_MEMORY_BUS_SEL   = 2'b01; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b00; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
            S_SUB_AB:   begin
                            IR_LOAD         = 0;
                            CCR_LOAD        = 1;
                            MAR_LOAD        = 0;
                            PC_LOAD         = 0;
                            PC_INC          = 1;
                            A_LOAD          = 1;
                            B_LOAD          = 0;
                            ALU_SEL         = 3'b001;
                            TO_MEMORY_BUS_SEL   = 2'b01; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b00; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
            S_AND_AB:   begin
                            IR_LOAD         = 0;
                            CCR_LOAD        = 1;
                            MAR_LOAD        = 0;
                            PC_LOAD         = 0;
                            PC_INC          = 1;
                            A_LOAD          = 1;
                            B_LOAD          = 0;
                            ALU_SEL         = 3'b010;
                            TO_MEMORY_BUS_SEL   = 2'b01; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b00; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
            S_OR_AB:    begin
                            IR_LOAD         = 0;
                            CCR_LOAD        = 1;
                            MAR_LOAD        = 0;
                            PC_LOAD         = 0;
                            PC_INC          = 1;
                            A_LOAD          = 1;
                            B_LOAD          = 0;
                            ALU_SEL         = 3'b011;
                            TO_MEMORY_BUS_SEL   = 2'b01; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b00; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
            S_INCA:     begin
                            IR_LOAD         = 0;
                            CCR_LOAD        = 1;
                            MAR_LOAD        = 0;
                            PC_LOAD         = 0;
                            PC_INC          = 1;
                            A_LOAD          = 1;
                            B_LOAD          = 0;
                            ALU_SEL         = 3'b100;
                            TO_MEMORY_BUS_SEL   = 2'b01; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b00; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
            S_INCB:     begin
                            IR_LOAD         = 0;
                            CCR_LOAD        = 1;
                            MAR_LOAD        = 0;
                            PC_LOAD         = 0;
                            PC_INC          = 1;
                            A_LOAD          = 0;
                            B_LOAD          = 1;
                            ALU_SEL         = 3'b101;
                            TO_MEMORY_BUS_SEL   = 2'b10; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b00; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
            S_DECA:     begin
                            IR_LOAD         = 0;
                            CCR_LOAD        = 1;
                            MAR_LOAD        = 0;
                            PC_LOAD         = 0;
                            PC_INC          = 1;
                            A_LOAD          = 1;
                            B_LOAD          = 0;
                            ALU_SEL         = 3'b110;
                            TO_MEMORY_BUS_SEL   = 2'b01; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b00; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
            S_DECB:     begin
                            IR_LOAD         = 0;
                            CCR_LOAD        = 1;
                            MAR_LOAD        = 0;
                            PC_LOAD         = 0;
                            PC_INC          = 1;
                            A_LOAD          = 0;
                            B_LOAD          = 1;
                            ALU_SEL         = 3'b111;
                            TO_MEMORY_BUS_SEL   = 2'b10; // 00 = PC; 01 = A; 10 = B;
                            FROM_MEMORY_BUS_SEL = 2'b00; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            write = 0;
                        end
        endcase
    end

endmodule
