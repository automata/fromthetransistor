module rw_memory #(parameter size = 64000) (
    input wire clk,
    input wire reset,
    input wire enable, // for address validation
    input wire write,
    input wire [31:0] address,
    input wire [31:0] data_in,
    output reg [31:0] data_out
);

    reg [7:0] memory[0:size - 1];

    always @ (posedge clk or negedge reset)
        if (enable) begin
            if (!reset) begin
                memory[address + 3] <= 8'h00;
                memory[address + 2] <= 8'h00;
                memory[address + 1] <= 8'h00;
                memory[address + 0] <= 8'h00;
            end else begin
                if (write) begin
                    memory[address + 3] <= data_in[31:24];
                    memory[address + 2] <= data_in[23:16];
                    memory[address + 1] <= data_in[15:8];
                    memory[address + 0] <= data_in[7:0];
                end
                else begin
                    data_out <= {
                        memory[address + 3],
                        memory[address + 2],
                        memory[address + 1],
                        memory[address + 0]
                    };
                end
            end
        end

endmodule
