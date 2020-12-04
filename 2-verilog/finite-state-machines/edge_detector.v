// Detects the rising edge of any input coming into the $level port through Mealy and Moore machines.
module edge_detector(
    input wire clk, reset,
    input wire level,
    output bit mealy_tick, moore_tick
);

    localparam
        zero_mealy = 1'b0,
        one_mealy = 1'b1;

    localparam [1:0]
        zero_moore = 2'b00,
        edge_moore = 2'b01,
        one_moore = 2'b10;

    bit state_mealy_reg, state_mealy_next;
    bit [1:0] state_moore_reg, state_moore_next;

    // state update on clock cycle, same for Moore and Mealy
    always @ (posedge clk or negedge reset)
        if (~reset) begin
            state_mealy_reg <= zero_mealy;
            state_moore_reg <= zero_moore;
        end
        else begin
            state_moore_reg <= state_moore_next;
            state_mealy_reg <= state_mealy_next;
        end

    // A Mealy designed output depends on the current state and input; the output is available as soon as the input is changed.
    // Therefore this design can be considered asynchronous.
    always @ (state_mealy_reg or level) begin
        mealy_tick = 1'b0;
        case (state_mealy_reg)
            zero_mealy: begin
                if (level) begin
                    mealy_tick = 1'b1; // output depends on current input ($level) and current state($zero_mealy)
                    state_mealy_next = one_mealy;
                end
            end
            one_mealy: begin
                if (~level)
                    state_mealy_next = zero_mealy;
            end
            default:
                state_mealy_next = state_mealy_reg;
        endcase
    end

    // A Moore machine's output depends on current state only; that means that once the current state changes, the output
    // of the next state will not be present in the current clock cycle, but the next one.
    // Therefore this design can be considered synchronous.
    always @ (state_moore_reg or level) begin
        moore_tick = 1'b0;
        case (state_moore_reg)
            zero_moore: begin
                moore_tick = 1'b0;
                if (level)
                    state_moore_next = edge_moore;
            end
            edge_moore: begin
                moore_tick = 1'b1; // output depends only on current state ($edge_moore)
                if (level)
                    state_moore_next = one_moore;
                else
                    state_moore_next = zero_moore;
            end
            one_moore: begin
                moore_tick = 1'b0;
                if (~level)
                    state_moore_next = zero_moore;
            end
            default:
                state_moore_next = state_moore_reg;
        endcase
    end

endmodule
