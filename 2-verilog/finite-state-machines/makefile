verilate:
	verilator -Wall --trace --cc $(src).v --build --exe $(src).cpp

build:
	g++ -std=gnu++14 -Wall -Iobj_dir/ -I/usr/share/verilator/include /usr/share/verilator/include/verilated_vcd_c.cpp /usr/share/verilator/include/verilated.cpp obj_dir/V$(src)__ALL.cpp $(src).cpp  -o $(src)

all: verilate build
	./$(src)

clean:
	rm -rf obj_dir/
