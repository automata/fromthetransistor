// Timing: 2 cycles
module multiplier(
    input wire clk,
    input wire [31:0] a,
    input wire [31:0] b,
    output logic signed [63:0] result
);
    logic signed [31:0] ax;
    logic signed [31:0] bx;

    // let the synthesis library choose the best multiplier style (depending on area/power/speed)
    always @ (posedge clk) begin
        ax <= a;
        bx <= b;
        result <= ax * bx;
    end

endmodule
