module counter(input wire clk, output reg [3:0] count);
    always @ (posedge clk)
        count <= count + 1;
endmodule
