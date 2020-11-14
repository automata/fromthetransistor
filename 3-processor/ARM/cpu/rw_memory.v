module rw_memory#(parameter SIZE = 64000) ( // size in bytes
    input wire mclk,
    input wire enable, // for address validation
    input wire write_enable,
    input wire [31:0] address,
    input wire [31:0] data_in,
    output logic [31:0] data_out
);
    logic [7:0] memory[0:SIZE - 1];

    always_ff @ (posedge mclk)
        if (enable) begin
            if (write_enable) begin
                memory[address + 3] <= data_in[31:24];
                memory[address + 2] <= data_in[23:16];
                memory[address + 1] <= data_in[15:8];
                memory[address + 0] <= data_in[7:0];
            end else begin
                data_out <= {
                    memory[address + 3],
                    memory[address + 2],
                    memory[address + 1],
                    memory[address + 0]
                };
            end
        end

endmodule
