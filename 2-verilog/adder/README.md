Combinatorial ripple carry adder made from a full-adder which is made from a half-adder.

##### Building and running
- full adder:
    - `make verilate ADDER=full_adder`
    - `make build ADDER=full_adder`
    - trace file: `full_adder_trace.vcd`

- ripple carry adder:
    - `make verilate ADDER=ripple`
    - `make build ADDER=ripple`
    - trace file: `ripple_trace.vcd`

run: `./main`
