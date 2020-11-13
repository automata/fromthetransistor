module memory #(parameter rom_end = 64000) (
    input wire clk,
    input wire reset,
    input wire [31:0] data_in,
    input wire [31:0] address,
    input wire write,
    output logic [31:0] data_out
);

    logic rom_enable, rw_enable;
    logic [31:0] rom_data_out, rw_data_out;

    always_comb begin
        if (address < rom_end) begin
            rom_enable = 1'b1;
            data_out = rom_data_out;
            rw_enable = 1'b0;
        end
        else begin
            rom_enable = 1'b0;
            rw_enable = 1'b1;
            data_out = rw_data_out;
        end
    end

    rom_memory _rom(
        .clk        (clk),
        .enable     (rom_enable),
        .address    (address),
        .data_out   (rom_data_out)
    );

    rw_memory _rw(
        .clk        (clk),
        .reset      (reset),
        .enable     (rw_enable),
        .write      (write),
        .address    (address),
        .data_in    (data_in),
        .data_out   (rw_data_out)
    );

endmodule
