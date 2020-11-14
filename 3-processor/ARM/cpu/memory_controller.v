/* verilator lint_off UNUSED */
/* verilator lint_off UNDRIVEN */
/*
* ARM memory controller.
*
* Given an address in memory, the controller either:
* - fetches the data at that address either sequentially or non-sequentially and then puts that data on
*   the bus making it available to the processor
* - takes the data given by the processor from the bus and puts it into memory at the specified address
*
* There are two types of memory accesses, controlled by nmreq and seq:
* - nmreq 0  seq 0: nonsequential: processor requests a transfer to or from an address that is unrelated
*   to the address used in the previous cycle
* - nmreq 0  seq 1: sequential: processor requests a transfer to or from an address that is related to the
*   one in the previous cycle
*
* *********** SIGNALS ************
* mclk: main clock for all memory accesses and processor operations;
* nreset:   when high for 1 clock cycle, the processor starts from address 0x0;
*
* ale:  address latch enable;
*       the address bus, lock, mas, nrw, nopc signals are latched when this is held low
*       (e.g. when interfacing with a ROM, the address must be valid until after the data is read)
* lock: lock any other device from accessing the memory
* mas:  memory access size - 00 = byte, 01 = halfword, 10 = word
* nopc: low if the processor is fetching an instruction from memory
* nwait: used to extend an access over a number of cycles of mclk;
*        should change when mclk is low;
*        used: low, not used: high;
* nrw:  read: low, write: high;
*
* nmreq: not memory request; when the processor requires memory access during the following cycles, this is low
* seq: high on sequential access
*
* din[31:0]:    unidirectional bus for data and instructions from memory to processor;
*               sampled during read cycles on the falling edge of mclk;
* dout[31:0]:   data from processor to memory;
*               during write cycles the output data becomes valid while mclk is low,
*               and remains valid until after the falling edge of mclk;
* sabort:       memory request not allowed
* bl[3:0]:      byte latch control;
*               which bytes to latch from the data bus on the falling edge of the clock
*/
module memory_controller(
    input wire mclk,
    input wire nreset,
    input wire ale,
    input wire mas,
    input wire nopc,
    input wire nrw,
    input wire nmreq,
    input wire seq,
    input wire [31:0] dout,
    input wire [3:0] bl,
    input wire [31:0] address_bus,
    output logic lock,
    output logic nwait,
    output logic [31:0] din,
    output logic sabort
);
    localparam ROM_MEMORY_SIZE = 64000, RW_MEMORY_SIZE = 64000;

    logic [31:0] reg_address_bus;
    logic [31:0] reg_din;
    logic [31:0] reg_dout;
    logic reg_lock;
    logic reg_mas;
    logic reg_nrw;
    logic reg_nopc;

    // latch memory access info
    always_ff @ (posedge mclk) begin
        if (~ale) begin
            reg_address_bus <= address_bus;
            reg_lock        <= lock;
            reg_mas         <= mas;
            reg_nrw         <= nrw;
            reg_nopc        <= nopc;
            reg_dout        <= dout; // data coming from the processor
        end else begin
            if (seq)
                reg_address_bus <= address_bus;
        end
    end

    // abort if address is wrong or trying to write to ROM
    always_comb begin
        if (nrw && reg_address_bus + 4 < ROM_MEMORY_SIZE || nmreq) begin
            sabort = 1'b1;
        end
    end

    // reset address to zero if nreset is high more than 1 clock cycle
    logic [1:0] reset_counter;
    always_ff @ (posedge mclk) begin
        if (nreset && reset_counter >= 1) begin
            reg_address_bus <= 32'h00000000;
            reset_counter <= 2'b00;
        end
        reset_counter <= reset_counter + 1;
    end

    // init memory
    rom_memory #(.SIZE(ROM_MEMORY_SIZE)) _rom (
        .mclk(mclk),
        .enable(~nopc && ~nmreq && ~sabort),
        .address(reg_address_bus),
        .data_out(reg_din)
    );

    rw_memory #(.SIZE(RW_MEMORY_SIZE)) _rw (
        .mclk(mclk),
        .enable(nopc && ~nmreq && ~sabort),
        .write_enable(nrw),
        .address(reg_address_bus),
        .data_in(reg_dout),
        .data_out(reg_din)
    );

    // update buses
    always_comb begin
        din = reg_din; // data going to the processor
    end

    // sequential memory access
    always_ff @ (posedge mclk) begin
        if (seq && ale) begin
        end
    end

endmodule
