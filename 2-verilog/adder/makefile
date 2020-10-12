verilate:
	verilator -Wall --trace --cc $(ADDER).v --build --exe $(ADDER)_main.cpp
build:
	g++ -Iobj_dir/ -I/usr/share/verilator/include/ /usr/share/verilator/include/verilated.cpp /usr/share/verilator/include/verilated_vcd_c.cpp obj_dir/V$(ADDER)__ALL.cpp $(ADDER)_main.cpp -o main
