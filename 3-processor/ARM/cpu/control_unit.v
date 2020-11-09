// controls the processing unit and instruct writes to memory
module control_unit(
    input wire [31:0] IR_fetch, // contains contents of IR
);

    // Moore machine: output depends on current state only
    reg [31:0] current_state, next_state;

    always @ (posedge clk or negedge reset) // Moore memory
        if (!reset) current_state <= 4'h00000000;
        else        current_state <= next_state;


    // pipeline: decode, fetch, execute
    always @ (current_state, IR_fetch) // define Moore function
        case (current_state)
        endcase

    always @ (current_state) // define each state
        case (current_state)
        endcase

endmodule
