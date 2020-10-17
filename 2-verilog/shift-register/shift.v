// shift register: circuit of 4 daisy chained registers where each register
// gets the value of the previous one
module shift
  (output reg [3:0] Dout0, Dout1, Dout2, Dout3,
   input wire enable, reset, clk,
   input wire [3:0] Din);

  always @ (posedge clk or posedge reset) begin
    if (reset) begin
      Dout0 <= 4'h00; Dout1 <= 4'h00; Dout2 <= 4'h00; Dout3 <= 4'h00;
    end else begin
      if (enable) begin
        // can chain assignments like this since they're non blocking so none
        // get updated until always finishes, so can daisy chain them together
        Dout0 <= Din; Dout1 <= Dout0; Dout2<= Dout1; Dout3 <= Dout2;
      end
    end
  end

endmodule
