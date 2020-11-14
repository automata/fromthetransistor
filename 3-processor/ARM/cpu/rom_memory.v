module rom_memory#(parameter SIZE = 64000) ( // size in bytes
    input wire mclk,
    input wire enable, // for address validation
    input wire [31:0] address,
    output logic [31:0] data_out
);
    logic [7:0] ROM [0:SIZE - 1]; // byte sized chunks

    initial begin
        // a single instruction is 4 bytes
        ROM[0] = 8'hFF;
        ROM[1] = 8'h00;
        ROM[2] = 8'h00;
        ROM[3] = 8'h00;
    end

    always_ff @ (posedge mclk)
    begin
        if (enable) begin
            $display("HERE");
            data_out <= {
                ROM[address + 3],
                ROM[address + 2],
                ROM[address + 1],
                ROM[address + 0]
            };
            $display("data_out = %d\n", data_out);
        end
    end

endmodule
