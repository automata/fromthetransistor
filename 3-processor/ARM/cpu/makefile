# memory_controller
memory_controller_verilate:
	verilator --default-language 1800-2017 --assert -Wall --trace -cc memory_controller.v --build --exe memory_controller.cpp

memory_controller_build:
	g++ -std=gnu++14 -Wall -Iobj_dir -I/usr/share/verilator/include /usr/share/verilator/include/verilated_vcd_c.cpp /usr/share/verilator/include/verilated.cpp obj_dir/Vmemory_controller__ALL.cpp memory_controller.cpp -o memory_controller

memory_controller: memory_controller_verilate memory_controller_build
	./memory_controller

# registers
registers_verilate:
	verilator -Wall --trace -cc register_bank.v --build --exe registers.cpp

registers_build:
	g++ -std=gnu++14 -Wall -Iobj_dir -I/usr/share/verilator/include /usr/share/verilator/include/verilated_vcd_c.cpp /usr/share/verilator/include/verilated.cpp obj_dir/Vregister_bank__ALL.cpp registers.cpp -o registers

registers: registers_verilate registers_build
	./registers

# alu
alu_verilate:
	verilator -Wall --trace -cc alu.v --build --exe alu.cpp

alu_build:
	g++ -std=gnu++14 -Wall -Iobj_dir -I/usr/share/verilator/include /usr/share/verilator/include/verilated_vcd_c.cpp /usr/share/verilator/include/verilated.cpp obj_dir/Valu__ALL.cpp alu.cpp -o alu

alu: alu_verilate alu_build
	./alu

# barrel shifter
barrel_verilate:
	verilator -Wall --trace -cc barrel_shifter.v --build --exe barrel_shifter.cpp
	
barrel_build:
	g++ -std=gnu++14 -Wall -Iobj_dir -I/usr/share/verilator/include /usr/share/verilator/include/verilated_vcd_c.cpp /usr/share/verilator/include/verilated.cpp obj_dir/Vbarrel_shifter__ALL.cpp barrel_shifter.cpp -o barrel

barrel: barrel_verilate barrel_build
	./barrel

# multiplier
multiplier_verilate:
	verilator -Wall --trace -cc multiplier.v --build --exe multiplier.cpp
	
multiplier_build:
	g++ -std=gnu++14 -Wall -Iobj_dir -I/usr/share/verilator/include /usr/share/verilator/include/verilated_vcd_c.cpp /usr/share/verilator/include/verilated.cpp obj_dir/Vmultiplier__ALL.cpp multiplier.cpp -o multiplier

multiplier: multiplier_verilate multiplier_build
	./multiplier
