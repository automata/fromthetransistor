module data_path
    (input wire clk, reset,
     input wire [7:0] address,
     input wire [7:0] from_memory,
     output reg [7:0] to_memory);
endmodule;
