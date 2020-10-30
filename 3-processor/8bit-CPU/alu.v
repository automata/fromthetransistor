module alu(
    input wire [7:0] A,
    input wire [7:0] B,
    input wire [2:0] SEL,
    output reg [3:0] NZVC,
    output reg [7:0] RESULT
);
    // ALU is pure combinational logic
    // integers are represented in two's complement (negatives: invert the digits and add 1)
    // 8bit gives us a range of [-128, 127].

    // A and B are assumed to be in this range i.e. no overflow flag will be
    //   triggered if A or B are outside of [-128, 127]

    always @ (A, B, SEL)
        case(SEL)
            3'b000: begin: ADD_AB: A = A + B
                        // carry + result
                        { NZVC[0], RESULT } = A + B;

                        // negative flag
                        NZVC[3] = RESULT[7];

                        // zero flag
                        if (RESULT == 0)
                            NZVC[2] = 1;
                        else
                            NZVC[2] = 0;

                        // overflow
                        if ((A[7] == 0 && B[7] == 0 && RESULT[7] == 1) ||
                            (A[7] == 1 && B[7] == 1 && RESULT[7] == 0))
                            NZVC[1] = 1;
                        else
                            NZVC[1] = 0;
                    end
            3'b001: begin: SUB_AB
                        // carry + result
                        { NZVC[0], RESULT } = A - B;

                        // negative flag
                        NZVC[3] = RESULT[7];

                        // zero flag
                        if (RESULT == 0) NZVC[2] = 1;
                        else NZVC[2] = 0;

                        // overflow
                        if (A[7] != RESULT[7]) NZVC[1] = 1;
                        else NZVC[1] = 0;
                    end
            3'b010: begin: AND_AB: A = A & B
                        RESULT = A & B;

                        // negative flag
                        NZVC[3] = RESULT[7];

                        // zero flag
                        if (RESULT == 0) NZVC[2] = 1;
                        else NZVC[2] = 0;
                    end
            3'b011: begin: OR_AB
                        RESULT = A | B;

                        // negative flag
                        NZVC[3] = RESULT[7];

                        // zero flag
                        if (RESULT == 0) NZVC[2] = 1;
                        else NZVC[2] = 0;
                    end
            3'b100: begin: INCA
                        // carry + result
                        { NZVC[0], RESULT } = A + 1;

                        // negative flag
                        NZVC[3] = RESULT[7];

                        // zero flag
                        if (RESULT == 0)
                            NZVC[2] = 1;
                        else
                            NZVC[2] = 0;

                        // overflow
                        if ((A[7] != RESULT[7])) NZVC[1] = 1;
                        else NZVC[1] = 0;
                    end
            3'b101: begin: INCB:
                        // carry + result
                        { NZVC[0], RESULT } = B + 1;

                        // negative flag
                        NZVC[3] = RESULT[7];

                        // zero flag
                        if (RESULT == 0)
                            NZVC[2] = 1;
                        else
                            NZVC[2] = 0;

                        // overflow
                        if ((B[7] != RESULT[7])) NZVC[1] = 1;
                        else NZVC[1] = 0;
                    end
            3'b110: begin: DECA:
                        // carry + result
                        { NZVC[0], RESULT } = A - 1;

                        // negative flag
                        NZVC[3] = RESULT[7];

                        // zero flag
                        if (RESULT == 0)
                            NZVC[2] = 1;
                        else
                            NZVC[2] = 0;

                        // overflow
                        if ((A[7] != RESULT[7])) NZVC[1] = 1;
                        else NZVC[1] = 0;
                    end
            3'b111: begin: DECB:
                        // carry + result
                        { NZVC[0], RESULT } = B - 1;

                        // negative flag
                        NZVC[3] = RESULT[7];

                        // zero flag
                        if (RESULT == 0)
                            NZVC[2] = 1;
                        else
                            NZVC[2] = 0;

                        // overflow
                        if ((B[7] != RESULT[7])) NZVC[1] = 1;
                        else NZVC[1] = 0;
                    end
            default: begin
                        RESULT = 8'hXX;
                        NZVC = 4'hX;
                        end
        endcase

endmodule
