module hello;
    initial begin
        $display("hello world"); $finish; // $display and $finish are verilator specific directives
    end
endmodule
