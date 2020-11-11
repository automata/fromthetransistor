module register(
    input wire clk,
    input wire reset,
    input wire write,
    input wire [31:0] data_in,
    output reg [31:0] data_out
);

    reg [31:0] content;

    always @ (posedge clk or negedge reset)
        if (!reset)
            content <= 32'h00000000;
        else
            if (write)
                content <= data_in;
            else
                data_out <= content;

endmodule
