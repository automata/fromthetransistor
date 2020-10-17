// 8bit register
module register(input reg enable, reset, clk, [7:0] signals, output reg [7:0] bits);
  always @ (posedge clk or posedge reset) begin
    if (reset)
      bits <= 8'h00;
    else
      if (enable)
        bits <= signals;
  end
endmodule
