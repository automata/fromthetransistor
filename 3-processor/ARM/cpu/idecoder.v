/* decodes the byte-code encoded instructions from memory */
module idecoder(
    input wire instruction,
    output bit o_ldr, // load
    output bit o_str, // store
    output bit o_b,   // branch
    output bit o_bl,  // branch with link
    output bit o_mov, // move
    output bit o_mvn, // move not
    output bit o_add, // add
    output bit o_sub, // subtract
    output bit o_rsb, // reverse subtract
    output bit o_adc, // add with carry
    output bit o_sbc, // subtract with carry
    output bit o_rsc, // reverse subtract with carry
    output bit o_and, // and
    output bit o_bic, // bit clear
    output bit o_eor, // exclusive or
    output bit o_orr, // or
    output bit o_mul, // multiply
    output bit o_mla, // multiply accummulate
    output bit o_cmp, // compare
    output bit o_cmn, // compare not
    output bit o_tst, // test
    output bit o_teq, // test equivalent
    output bit o_swp, // swap
    output bit o_swi, // software interrupt
    output bit [3:0] o_cond,
    output bit o_byte,
    output bit o_set, // whether the instruction will set NZVC on execution
    output bit [31:0] label, // address to branch to
    output bit [4:0] rd, // destination register for instruction (label for b/bl)
    output bit [4:0] rn,
    output bit [4:0] rm,
    output bit [4:0] rs,
    output bit o_const_offset,
    output bit o_reg_offset,
    output bit o_scaled_reg_offset,
    output bit o_immediate,
    output bit o_pre_index,
    output bit o_post_index
);

    always_comb begin
        o_cond = instruction[31:28];
    end

endmodule
