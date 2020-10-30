# ALU test
alu_test: alu_test_verilate alu_test_build
	./alu_test

alu_test_verilate:
	verilator -Wall --cc alu.v --build --exe alu_test.cpp

alu_test_build:
	g++ -std=c++17 -Wall -Iobj_dir/ -I/usr/share/verilator/include /usr/share/verilator/include/verilated.cpp obj_dir/Valu__ALL.cpp alu_test.cpp  -o alu_test
