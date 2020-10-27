verilate:
	verilator -Wall --trace --cc $(source).v --build --exe $(source)_main.cpp
build:
	g++ -Iobj_dir/ -I/usr/share/verilator/include /usr/share/verilator/include/verilated_vcd_c.cpp /usr/share/verilator/include/verilated.cpp obj_dir/V$(source)__ALL.cpp $(source)_main.cpp  -o $(source)_main
