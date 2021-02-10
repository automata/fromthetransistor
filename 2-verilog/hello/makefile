# compiles and runs
all:
	verilator -Wall --cc hello.v --exe main.cpp
	cd obj_dir ; make -f Vhello.mk ; ./Vhello
