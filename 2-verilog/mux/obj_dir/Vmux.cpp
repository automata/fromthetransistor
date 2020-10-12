// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmux.h for the primary calling header

#include "Vmux.h"
#include "Vmux__Syms.h"

//==========

void Vmux::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vmux::eval\n"); );
    Vmux__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vmux* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
            VL_FATAL_MT("mux.v", 2, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vmux::_eval_initial_loop(Vmux__Syms* __restrict vlSymsp) {
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
            VL_FATAL_MT("mux.v", 2, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vmux::_combo__TOP__1(Vmux__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux::_combo__TOP__1\n"); );
    Vmux* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->out = (1U & ((0U == (IData)(vlTOPp->sel))
                          ? (IData)(vlTOPp->in) : (
                                                   (1U 
                                                    == (IData)(vlTOPp->sel))
                                                    ? 
                                                   ((IData)(vlTOPp->in) 
                                                    >> 1U)
                                                    : 
                                                   ((2U 
                                                     == (IData)(vlTOPp->sel))
                                                     ? 
                                                    ((IData)(vlTOPp->in) 
                                                     >> 2U)
                                                     : 
                                                    ((3U 
                                                      == (IData)(vlTOPp->sel)) 
                                                     & ((IData)(vlTOPp->in) 
                                                        >> 3U))))));
}

void Vmux::_eval(Vmux__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux::_eval\n"); );
    Vmux* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

VL_INLINE_OPT QData Vmux::_change_request(Vmux__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux::_change_request\n"); );
    Vmux* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vmux::_change_request_1(Vmux__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux::_change_request_1\n"); );
    Vmux* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vmux::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((in & 0xf0U))) {
        Verilated::overWidthError("in");}
    if (VL_UNLIKELY((sel & 0xfcU))) {
        Verilated::overWidthError("sel");}
}
#endif  // VL_DEBUG
