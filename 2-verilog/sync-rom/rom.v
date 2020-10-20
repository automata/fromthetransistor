// 4x4 synchronous ROM
// given an address, fetch the bits of that address (4 addresses each
// containing 4 bits, address encoded in 2 bits)
module rom
    (output reg [3:0] data_out,
     input wire [1:0] address,
     input wire clk);

    // set ROM
    reg [3:0] ROM [0:3]; // 4bit vector bus
    initial begin
        ROM[0] = 4'b0011;
        ROM[1] = 4'b1000;
        ROM[2] = 4'b1111;
        ROM[3] = 4'b0110;
    end

    // fetch ROM synchronously
    always @ (posedge clk)
        data_out <= ROM[address];

endmodule
