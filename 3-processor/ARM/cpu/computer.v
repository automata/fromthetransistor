module computer(
    input wire clk,
    input wire reset
);
    bit [31:0] address;
    bit [31:0] to_memory;
    bit [31:0] from_memory;
    bit write;

    cpu _cpu(
        .clk            (clk),
        .reset          (reset),
        .from_memory    (from_memory),
        .to_memory      (to_memory),
        .write          (write)
    );

    memory _memory(
        .clk            (clk),
        .reset          (reset),
        .data_in        (to_memory),
        .address        (address),
        .write          (write),
        .data_out       (from_memory)
    );

endmodule
