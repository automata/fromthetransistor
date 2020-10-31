module rom_128x8_sync(
    input wire clk,
    input wire [7:0] address,
    output reg [7:0] data_out
);

    // ------------------------ INSTRUCTION SET -----------------------------
    // load and stores
    parameter LDA_IMM = 8'h10; // <data> load register A using immediate addressing with <data>
    parameter LDA_DIR = 8'h11; // <addr> load register A using direct addressing from <addr>
    parameter LDB_IMM = 8'h12; // <data> load register B using immediate addressing with <data>
    parameter LDB_DIR = 8'h13; // <addr> load register B using direct addressing from <addr>
    parameter STA_DIR = 8'h14; // <addr> store register A in memory to <addr> (direct addressing)
    parameter STB_DIR = 8'h15; // <addr> store register B in memory to <addr> (direct addressing)
    // data manipulations (ALU stuff)
    parameter ADD_AB  = 8'h20; // A = A + B
    parameter SUB_AB  = 8'h21; // A = A - B
    parameter AND_AB  = 8'h22; // A = A & B
    parameter OR_AB   = 8'h23; // A = A | B
    parameter INCA    = 8'h24; // A = A + 1
    parameter INCB    = 8'h25; // B = B + 1
    parameter DECA    = 8'h26; // A = A - 1
    parameter DECB    = 8'h27; // B = B - 1
    // branches
    parameter BRA     = 8'h30; // <addr> branch always to <address>
    parameter BNU     = 8'h31; // <addr> branch to <addr> if N=1 (negative flag)
    parameter BND     = 8'h32; // <addr> branch to <addr> if N=0 (negative flag
    parameter BZU     = 8'h33; // <addr> branch to <addr> if Z=1 (zero flag)
    parameter BZD     = 8'h34; // <addr> branch to <addr> if Z=0 (zero flag)
    parameter BVU     = 8'h35; // <addr> branch to <addr> if V=1 (two's complement overflow flag)
    parameter BVD     = 8'h36; // <addr> branch to <addr> if V=0 (two's complement overflow flag)
    parameter BCU     = 8'h37; // <addr> branch to <addr> if C=1 (carry flag)
    parameter BCD     = 8'h38; // <addr> branch to <addr> if C=0 (carry flag)

    reg [7:0] ROM [0:127];
    initial begin           // not synthesizable unless on Xilinx
        ROM[0] = LDA_IMM;   // opcode
        ROM[1] = 8'hAA;     // put this value into register A
        ROM[2] = LDB_IMM;   // opcode
        ROM[3] = 8'hAA;     // put this value into register A
        ROM[4] = LDA_DIR;
        ROM[5] = 8'h0F;
        ROM[6] = LDB_DIR;
        ROM[7] = 8'h0F;
        ROM[15] = 8'hFF;
    end

    reg enable;
    always @ (address)
        if (address < 128)  enable = 1'b1;
        else                enable = 1'b0;

    wire [6:0] truncated_address; // ROM requires a 7 bit index, but address is 8, so we truncate
    assign truncated_address = address[6:0];

    always @ (posedge clk)
        if (enable) data_out <= ROM[truncated_address]; // will synthesize to 8 * 128 flipflops so 128 8bit registers

endmodule
