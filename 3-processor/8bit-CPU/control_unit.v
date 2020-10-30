// simple pipeline: decode, fetch, execute
// no instruction pipelining (so 1 instruction per ~10 clock cycles) - not
// sure if ARM also does it
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
                            if (IR == LDA_IMM) next_state = S_LDA_IMM_1;
                            // else if (IR == ...
                        end
            S_LDA_IMM_0: next_state = S_LDA_IMM_1;
            S_LDA_IMM_1: next_state = S_LDA_IMM_2;
            S_LDA_IMM_2: next_state = S_LDA_IMM_3;
            S_LDA_IMM_3: next_state = S_FETCH_0;
        endcase
    end

    always @ (current_state) // Moore machine so output logic depends solely on current_state
    begin: OUTPUT_LOGIC
        case (current_state)
            S_FETCH_0:  begin
                            IR_LOAD         = 0;
                            CCR_LOAD        = 0;
                            MAR_LOAD        = 1;
                            PC_LOAD         = 0;
                            PC_INC          = 0;
                            A_LOAD          = 0;
                            B_LOAD          = 0;
                            ALU_SEL         = 0;
                            FROM_MEMORY_SEL = 2'b00; // 00 = ALU_RESULT; 01 = TO_MEMORY_BUS; 10 = from_memory
                            TO_MEMORY_SEL   = 2'b00; // 00 = PC; 01 = A; 10 = B;
                            write = 0;
                        end
            // .. other states
        endcase
    end

endmodule
