/* verilator lint_off WIDTH */
module alu(
    input wire [3:0] opcode,
    input wire [31:0] a, // from register bank
    input wire [31:0] b, // from barrel shifter
    input wire carry_in,
    output logic signed [31:0] result,
    output logic [3:0] nzvc
);
    logic [31:0] a_compl, b_compl, temp;
    logic carry_out;

    always @ (*) begin
        a_compl = (~a + 32'h00000001);
        b_compl = (~b + 32'h00000001);
        case (opcode)
            4'b0000: begin: AND
                nzvc = 4'b0000;
                result = a & b;
                nzvc[3] = result[31];
                nzvc[2] = result == 0 ? 1'b1 : 1'b0;
            end
            4'b0001: begin: EOR
                nzvc = 4'b0000;
                result = a ^ b;
                nzvc[3] = result[31];
                nzvc[2] = result == 0 ? 1'b1 : 1'b0;
            end
            4'b0010: begin: SUB
                nzvc = 4'b0000;
                {carry_out, result} = a + b_compl;
                nzvc[3] = result[31];
                nzvc[2] = result == 0 ? 1'b1 : 1'b0;
                nzvc[1] = carry_out ^ a[31] ^ b_compl[31] ^ result[31];
                nzvc[0] = carry_out;
            end
            4'b0011: begin: RSB
                nzvc = 4'b0000;
                {carry_out, result} = b + a_compl;
                nzvc[3] = result[31];
                nzvc[2] = result == 0 ? 1'b1 : 1'b0;
                nzvc[1] = carry_out ^ b[31] ^ a_compl[31] ^ result[31];
                nzvc[0] = carry_out;
            end
            4'b0100: begin: ADD
                nzvc = 4'b0000;
                {carry_out, result} = a + b;
                nzvc[3] = result[31];
                nzvc[2] = result == 0 ? 1'b1 : 1'b0;
                nzvc[1] = carry_out ^ a[31] ^ b[31] ^ result[31];
                nzvc[0] = carry_out;
            end
            4'b0101: begin: ADC
                nzvc = 4'b0000;
                {carry_out, result} = a + b + carry_in;
                nzvc[3] = result[31];
                nzvc[2] = result == 0 ? 1'b1 : 1'b0;
                nzvc[1] = carry_out ^ a[31] ^ b[31] ^ result[31];
                nzvc[0] = carry_out;
            end
            4'b0110: begin: SBC
                nzvc = 4'b0000;
                {carry_out, result} = a + b_compl - 1 + carry_in;
                nzvc[3] = result[31];
                nzvc[2] = result == 0 ? 1'b1 : 1'b0;
                nzvc[1] = carry_out ^ a[31] ^ b_compl[31] ^ result[31];
                nzvc[0] = carry_out;
            end
            4'b0111: begin: RSC
                nzvc = 4'b0000;
                {carry_out, result} = b + a_compl + 1 - carry_in;
                nzvc[3] = result[31];
                nzvc[2] = result == 0 ? 1'b1 : 1'b0;
                nzvc[1] = carry_out ^ b[31] ^ a_compl[31] ^ result[31];
                nzvc[0] = carry_out;
            end
            4'b1000: begin: TST // only updates flags
                nzvc = 4'b0000;
                result = 32'hXXXXXXXX;
                temp = a & b;
                nzvc[3] = temp[31];
                nzvc[2] = temp == 0 ? 1'b1 : 1'b0;
            end
            4'b1001: begin: TEQ // only updates flags
                nzvc = 4'b0000;
                result = 32'hXXXXXXXX;
                temp = a ^ b;
                nzvc[3] = temp[31];
                nzvc[2] = temp == 0 ? 1'b1 : 1'b0;
            end
            4'b1010: begin: CMP
                nzvc = 4'b0000;
                result = 32'hXXXXXXXX;
                {carry_out, temp} = a + b_compl;
                nzvc[3] = temp[31];
                nzvc[2] = temp == 0 ? 1'b1 : 1'b0;
                nzvc[1] = carry_out ^ a[31] ^ b_compl[31] ^ temp[31];
                nzvc[0] = carry_out;
            end
            4'b1011: begin: CMN
                nzvc = 4'b0000;
                result = 32'hXXXXXXXX;
                {carry_out, temp} = a + b;
                nzvc[3] = temp[31];
                nzvc[2] = temp == 0 ? 1'b1 : 1'b0;
                nzvc[1] = carry_out ^ a[31] ^ b[31] ^ temp[31];
                nzvc[0] = carry_out;
            end
            4'b1100: begin: ORR
                nzvc = 4'b0000;
                result = a | b;
                nzvc[3] = result[31];
                nzvc[2] = result == 0 ? 1'b1 : 1'b0;
            end
            4'b1101: begin: MOV
                nzvc = 4'b0000;
                result = b;
                nzvc[3] = result[31];
                nzvc[2] = result == 0 ? 1'b1 : 1'b0;
            end
            4'b1110: begin: BIC
                nzvc = 4'b0000;
                result = a & (~b);
                nzvc[3] = result[31];
                nzvc[2] = result == 0 ? 1'b1 : 1'b0;
            end
            4'b1111: begin: MVN
                nzvc = 4'b0000;
                result = ~b;
                nzvc[3] = result[31];
                nzvc[2] = result == 0 ? 1'b1 : 1'b0;
            end
            default: result = 32'hXXXXXXXX;
        endcase
    end
endmodule
