## Verilog
```verilog
module hello;
    initial begin
        $display("hello world"); $finish;
    end
endmodule
```

### What is Verilog?
- hardware description language i.e. describe circuits textually
- in order to map the code to an FPGA, you need to `synthesize` it.
- 3 main levels of (digital) logic description:
    - behavioural (non-synthesizable)
    - register transfer level (i.e. where does data go?) (automatically converted to gate-level, so synthesizable)
    - gate logic (lowest level) (synthesizable)
- code can be written in all 3 description levels in Verilog; you manually replace behavioural constructs with RTL level code when it's time to synthesize.

### Language intro
- all code lives in a module, one module per file.
- C-like syntax for most operators and directives (see [cheatsheet](https://marceluda.github.io/rp_dummy/EEOF2018/Verilog_Cheat_Sheet.pdf))
- all assignments are executed concurrently unless specified otherwise (since this described hardware, hence nothing is sequential by nature)
    - that means that the below (*combinational logic*) code will be synthesized to 3 separate circuits; all assignments will be run concurrently:
        ```verilog
        assign A = 1;
        assign B = 1;
        assign C = 1;

        ```
- combinational elements can be modelled using `assign` and `always` statements
- sequential elements can only be modelled using `always` statements
- to test the logic you can write test benches (although I think I'll write those directly in verilator's C++ top-level file)

## Resources
- [zipcpu verilog crash course](https://zipcpu.com/blog/2017/06/21/looking-at-verilator.html)
- [verilator](https://www.veripool.org/wiki/verilator)
- [verilog cheatsheet](https://marceluda.github.io/rp_dummy/EEOF2018/Verilog_Cheat_Sheet.pdf)
- [see signal waves nicely](http://gtkwave.sourceforge.net/)
- [verilog in one day](http://www.asic-world.com/verilog/)
- [Quick Start Guide to Verilog](https://www.springer.com/gp/book/9783030105518)
