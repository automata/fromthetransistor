`timescale 1ns/1ps
/* verilator lint_off UNUSED */
module hello(input i_clk, i_reset, output wire test);
    initial begin;
        $display("hello world");
    end

    assign test = i_clk;

    always @(posedge i_clk) begin
        $display("tick tock");
    end
endmodule
