/*
8 bit address to reference 0..255 locations of 8bits each
256 total bytes:
    128: program (ROM)
    96: data (RW)
    32: IO (16 in, 16 out)
entire address is loaded on the bus at once
*/
module memory
    (input wire clk, reset,
     input wire [7:0] address,
     input wire write,
     input wire [7:0] data_in,
     // input ports address space: 224..239 (xE0..xEF)
     input reg [7:0] port_in_00,
     input reg [7:0] port_in_01,
     input reg [7:0] port_in_02,
     input reg [7:0] port_in_03,
     input reg [7:0] port_in_04,
     input reg [7:0] port_in_05,
     input reg [7:0] port_in_06,
     input reg [7:0] port_in_07,
     input reg [7:0] port_in_08,
     input reg [7:0] port_in_09,
     input reg [7:0] port_in_10,
     input reg [7:0] port_in_11,
     input reg [7:0] port_in_12,
     input reg [7:0] port_in_13,
     input reg [7:0] port_in_14,
     input reg [7:0] port_in_15,
     // output ports address space: 240..255 (xF0..xFF)
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
     output reg [7:0] port_out_15,
     // data_out is written on the CPU data bus
     // can be data from the RW or ROM memories, OR simply the input ports
     // so we multiplex it on <address>
     output reg [7:0] data_out);

    reg [7:0] rom_data_out;
    reg [7:0] rw_data_out;

    // handle clocked write to data_out
    rom_128x8_sync program_memory(
        .clk            (clk),
        .address        (address),
        .data_out       (rom_data_out)
    );

    // handle clocked read/write to data_out
    rw_96x8_sync data(
        .clk            (clk),
        .write          (write),
        .address        (address),
        .data_in        (data_in),
        .data_out       (rw_data_out)
    );

    // set value of output ports
    output_ports outputs(
        .address        (address),
        .clk            (clk),
        .reset          (reset),
        .data_in        (data_in),     // to write to output port at <address>
        .write          (write),
        .port_out_00    (port_out_00),
        .port_out_01    (port_out_01),
        .port_out_02    (port_out_02),
        .port_out_03    (port_out_03),
        .port_out_04    (port_out_04),
        .port_out_05    (port_out_05),
        .port_out_06    (port_out_06),
        .port_out_07    (port_out_07),
        .port_out_08    (port_out_08),
        .port_out_09    (port_out_09),
        .port_out_10    (port_out_10),
        .port_out_11    (port_out_11),
        .port_out_12    (port_out_12),
        .port_out_13    (port_out_13),
        .port_out_14    (port_out_14),
        .port_out_15    (port_out_15)
    );

    // handle non-clocked read from input ports and set appropriate data_out
    always @ (address, rom_data_out, rw_data_out,
              port_in_00, port_in_01, port_in_02, port_in_03,
              port_in_04, port_in_05, port_in_06, port_in_07,
              port_in_08, port_in_09, port_in_10, port_in_11,
              port_in_12, port_in_13, port_in_14, port_in_15)
        begin: MUX
            if      (address < 128)                     data_out = rom_data_out;
            else if (address >= 128 && address < 224)   data_out = rw_data_out;
            else if (address == 8'hE0)                  data_out = port_in_00;
            else if (address == 8'hE1)                  data_out = port_in_01;
            else if (address == 8'hE2)                  data_out = port_in_02;
            else if (address == 8'hE3)                  data_out = port_in_03;
            else if (address == 8'hE4)                  data_out = port_in_04;
            else if (address == 8'hE5)                  data_out = port_in_05;
            else if (address == 8'hE6)                  data_out = port_in_06;
            else if (address == 8'hE7)                  data_out = port_in_07;
            else if (address == 8'hE8)                  data_out = port_in_08;
            else if (address == 8'hE9)                  data_out = port_in_09;
            else if (address == 8'hEA)                  data_out = port_in_10;
            else if (address == 8'hEB)                  data_out = port_in_11;
            else if (address == 8'hEC)                  data_out = port_in_12;
            else if (address == 8'hED)                  data_out = port_in_13;
            else if (address == 8'hEE)                  data_out = port_in_14;
            else if (address == 8'hEF)                  data_out = port_in_15;
        end

endmodule;
