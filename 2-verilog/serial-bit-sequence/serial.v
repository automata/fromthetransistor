// given a bitstream from some transmiter, drive signal error if the sequence 111 is detected.
module serial
    (output reg error,
     input wire Din, clk, reset);

    // encode the states
    parameter   Start = 3'b000,
                D0_is_1 = 3'b001,
                D0_is_not_1 = 3'b010,
                D1_is_1 = 3'b011,
                D1_is_not_1 = 3'b100;

    // define memory
    reg [2:0] current_state, next_state;
    always @ (posedge clk or negedge reset)
    begin: MEMORY
        if (!reset) current_state <= Start;
        else        current_state <= next_state;
    end

    // define next_state based on inputs and current_state, so define the
    // mealy function
    always @ (current_state or Din)
    begin: NEXT_STATE_LOGIC
        case (current_state)
            Start:          if (Din == 1'b1) next_state = D0_is_1;  else next_state = D0_is_not_1;
            D0_is_1:        if (Din == 1'b1) next_state = D1_is_1;  else next_state = D1_is_not_1;
            D1_is_1:        next_state = Start;
            D0_is_not_1:    next_state = D1_is_not_1;
            D1_is_not_1:    next_state = Start;
            default:        next_state = Start;
        endcase
    end

    // define outputs based on current state and Din
    // output based on current_state and inputs, so previous results
    // not encoded in the current_state, so this is a mealy function
    always @ (current_state or Din)
    begin: OUTPUT_LOGIC
        case (current_state)
            D1_is_1: if (Din == 1'b1) error = 1'b1; else error = 1'b0; // mealy, since output not present in current state
            default: error = 1'b0;
        endcase
    end

endmodule
