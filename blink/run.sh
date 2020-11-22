verilator -Wall --cc blinking.v --exe  sim_main.cpp
cd obj_dir && make -f Vblinking.mk && ./Vblinking