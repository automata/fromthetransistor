module register(
    input wire clk,
    input wire reset,
    input wire write_enable,
    input wire [31:0] data_in,
    output bit [31:0] data_out
);
    bit [31:0] content;

    always @ (posedge clk or negedge reset)
        if (!reset)
            content <= 32'h00000000;
        else
            if (write_enable)
                content <= data_in;
            else
                data_out <= content;

endmodule
