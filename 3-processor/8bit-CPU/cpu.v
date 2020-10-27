module cpu
    (input wire clk, reset,
     input wire [7:0] from_memory,
     output reg write, // can write to memory?
     output reg [7:0] to_memory)
endmodule;
