module rw_96x8_sync(
    input wire clk,
    input wire write, // can write?
    input wire [7:0] address,
    input wire [7:0] data_in,
    output reg [7:0] data_out
);

    reg [7:0] RW [128:223];

    reg enable;
    always @ (address)
    begin
        if (address >= 128 && address < 224)   enable = 1'b1;
        else                                   enable = 1'b0;
    end

    always @ (posedge clk)
    begin
        if (enable && write)                   RW[address] <= data_in; // BUST YO LOGIC WITH USELESS FFs!
        else if (enable && !write)             data_out    <= RW[address];
        $display("RW dump at <%8b>: %8b", address, data_in);
    end

endmodule
