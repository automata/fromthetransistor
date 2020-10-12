all:
	g++ -Iobj_dir/ -I/usr/share/verilator/include /usr/share/verilator/include/verilated.cpp obj_dir/Vhello__ALL.cpp main.cpp  -o main
verilate:
	verilator -Wall --cc hello.v --build --exe main.cpp
