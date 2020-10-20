## Verilog
```verilog
module hello;
    initial begin
        $display("hello world"); $finish;
    end
endmodule
```

- since I don't currently have an FPGA at hand, all Verilog code is synthesized and simulated with [Verilator](https://www.veripool.org/wiki/verilator) and [yosys](http://www.clifford.at/yosys/)
- for arch systems, install `verilator` with `yay -S verilator`. Same with `yosys`. To view the designs, install `graphviz && xdot`. For **verilator**, the headers will be in `/usr/share/verilator/include/` (if not there, see `verilator -V`)
    - `systemc` is a dependency for generating waveform traces: `yay -S systemc`
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
- **module inputs** are by default wires (obvs, you can connect modules inbetween only with wires)
- **module outputs** are either *reg* or *wire*

#### Value set
- 0: logic zero
- 1: logic one
- x or X: unknown or uninitialized
- z or Z: high impedance, tri-stated or floating (oo resistance)

- all of these have an associated strength, in order to resolve the value of a signal when driven by multiple sources

- when a signal is driven by multiple drivers, it will take on the value of the driver with the highest strength; if two drivers have the same strenght, then the value is unknown (X || x).

### Combinational Logic
- output directly depend on the current value of inputs --> a model that continuously performs signal assignments provides an accurate model of this circuit behaviour.
- all assignments are executed concurrently unless specified otherwise (since this described hardware, hence nothing is sequential by nature)
    - that means that the below (*combinational logic*) code will be synthesized to 3 separate circuits; all assignments will be run concurrently:
        ```verilog
        assign A = 1;
        assign B = 1;
        assign C = 1;

        ```
    - the `=` here is a `continous assignment`
    - a gate delay can be added for both the rising and falling transitions of the continous assignment (scale set with `timescale`). **THIS IS NOT SYNTHESIZABLE** -- if you really want a delay use a simple counter dependent on the driving clock
        ```verilog
        `timescale 1ns/1ps
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
    - NOTE: primitives can all accept delays `not #2 U0 (...)` just like `assign`
- combinational elements can be modelled using `assign` and `always` statements
- sequential elements can only be modelled using `always` statements
- to test the logic you can write test benches (although I think I'll write those directly in verilator's C++ top-level file)

#### Gate Level Primitives
- provided by the language itself
- **not()**, **and()**, **nand()**, **or()**, **nor()**, **xor()**, **xnor()**
- each of these are instantiated as lower level subsystems (i.e. modules)
- benefits: number of inputs can be easily scaled **AND** you get a gate-level netlist so these are ready to be synthesized
    ```verilog
    module SystemX (output wire F,
                    input wire A, B, C);
        wire An, Bn, Cn; // internal nets
        wire m0, m2, m6;

        // output is listed first in the port mapping
        // not, and etc are all subsystems, so their name appears before the port list (U0, U1 etc)
        not U0 (An, A);
        not U1 (Bn, B);
        not U2 (Cn, C);

        and U3 (m0, An, Bn, Cn);
        and U4 (m2, An, B, Cn);
        and U5 (m6, A, B, Cn);
    endmodule
    ```
#### User Level Primitives
- nice for repeatable combinational logic
    ```verilog
    primitive SystemX_UDP(output F, input A, B, C); // this needs its own file just like a module
        table
        //  A B: C
            0 0: 1;
            0 1: 1;
            1 0: 0;
            1 1: 1;
        endtable
    endprimitive
    ```
    ```verilog
    module SystemX(output wire F, input wire A, B, C);
        SystemX_UDP U0 (F, A, B, C);
    endmodule
    ```
#### Constructs
- **for**-loops are synthesizable since they don't run some operations sequentially but rather replicate the inner calls **n** times (`for (int i = 0; i < n; i++)`) (unroll + expand)

### Sequential Logic
- D-flip-flops, register, counters, finite state machines etc.
- basically everything that depends on a clock and hence needs to hold state between clock ticks
- most of the constructs are single rate, meaning they update their state on the rising edge of the clock; you can also have double rate constructs, which update on the rising and falling edges.
- all based on **procedural assignments**, which are evaluated in the order they are listed, and act only on storage types (reg, integer, real, time)
- sequential logic written in `initial` and `always` blocks
#### Blocking and Non-blocking assignments
    ```verilog
    module tick;
        // initial block only runs at the beginning of the simulation and is not synthesizable (you can't give an initial value to voltages ;))
        // used in testbenches (@ZipCPU "I avoid test benches like the plague")
        initial begin
            Clock_TB = 1'b0;
        end

        // for the whole simulation, this will runs stuff line by line within it.
        always begin
            #10 Clock_TB = ~Clock_TB // "tick" the clock every 10 time units
        end

        always @(signal_1, signal_2) begin // always block is triggered only on when signal_1 is high OR when signal_2 is high
            signal_1_assignment ...
            signal_2_assignment ...
        end

        always @(posedge signal_1, negedge signal_2) begin // like above but trigger on a rising/falling edge
            signal_1_assignment ...
            signal_2_assignment ...
        end

        always @* begin
            // this triggers on any signal that is up and on the right-hand side of any assignment in this block
        end
    endmodule
    ```
- D-flip-flop
    ```verilog
    module ff(input Q, output D);
        always @(posedge clk) begin
            Q = D;
        end
    endmodule
    ```
- every procedural block has two types of assignments:
    - **blocking**: `a = b`
        - each assignment in the block is executed in parallel
        - if you use **all the inputs of the system with these kind of assignments in a procedural block, you get synthesizable combinational logic**
        - so they are basically synonymous to **continous assignments** (only benefit of using them here is that procedural blocks allow you to access more features of the language)
            ```verilog
            module blocking(output reg S, input wire, A, B, C); // triple xor
                reg n1;
                always @(A, B, C) begin
                    n1 = A ^ B;
                    S = n1 ^ C;
                end
            endmodule
            ```
    - **non-blocking**: `a <= b`
        - the assignment to the target signal is deferred until the end of the procedural block
        - when this behaviour is coupled with triggering the block off a clock signal, this approach can model synthesizable sequential logic circuits
        - **only generates** sequential logic (no way to describe circuits combinationally since assignment is deffered at the end of the block)
            ```verilog
            module dflipflip(output reg F, input wire, A, clk); // flip flip since both latches are driven by the same clock (non inverted on both)
                reg B;
                always @(posedge clk) begin
                    B <= A;
                    F <= B;
                end
            endmodule
            ```
- differences:
    - there's no difference between these assignments in a procedural block unless there are interdependencies in the assignments (i.e. on variable from LHS goes to RHS on a later assignment)
    ```verilog
    module nodiff(output reg Y, Z, input wire A, B, C)
        // both always blocks produce the same circuit
        always @ (A, B, C) begin
            Y = A & B;
            Z = B | C;
        end

        always @ (A, B, C) begin
            Y <= A & B;
            Z <= B | C;
        end
    endmodule
    ```
    - interdependencies means you will get different behaviour
        ```verilog
        module diff(output reg F, input wire A, clk);
            // the always blocks don't result in the same circuit
            reg B;

            // these assignments happen immediately, so F gets the updated value of A, which means that you get F = A, so one circuit element
            always @ (posedge clk) begin
                B = A;
                F = B;
            end

            // these assignments happen at the end of the procedural block, so that means that F will not be using the update value of B, but the initial one before A was assigned to it
            // so you get two circuit elements
            // it takes F two rising edges to get the value of B, instead of 1 as above
            always @ (posedge clk) begin
                B <= A;
                F <= B;
            end
        endmodule
        ```
- rule: use all inputs in the sensitivity list ==> combinational logic
    - rule of thumb: "Unless you're modelling a clocked flip flop, you should always use the default (`@*`) sensitivity list for a combinational block."
    - https://stackoverflow.com/questions/16312116/verilog-always-sensitivity-list
- if you write something like this:
    ```verilog
    module temp(input reg [1:0] in, output wire out);
    always @ (*)
    begin
        $display("here");
        out = in;
    end
    endmodule
    ```
    - since the input is a 2-bit bus, this block will trigger on each bit in `in` in simulation, but synthesis will fail unless you `genvar` it
#### Statement groups
- `begin` and `end` --> all statements run in order
    ```verilog
    module beginex();
        reg [7:0] mem;

        // at 0, mem gets assigned 0
        // 10 time units later, hex55
        // 15 time units later, hexAA
        initial
            begin: Example // name of module
                mem = 8'h00;
                #10 mem = 8'h55;
                #15 mem = 8'hAA;
            end
        end
    endmodule
    ```
- `fork` and `join` --> all statements run in parallel
    ```verilog
    module forkex(); // everything in absolute time
        reg [7:0] mem;

        // at 0, mem gets assigned 0
        // at 10, mem gets assigned hex55
        // at 15, mem gets assigned hexAA
        initial
            fork: Example
                mem = 8'h00;
                #10 mem = 8'h55;
                #15 mem = 8'hAA;
            join
        end
    endmodule
    ```
#### Other constructs in procedural blocks
```verilog
    begin: Example
        integer i; // local var, not visible outside the block
        i = 2;

        if (i == 2)
            ...;
        else if (i > 3)
            ...;
        else
            ...;

        case i
            2: ...
            3: ...
        endcase

        // loops
        while, forever, repeat, for

        // stop a loop with disable
        initial begin
            clk = 0;
            forever begin: loop_ex
                if (en == 1)
                    #10 clk = ~clk;
                else
                    disable loop_ex;
            end
        end
        
    end
```
- system tasks
    - not part of the circuit, just interaction. all begin with $ and are used through simulation
        ```verilog
        $display
        $write
        $monitor // printing occurs only when value is changed
        $fopen() // open file
        $fclose()
        $fdisplay()
        $fwrite()
        $fmonitor()

        // simulation control
        $finish
        $stop() // halts the simulation and enters interactive debug mode
        $time() // returns current time
        ```
### Testbenches
- avoid them like the plague, use verilator instead (see header `testbench.h`)

### Synthesis
- command: `yosys -S <input>.v -o synth.v`

## Vocab
- **netlist**: description of the connectivity of some circuit
## Resources
### Software
- [Verilator](https://www.veripool.org/wiki/verilator)
- [See signal waves nicely with gtkwave](http://gtkwave.sourceforge.net/)
- [FPGA design flow](https://zipcpu.com/blog/2020/04/01/design-flow.html)
    - quite involved, but `yosys` and `gtkwave` are quite handy.
### Papers and Tutorials
- [Quick Start Guide to Verilog](https://www.springer.com/gp/book/9783030105518)
- [Zipcpu verilog crash course](https://zipcpu.com/blog/2017/06/21/looking-at-verilator.html)
- [Verilog cheatsheet](https://marceluda.github.io/rp_dummy/EEOF2018/Verilog_Cheat_Sheet.pdf)
- [Another Verilog cheatsheet](https://www.cl.cam.ac.uk/~djg11/teaching/learners.pdf)
- [Verilog in one day](http://www.asic-world.com/verilog/)
