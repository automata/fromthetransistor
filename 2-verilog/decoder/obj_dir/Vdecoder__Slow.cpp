// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdecoder.h for the primary calling header

#include "Vdecoder.h"
#include "Vdecoder__Syms.h"

//==========

VL_CTOR_IMP(Vdecoder) {
    Vdecoder__Syms* __restrict vlSymsp = __VlSymsp = new Vdecoder__Syms(this, name());
    Vdecoder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vdecoder::__Vconfigure(Vdecoder__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-12);
    Verilated::timeprecision(-12);
}

Vdecoder::~Vdecoder() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vdecoder::_eval_initial(Vdecoder__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdecoder::_eval_initial\n"); );
    Vdecoder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vdecoder::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdecoder::final\n"); );
    // Variables
    Vdecoder__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vdecoder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vdecoder::_eval_settle(Vdecoder__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdecoder::_eval_settle\n"); );
    Vdecoder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

void Vdecoder::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdecoder::_ctor_var_reset\n"); );
    // Body
    A = VL_RAND_RESET_I(1);
    B = VL_RAND_RESET_I(1);
    F3 = VL_RAND_RESET_I(1);
    F2 = VL_RAND_RESET_I(1);
    F1 = VL_RAND_RESET_I(1);
    F0 = VL_RAND_RESET_I(1);
}
