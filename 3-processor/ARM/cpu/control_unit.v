/* Controls the processing unit
* 3 stage pipeline:
* - fetch: load instruction register
* - decode: decode instruction
* - execute: execute instruction's state machine
*/
module control_unit(
    input wire mclk,
    input wire nreset,
    input wire [31:0] ir, // instruction register
    output logic ir_load, // load instruction register with next instruction to be executed
);
    logic [31:0] mov_mask;
    initial begin
        //             cond  I    SSBZ Rd shifter_op
        mov_mask = 32'b1111001110111111111111111111111
    end

    parameter s_fetch_0 = 3'b000;

    logic integer current_state, next_state;
    always_ff @ (posedge mclk) begin
        if (nreset)
            current_state <= state_fetch_0;
        else
            current_state <= next_state;
    end

    always_comb begin
        case (current_state)
            s_fetch_0: next_state = s_decode;
            s_decode: begin
            end
        endcase
    end

    // SBZ reserved for MMU
    always_comb begin
        case (current_state)
            s_decode: begin
                if (ir & mov_mask == mov_mask)
            end
        endcase
    end

endmodule
