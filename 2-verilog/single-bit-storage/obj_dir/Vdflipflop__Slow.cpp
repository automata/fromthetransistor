// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdflipflop.h for the primary calling header

#include "Vdflipflop.h"
#include "Vdflipflop__Syms.h"

//==========

VL_CTOR_IMP(Vdflipflop) {
    Vdflipflop__Syms* __restrict vlSymsp = __VlSymsp = new Vdflipflop__Syms(this, name());
    Vdflipflop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vdflipflop::__Vconfigure(Vdflipflop__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-9);
    Verilated::timeprecision(-12);
}

Vdflipflop::~Vdflipflop() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vdflipflop::_initial__TOP__1(Vdflipflop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdflipflop::_initial__TOP__1\n"); );
    Vdflipflop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_WRITEF("dflipflop with async reset\n");
}

void Vdflipflop::_eval_initial(Vdflipflop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdflipflop::_eval_initial\n"); );
    Vdflipflop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__1(vlSymsp);
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__reset = vlTOPp->reset;
}

void Vdflipflop::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdflipflop::final\n"); );
    // Variables
    Vdflipflop__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vdflipflop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vdflipflop::_eval_settle(Vdflipflop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdflipflop::_eval_settle\n"); );
    Vdflipflop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vdflipflop::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdflipflop::_ctor_var_reset\n"); );
    // Body
    Q = VL_RAND_RESET_I(1);
    Qn = VL_RAND_RESET_I(1);
    D = VL_RAND_RESET_I(1);
    clk = VL_RAND_RESET_I(1);
    reset = VL_RAND_RESET_I(1);
    preset = VL_RAND_RESET_I(1);
    enable = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<1; ++__Vi0) {
            __Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }}
}
