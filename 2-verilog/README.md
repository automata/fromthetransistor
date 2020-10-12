## Verilog
```verilog
module hello;
    initial begin
        $display("hello world"); $finish;
    end
endmodule
```

- since I don't currently have an FPGA at hand, all Verilog code is synthesized and simulated with [Verilator](https://www.veripool.org/wiki/verilator)
- for arch systems, install `verilator` with `yay -S verilator`. The headers headers will be in `/usr/share/verilator/include/` (if not there, try `verilator -V`)
    - has `systemc` as a dependency when generating waveform traces: `yay -S systemc`
- [GTKWave](http://gtkwave.sourceforge.net/) is used to visualize the signal waveforms: `yay -S gtkwave`

### What is Verilog?
- hardware description language i.e. describe circuits textually
- in order to map the code to an FPGA, you need to `synthesize` it.
- 3 main levels of (digital) logic description:
    - behavioural (non-synthesizable)
    - register transfer level (i.e. where does data go?) (automatically converted to gate-level, so synthesizable)
    - gate logic (lowest level) (synthesizable)
- code can be written in all 3 description levels in Verilog; you manually replace behavioural constructs with RTL level code when it's time to synthesize.
- in its essence, it models sequential and combinational logic through text

### Language intro
- everything is based on signals
- all signals are associated with a data type which in turn can take on some values
- all code lives in a module, one module per file.
- C-like syntax for most operators and directives (see [cheatsheet](https://marceluda.github.io/rp_dummy/EEOF2018/Verilog_Cheat_Sheet.pdf))
- data types:
    - nets i.e. interconnets; need to always be driven; most common one is the *wire* (so no storage)
    - reg i.e. logic storage (not actually a register!!!); can store 0, 1, X, Z.
    - integer; supports multiple bases
        - `8'b1011_0000; // 8 binary bits`
        - can have hex, decimal, binary etc.
    - real
    - time aka realtime i.e. unsigned 64bit
- language is weakly typed, so automatic conversions between types are supported; padding is done automatically
- vectors:
    - `wire [7:0] sum; // 8bit net`
- arrays:
    - `reg [7:0] mem[0:4095]; // an array of 4096 8bit regs`

#### Value set
- 0: logic zero
- 1: logic one
- x or X: unknown or uninitialized
- z or Z: high impedance, tri-stated or floating (oo resistance)

- all of these have an associated strength, in order to resolve the value of a signal when driven by multiple sources

- when a signal is driven by multiple drivers, it will take on the value of the driver with the highest strength; if two drivers have the same strenght, then the value is unknown (X || x).

### (Continuous) Assignments
- all assignments are executed concurrently unless specified otherwise (since this described hardware, hence nothing is sequential by nature)
    - that means that the below (*combinational logic*) code will be synthesized to 3 separate circuits; all assignments will be run concurrently:
        ```verilog
        assign A = 1;
        assign B = 1;
        assign C = 1;

        ```
    - the `=` here is a `continous assignment`
    - a gate delay can be added for both the rising and falling transitions of the continous assignment (scale set with `timescale`)
        ```verilog
        timescale 1ns/1ps
        module delayed
            assign #1 A = 4; // delay of 1 on all transitions
            assign #(2, 3) F = 1; // delay of 2ns on rise, 3ns on fall
        endmodule
        ```
        ```verilog
        timescale 1ns/1ps
        module delayed (input wire x, y, output wire result)
            assign #1 result = x & y; // if x and y are both high, result is high 1ns later than then the instant when both become high, and low 1ns later than the instant when one becomes low
        endmodule
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
