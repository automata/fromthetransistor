/* verilator lint_off UNUSED */
module hello(input i_clk, i_reset);
initial begin;
    $display("hello world");
end

always @(posedge i_clk) begin
    $display("tick tock");
end
endmodule
