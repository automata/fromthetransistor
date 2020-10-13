// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdlatch.h for the primary calling header

#include "Vdlatch.h"
#include "Vdlatch__Syms.h"

//==========

VL_CTOR_IMP(Vdlatch) {
    Vdlatch__Syms* __restrict vlSymsp = __VlSymsp = new Vdlatch__Syms(this, name());
    Vdlatch* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vdlatch::__Vconfigure(Vdlatch__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-9);
    Verilated::timeprecision(-12);
}

Vdlatch::~Vdlatch() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vdlatch::_initial__TOP__1(Vdlatch__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdlatch::_initial__TOP__1\n"); );
    Vdlatch* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_WRITEF("dlatch\n");
    VL_WRITEF("dflipflop with async reset\n");
}

void Vdlatch::_eval_initial(Vdlatch__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdlatch::_eval_initial\n"); );
    Vdlatch* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__1(vlSymsp);
    vlTOPp->__Vclklast__TOP__dflipflop__02Eclk = vlTOPp->dflipflop__02Eclk;
    vlTOPp->__Vclklast__TOP__reset = vlTOPp->reset;
}

void Vdlatch::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdlatch::final\n"); );
    // Variables
    Vdlatch__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vdlatch* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vdlatch::_eval_settle(Vdlatch__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdlatch::_eval_settle\n"); );
    Vdlatch* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__2(vlSymsp);
}

void Vdlatch::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdlatch::_ctor_var_reset\n"); );
    // Body
    dlatch__02Eclk = VL_RAND_RESET_I(1);
    dlatch__02ED = VL_RAND_RESET_I(1);
    dlatch__02EQ = VL_RAND_RESET_I(1);
    dlatch__02EQn = VL_RAND_RESET_I(1);
    dflipflop__02EQ = VL_RAND_RESET_I(1);
    dflipflop__02EQn = VL_RAND_RESET_I(1);
    dflipflop__02ED = VL_RAND_RESET_I(1);
    dflipflop__02Eclk = VL_RAND_RESET_I(1);
    reset = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<1; ++__Vi0) {
            __Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }}
}
