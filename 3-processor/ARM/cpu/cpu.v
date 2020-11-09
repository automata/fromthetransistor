module cpu(
    // ---- clocks and timing ----
    input wire MCLK,
    input wire nWAIT,
    output reg ECLK,

    // ---- interrupts ----
    input wire nIRQ,
    input wire nFIQ,
    input wire ISYNC,

    // ---- bus controls ----
    input wire nRESET,
    input wire BUSEN, // bus enable i.e. which bus is active of (DIN, DOUT, D)
    output reg HIGHZ,
    output reg nHIGHZ,
    input wire nENIN,
    output reg nENOUT,
    output reg nENOUTI,
    input wire ABE,
    input wire ALE,
    input wire APE,
    input wire DBE,
    input wire TBE,
    output reg BUSDIS,
    output reg ECAPCLK,

    // ---- power ----
    input wire VDD, // transistor drain, positive voltage
    input wire VSS, // transistor source, ground

    // ---- debug ----
    input wire DBGRQ,
    input wire BREAKPT,
    output reg DBGACK,
    output reg nEXEC,
    input wire EXTERN1,
    input wire EXTERN0,
    input wire DBGEN,
    output reg RANGEOUT0,
    output reg RANGEOUT1,
    output reg DBGRQI,
    output reg COMMRX,
    output reg COMMTX,

    // ---- boundary scan ----
    input wire TCK,
    input wire TMS,
    input wire TDI,
    input wire nTRST,
    output reg TDO,
    output reg [3:0] TAPSM,
    output reg [3:0] IR,
    output reg nTDOEN,
    output reg TCK1,
    output reg TCK2,
    output reg [3:0] SCREG,

    // ---- bounday scan control ----
    output reg [1:0] sCONTROL,

    // ---- processor mode ----
    output reg [4:0] nM,

    // ---- memory interface ----
    output reg [31:0] A, // address in memory; all addresses are byte addresses, this increments by 4 each cycle
    output reg [31:0] DOUT,
    output reg [31:0] D,
    output reg [31:0] DIN,
    output reg nMREQ,
    output reg SEQ,
    output reg nRW,
    output reg [1:0] MAS, // encodes the size of the transfer: word, halfword, byte
    input wire [3:0] BL, // allow latching of bytes from word wide buses

    // indicates to an arbiter that an atomic operation is being performed on the bus
    // normally LOW, but set HIGH to indicate that a SWP or SWPB instruction is executed
    output reg LOCK,

    // ---- memory management interface ----
    input wire ABORT,

    // ---- coprocessor interface ----
    output reg nOPC,
    output reg nCPI,
    input wire CPA,
    input wire CPB
);

// contains control_unit and processing unit

endmodule
