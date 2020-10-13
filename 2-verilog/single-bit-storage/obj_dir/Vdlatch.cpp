// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdlatch.h for the primary calling header

#include "Vdlatch.h"
#include "Vdlatch__Syms.h"

//==========

void Vdlatch::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vdlatch::eval\n"); );
    Vdlatch__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vdlatch* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        vlSymsp->__Vm_activity = true;
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("dlatch.v", 3, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vdlatch::_eval_initial_loop(Vdlatch__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    vlSymsp->__Vm_activity = true;
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("dlatch.v", 3, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vdlatch::_combo__TOP__2(Vdlatch__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdlatch::_combo__TOP__2\n"); );
    Vdlatch* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->dlatch__02Eclk) {
        vlTOPp->dlatch__02EQ = vlTOPp->dlatch__02ED;
    }
    if (vlTOPp->dlatch__02Eclk) {
        vlTOPp->dlatch__02EQn = (1U & (~ (IData)(vlTOPp->dlatch__02ED)));
    }
}

VL_INLINE_OPT void Vdlatch::_sequent__TOP__4(Vdlatch__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdlatch::_sequent__TOP__4\n"); );
    Vdlatch* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->dflipflop__02EQn = (1U & ((IData)(vlTOPp->reset) 
                                      | (~ (IData)(vlTOPp->dflipflop__02ED))));
    vlTOPp->dflipflop__02EQ = ((~ (IData)(vlTOPp->reset)) 
                               & (IData)(vlTOPp->dflipflop__02ED));
}

void Vdlatch::_eval(Vdlatch__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdlatch::_eval\n"); );
    Vdlatch* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__2(vlSymsp);
    if ((((IData)(vlTOPp->dflipflop__02Eclk) & (~ (IData)(vlTOPp->__Vclklast__TOP__dflipflop__02Eclk))) 
         | ((IData)(vlTOPp->reset) & (~ (IData)(vlTOPp->__Vclklast__TOP__reset))))) {
        vlTOPp->_sequent__TOP__4(vlSymsp);
    }
    // Final
    vlTOPp->__Vclklast__TOP__dflipflop__02Eclk = vlTOPp->dflipflop__02Eclk;
    vlTOPp->__Vclklast__TOP__reset = vlTOPp->reset;
}

VL_INLINE_OPT QData Vdlatch::_change_request(Vdlatch__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdlatch::_change_request\n"); );
    Vdlatch* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vdlatch::_change_request_1(Vdlatch__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdlatch::_change_request_1\n"); );
    Vdlatch* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vdlatch::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdlatch::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((dlatch__02Eclk & 0xfeU))) {
        Verilated::overWidthError("dlatch.clk");}
    if (VL_UNLIKELY((dlatch__02ED & 0xfeU))) {
        Verilated::overWidthError("dlatch.D");}
    if (VL_UNLIKELY((dflipflop__02ED & 0xfeU))) {
        Verilated::overWidthError("dflipflop.D");}
    if (VL_UNLIKELY((dflipflop__02Eclk & 0xfeU))) {
        Verilated::overWidthError("dflipflop.clk");}
    if (VL_UNLIKELY((reset & 0xfeU))) {
        Verilated::overWidthError("reset");}
}
#endif  // VL_DEBUG
