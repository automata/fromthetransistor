/*
8 bit address to reference 0..255 locations of 8bits each
256 total bytes:
    128: program (ROM)
    96: data (RW)
    32: IO (16 in, 16 out)
entire address is loaded on the bus at once
*/
module memory
    (input wire clk, reset,
     input wire write, // can write?
     input wire [15:0] port_in[0:7], // IO
     input wire [7:0] address, data_in,
     output reg [7:0] data_out,
     output reg [15:0] port_out[0:7]); // IO

endmodule;
