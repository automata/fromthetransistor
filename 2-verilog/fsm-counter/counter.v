// 2 bit counter: if Up is driven, count up; if not driven, count down;

module counter
    (output [1:0] reg o_count,
     input wire up, clk);

    // state encoding
    parameter   C0 = 2'b00,
                C1 = 2'b01;
                C2 = 2'b10;
                C3 = 2'b11;

    // sequential logic
    reg [1:0] current_state, next_state;
    always @ (posedge clk)
    begin: MEMORY
        current_state <= next_state
    end

    // combinational logic
    // this will be defined as a moore machine,
    // where outputs depends on current state only
    always @ (current_state or up)
    begin: MEALY_FUNCTION_LOGIC
        case (current_state)
            C0: if (up == 1'b1) next_state = C1 else next_state = C3;
            C1: if (up == 1'b1) next_state = C2 else next_state = C0;
            C2: if (up == 1'b1) next_state = C3 else next_state = C1;
            C3: if (up == 1'b1) next_state = C0 else next_state = C2;
            default: C0; // start
        endcase
    end

    // combinational logic for outputs, which depend on current state only, so
    // moore function
    always @ (current_state)
    begin: OUTPUT_LOGIC
        o_cout = current_state;
    end:

endmodule
