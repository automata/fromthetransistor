// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfull_adder.h for the primary calling header

#include "Vfull_adder.h"
#include "Vfull_adder__Syms.h"

//==========

VL_CTOR_IMP(Vfull_adder) {
    Vfull_adder__Syms* __restrict vlSymsp = __VlSymsp = new Vfull_adder__Syms(this, name());
    Vfull_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vfull_adder::__Vconfigure(Vfull_adder__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-9);
    Verilated::timeprecision(-12);
}

Vfull_adder::~Vfull_adder() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vfull_adder::_eval_initial(Vfull_adder__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfull_adder::_eval_initial\n"); );
    Vfull_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vfull_adder::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfull_adder::final\n"); );
    // Variables
    Vfull_adder__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vfull_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vfull_adder::_eval_settle(Vfull_adder__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfull_adder::_eval_settle\n"); );
    Vfull_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

void Vfull_adder::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfull_adder::_ctor_var_reset\n"); );
    // Body
    Sum = VL_RAND_RESET_I(1);
    Cout = VL_RAND_RESET_I(1);
    A = VL_RAND_RESET_I(1);
    B = VL_RAND_RESET_I(1);
    Cin = VL_RAND_RESET_I(1);
    full_adder__DOT__HA1_Sum = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<1; ++__Vi0) {
            __Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }}
}
