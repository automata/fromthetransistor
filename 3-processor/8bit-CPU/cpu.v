module cpu(
    input wire clk, reset,
    input wire [7:0] from_memory,   // data bus from memory
    output reg [7:0] to_memory,     // data bus to memory
    output reg [7:0] address,       // address bus to memory (index into memory)
    output reg write                // can write to memory?
);

    always @ (posedge clk or negedge reset)
    begin
        // the control unit is called directly from the data_path
        // as it is the main FSM that controls the flow of data in the cpu
        data_path dp(
            .clk            (clk),
            .reset          (reset),
            .from_memory    (from_memory),
            .to_memory      (to_memory)
            .address        (address)
        );
    end

endmodule;
