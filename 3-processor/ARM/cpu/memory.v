/* verilator lint_off UNUSED */
module memory #(parameter rom_end = 64000)(
    input wire clk,
    input wire [31:0] data_in,
    input wire [31:0] address,
    input wire write,
    input wire reset,
    output reg [31:0] data_out
);

    reg rom_enable;
    reg rw_enable;

    always @ (address) begin
        if (address < rom_end) begin
            rom_enable = 1'b1;
            rw_enable = 1'b0;
        end
        else begin
            rom_enable = 1'b0;
            rw_enable = 1'b1;
        end
    end

    rom_memory _rom(
        .clk        (clk),
        .enable     (rom_enable),
        .address    (address),
        .data_out   (data_out)
    );

    rw_memory _rw(
        .clk        (clk),
        .enable     (rw_enable),
        .write      (write),
        .address    (address),
        .data_in    (data_in),
        .data_out   (data_out)
    );

endmodule
