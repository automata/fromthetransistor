# computer test
computer_test: computer_test_verilate computer_test_build
	./computer_test

computer_test_verilate:
	verilator -Wall --trace --cc computer.v --build --exe computer_test.cpp

computer_test_build:
	g++ -std=gnu++14 -Wall -Iobj_dir/ -I/usr/share/verilator/include /usr/share/verilator/include/verilated_vcd_c.cpp /usr/share/verilator/include/verilated.cpp obj_dir/Vcomputer__ALL.cpp computer_test.cpp  -o computer_test

# ALU test
alu_test: alu_test_verilate alu_test_build
	./alu_test

alu_test_verilate:
	verilator -Wall --cc alu.v --build --exe alu_test.cpp

alu_test_build:
	g++ -std=gnu++14 -Wall -Iobj_dir/ -I/usr/share/verilator/include /usr/share/verilator/include/verilated.cpp obj_dir/Valu__ALL.cpp alu_test.cpp  -o alu_test
