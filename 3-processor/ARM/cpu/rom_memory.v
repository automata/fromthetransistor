module rom_memory #(parameter size = 64000) (
    input wire clk,
    input wire enable, // for address validation
    input wire [31:0] address,
    output bit [31:0] data_out
);
    bit [7:0] ROM [0:size - 1]; // byte sized chunks

    initial begin
        // a single instruction is 4 bytes
        ROM[0] = 8'h00;
        ROM[1] = 8'h01;
        ROM[2] = 8'h02;
        ROM[3] = 8'h03;
    end

    always @ (posedge clk)
    begin
        if (enable) begin
            data_out <= {
                ROM[address + 3],
                ROM[address + 2],
                ROM[address + 1],
                ROM[address + 0]
            };
        end
    end

endmodule
