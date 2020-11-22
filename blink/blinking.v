module blinking (
    input CLOCK_50,
    output LED
);

    reg [32:0] counter; // 33 bit counter 
    reg state; // single bit state
    
    assign LED = state;
    
    always @ (posedge CLOCK_50) begin
        counter <= counter + 1; // increment counter on clock cycle
        state <= counter[18]; // whenever 18'th bit is 1 LED is ON  
    end

endmodule