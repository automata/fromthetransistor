/* verilator lint_off COMBDLY */
`timescale 1ns/1ps
module dlatch(input wire clk, D, output reg Q, Qn);
    initial begin;
        $display("dlatch");
    end

    always @(clk or D) begin
        if (clk == 1'b1)
        begin
            Q <= D; // using blocking '=' also works but it will be interpreted as a combinational device which defeats the purpose of having a clock
            Qn <= ~D;
        end
    end
endmodule
