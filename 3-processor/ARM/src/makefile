memory_verilate:
	verilator -Wall -cc memory.v --build --exe memory.cpp

memory_build:
	g++ -std=gnu++14 -Wall -Iobj_dir -I/usr/share/verilator/include /usr/share/verilator/include/verilated.cpp obj_dir/Vmemory__ALL.cpp memory.cpp -o memory

memory: memory_verilate memory_build
	./memory
