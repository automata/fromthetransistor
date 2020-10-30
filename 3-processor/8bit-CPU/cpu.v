module cpu(
    input wire clk, reset,
    input wire [7:0] from_memory,   // data bus from memory
    output reg [7:0] to_memory,     // data bus to memory
    output reg [7:0] address,       // address bus to memory (index into memory)
    output reg write                // can write to memory?
);

    always @ (posedge clk or negedge reset)
    begin
        control_unit cu(
            .clk            (clk),
            .reset          (reset),
            .write          (write)
        );

        data_path dp(
            .clk            (clk),
            .reset          (reset),
            .from_memory    (from_memory),
            .to_memory      (to_memory)
            .address        (address)
        );
    end

endmodule;
