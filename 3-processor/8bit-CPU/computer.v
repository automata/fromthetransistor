module computer(
    input wire clk, reset
);

    parameter ZERO = 8'h00;

    reg [7:0] address;
    reg [7:0] from_memory;
    reg [7:0] to_memory;
    reg write;

    reg [7:0] port_out_00;
    reg [7:0] port_out_01;
    reg [7:0] port_out_02;
    reg [7:0] port_out_03;
    reg [7:0] port_out_04;
    reg [7:0] port_out_05;
    reg [7:0] port_out_06;
    reg [7:0] port_out_07;
    reg [7:0] port_out_08;
    reg [7:0] port_out_09;
    reg [7:0] port_out_10;
    reg [7:0] port_out_11;
    reg [7:0] port_out_12;
    reg [7:0] port_out_13;
    reg [7:0] port_out_14;
    reg [7:0] port_out_15;

    always @ (posedge clk or negedge reset)
    begin
        cpu _cpu(
            .clk            (clk),
            .reset          (reset),
            .from_memory    (from_memory),  // input  (from MEMORY)
            .address        (address),      // output (address into memory, to MEMORY)
            .to_memory      (to_memory),    // output (put stuff into memory at <address>, to MEMORY)
            .write          (write),        // output (can write to memory at <address>?, to MEMORY)
        );

        memory _memory(
            .clk            (clk),
            .reset          (reset),
            .address        (address),      // input  (from CPU)
            .write          (write),        // input  (from CPU)
            .data_in        (to_memory),    // input  (from CPU)
            .data_out       (from_memory),  // output (to CPU)
            // PORTS
            .port_in_00     (ZERO),         // input
            .port_in_01     (ZERO),         // input
            .port_in_02     (ZERO),         // input
            .port_in_03     (ZERO),         // input
            .port_in_04     (ZERO),         // input
            .port_in_05     (ZERO),         // input
            .port_in_06     (ZERO),         // input
            .port_in_07     (ZERO),         // input
            .port_in_08     (ZERO),         // input
            .port_in_09     (ZERO),         // input
            .port_in_10     (ZERO),         // input
            .port_in_11     (ZERO),         // input
            .port_in_12     (ZERO),         // input
            .port_in_13     (ZERO),         // input
            .port_in_14     (ZERO),         // input
            .port_in_15     (ZERO),         // input
            .port_out_00    (port_out_00),  // output
            .port_out_01    (port_out_01),  // output
            .port_out_02    (port_out_02),  // output
            .port_out_03    (port_out_03),  // output
            .port_out_04    (port_out_04),  // output
            .port_out_05    (port_out_05),  // output
            .port_out_06    (port_out_06),  // output
            .port_out_07    (port_out_07),  // output
            .port_out_08    (port_out_08),  // output
            .port_out_09    (port_out_09),  // output
            .port_out_10    (port_out_10),  // output
            .port_out_11    (port_out_11),  // output
            .port_out_12    (port_out_12),  // output
            .port_out_13    (port_out_13),  // output
            .port_out_14    (port_out_14),  // output
            .port_out_15    (port_out_15)   // output
        );
    end

endmodule
