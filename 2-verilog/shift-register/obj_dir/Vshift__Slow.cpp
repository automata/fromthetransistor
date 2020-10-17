// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vshift.h for the primary calling header

#include "Vshift.h"
#include "Vshift__Syms.h"

//==========

VL_CTOR_IMP(Vshift) {
    Vshift__Syms* __restrict vlSymsp = __VlSymsp = new Vshift__Syms(this, name());
    Vshift* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vshift::__Vconfigure(Vshift__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-12);
    Verilated::timeprecision(-12);
}

Vshift::~Vshift() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vshift::_eval_initial(Vshift__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vshift::_eval_initial\n"); );
    Vshift* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__reset = vlTOPp->reset;
}

void Vshift::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vshift::final\n"); );
    // Variables
    Vshift__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vshift* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vshift::_eval_settle(Vshift__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vshift::_eval_settle\n"); );
    Vshift* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vshift::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vshift::_ctor_var_reset\n"); );
    // Body
    Dout0 = VL_RAND_RESET_I(4);
    Dout1 = VL_RAND_RESET_I(4);
    Dout2 = VL_RAND_RESET_I(4);
    Dout3 = VL_RAND_RESET_I(4);
    enable = VL_RAND_RESET_I(1);
    reset = VL_RAND_RESET_I(1);
    clk = VL_RAND_RESET_I(1);
    Din = VL_RAND_RESET_I(4);
    { int __Vi0=0; for (; __Vi0<1; ++__Vi0) {
            __Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }}
}
