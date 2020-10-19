verilate:
	verilator -Wall --trace --cc serial.v --build --exe main.cpp
build:
	g++ -Iobj_dir/ -I/usr/share/verilator/include /usr/share/verilator/include/verilated_vcd_c.cpp /usr/share/verilator/include/verilated.cpp obj_dir/Vserial__ALL.cpp main.cpp  -o main
