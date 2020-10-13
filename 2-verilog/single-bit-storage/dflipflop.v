`timescale 1ns/1ps
// dflipflop with async reset
module dflipflop(output reg Q, Qn, input wire D, clk, reset, preset, enable);
    initial begin
        $display("dflipflop with async reset");
    end

    always @ (posedge clk or posedge reset) begin
        if (reset) begin
            Q <= 1'b0;
            Qn <= 1'b1;
        end else if (preset) begin
            Q <= 1'b1;
            Qn <= 1'b0;
        end else begin
            if (enable) begin
                Q <= D;
                Qn <= ~D;
            end
        end
    end
endmodule
