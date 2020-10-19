/*
 * A simple FSM modelled as a Mealy machine i.e:
 *   next_state = f(current_state, inputs)
 *   (Moore: next_state = f(current_state), so current state already encodes
 *   inputs)
 *
 *
 */
module fsm
    (output reg out_open, out_close,
    input wire button, clk);

    parameter   closed = 1'b0,
                opened = 1'b1;

    // define fsm's memory
    reg current_state, next_state;

    always @ (posedge clk)
    begin: MEMORY
        current_state <= next_state;
    end

    // define how next_state gets updated based on inputs and current state;
    // this is combinational (no memory involved) so needs to trigger on all
    // inputs (current_state and button)
    // basically, define the mealy function
    // (combinational)
    always @ (current_state or button)
    begin: MEALY
        case (current_state)
            closed: if (button == 1'b1) next_state = opened; else next_state = closed;
            opened: if (button == 1'b1) next_state = closed; else next_state = opened;
            default: next_state = closed;
        endcase
    end

    // define how the outputs behave (combinational)
    always @ (current_state or button)
    begin: OUTPUT
        case (current_state)
            opened:
            if (button == 1'b1)
            begin
                out_open = 1'b1;
                out_close = 1'b0;
            end
            else
            begin
                out_open = 1'b0;
                out_close = 1'b0;
            end

            closed:
            if (button == 1'b1)
            begin
                out_open = 1'b0;
                out_close = 1'b1;
            end
            else
            begin
                out_open = 1'b0;
                out_close = 1'b0;
            end
            default:
            begin
                out_open = 1'b0;
                out_close = 1'b0;
            end
        endcase
    end
endmodule
