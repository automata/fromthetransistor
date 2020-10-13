verilate:
	verilator -Wall --trace --cc dflipflop.v --build --exe main.cpp
build:
	g++ -Iobj_dir/ -I/usr/share/verilator/include /usr/share/verilator/include/verilated_vcd_c.cpp /usr/share/verilator/include/verilated.cpp obj_dir/Vdlatch__ALL.cpp obj_dir/Vdflipflop__ALL.cpp main.cpp  -o main
