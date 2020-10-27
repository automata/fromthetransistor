// writes data to the output ports
// each output port has a buffer: data stored by the CPU will be there until written to again (so all ports are flip flops)
module output_ports
    (input wire address, // 240..255 for outputs
     input wire clk, reset
     input wire [7:0] address,
     input wire [7:0] data_in, // outputs FFs set from data_in
     output reg [7:0] port_out_00,
     output reg [7:0] port_out_01,
     output reg [7:0] port_out_02,
     output reg [7:0] port_out_03,
     output reg [7:0] port_out_04,
     output reg [7:0] port_out_05,
     output reg [7:0] port_out_06,
     output reg [7:0] port_out_07,
     output reg [7:0] port_out_08,
     output reg [7:0] port_out_09,
     output reg [7:0] port_out_10,
     output reg [7:0] port_out_11,
     output reg [7:0] port_out_12,
     output reg [7:0] port_out_13,
     output reg [7:0] port_out_14,
     output reg [7:0] port_out_15);

    always @ (posedge clk or negedge reset)
        if (!reset)                     port_out_00 <= 8'h00;
        if (write && address == 8'hF0)  port_out_00 <= data_in;
    always @ (posedge clk or negedge reset)
        if (!reset)                     port_out_01 <= 8'h00;
        if (write && address == 8'hF1)  port_out_01 <= data_in;
    always @ (posedge clk or negedge reset)
        if (!reset)                     port_out_02 <= 8'h00;
        if (write && address == 8'hF2)  port_out_02 <= data_in;
    always @ (posedge clk or negedge reset)
        if (!reset)                     port_out_03 <= 8'h00;
        if (write && address == 8'hF3)  port_out_03 <= data_in;
    always @ (posedge clk or negedge reset)
        if (!reset)                     port_out_04 <= 8'h00;
        if (write && address == 8'hF4)  port_out_04 <= data_in;
    always @ (posedge clk or negedge reset)
        if (!reset)                     port_out_05 <= 8'h00;
        if (write && address == 8'hF5)  port_out_05 <= data_in;
    always @ (posedge clk or negedge reset)
        if (!reset)                     port_out_06 <= 8'h00;
        if (write && address == 8'hF6)  port_out_06 <= data_in;
    always @ (posedge clk or negedge reset)
        if (!reset)                     port_out_07 <= 8'h00;
        if (write && address == 8'hF7)  port_out_07 <= data_in;
    always @ (posedge clk or negedge reset)
        if (!reset)                     port_out_08 <= 8'h00;
        if (write && address == 8'hF8)  port_out_08 <= data_in;
    always @ (posedge clk or negedge reset)
        if (!reset)                     port_out_09 <= 8'h00;
        if (write && address == 8'hF9)  port_out_09 <= data_in;
    always @ (posedge clk or negedge reset)
        if (!reset)                     port_out_10 <= 8'h00;
        if (write && address == 8'hFA)  port_out_10 <= data_in;
    always @ (posedge clk or negedge reset)
        if (!reset)                     port_out_11 <= 8'h00;
        if (write && address == 8'hFB)  port_out_11 <= data_in;
    always @ (posedge clk or negedge reset)
        if (!reset)                     port_out_12 <= 8'h00;
        if (write && address == 8'hFC)  port_out_12 <= data_in;
    always @ (posedge clk or negedge reset)
        if (!reset)                     port_out_13 <= 8'h00;
        if (write && address == 8'hFD)  port_out_13 <= data_in;
    always @ (posedge clk or negedge reset)
        if (!reset)                     port_out_14 <= 8'h00;
        if (write && address == 8'hFE)  port_out_14 <= data_in;
    always @ (posedge clk or negedge reset)
        if (!reset)                     port_out_15 <= 8'h00;
        if (write && address == 8'hFF)  port_out_15 <= data_in;

 endmodule
