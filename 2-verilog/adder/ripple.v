// Verilator lint_off UNOPTFLAT
/*
* UNOPTFLAT is usually a worrisome error as it points to a
* loop in the combinational logic. Here however Verilator
* gets it wrong: it thinks that all of the elements of
* m_carry are a single signal and since one carry value determines
* the next value of the same signal (submodule call), it considers it
* a logic loop; this can be fixed by unrolling all the submodules and
* putting all the code from them in this single file, wrapped in an always @
* block, thus getting rid of the genvar. But I'm too lazy to do that now.
*/
`timescale 1ns/1ps
module ripple
    #(parameter N = 16) // N-bits ripple carry adder
    (output wire [N:0] Sum,
     input wire [N-1:0] A, B);

    wire [N:0] m_carry;
    wire [N-1:0] m_sum;
    assign m_carry[0] = 1'b0;

    genvar ix;
    generate
        for (ix = 0; ix < N; ix = ix + 1) begin
            full_adder fainst
            (
                .Sum(m_sum[ix]),
                .Cout(m_carry[ix+1]),
                .A(A[ix]),
                .B(B[ix]),
                .Cin(m_carry[ix])
            );
        end
    endgenerate

    assign Sum = {m_carry[N], m_sum}; // concatenate

endmodule
