// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vripple.h for the primary calling header

#include "Vripple.h"
#include "Vripple__Syms.h"

//==========

void Vripple::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vripple::eval\n"); );
    Vripple__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vripple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
            VL_FATAL_MT("ripple.v", 3, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vripple::_eval_initial_loop(Vripple__Syms* __restrict vlSymsp) {
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
            VL_FATAL_MT("ripple.v", 3, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vripple::_combo__TOP__2(Vripple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vripple::_combo__TOP__2\n"); );
    Vripple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->ripple__DOT__genblk1__BRA__0__KET____DOT__fainst__DOT__HA1_Sum 
        = (1U & ((IData)(vlTOPp->A) ^ (IData)(vlTOPp->B)));
    vlTOPp->ripple__DOT__genblk1__BRA__1__KET____DOT__fainst__DOT__HA1_Sum 
        = (1U & (((IData)(vlTOPp->A) ^ (IData)(vlTOPp->B)) 
                 >> 1U));
    vlTOPp->ripple__DOT__genblk1__BRA__2__KET____DOT__fainst__DOT__HA1_Sum 
        = (1U & (((IData)(vlTOPp->A) ^ (IData)(vlTOPp->B)) 
                 >> 2U));
    vlTOPp->ripple__DOT__genblk1__BRA__3__KET____DOT__fainst__DOT__HA1_Sum 
        = (1U & (((IData)(vlTOPp->A) ^ (IData)(vlTOPp->B)) 
                 >> 3U));
    vlTOPp->ripple__DOT__genblk1__BRA__4__KET____DOT__fainst__DOT__HA1_Sum 
        = (1U & (((IData)(vlTOPp->A) ^ (IData)(vlTOPp->B)) 
                 >> 4U));
    vlTOPp->ripple__DOT__genblk1__BRA__5__KET____DOT__fainst__DOT__HA1_Sum 
        = (1U & (((IData)(vlTOPp->A) ^ (IData)(vlTOPp->B)) 
                 >> 5U));
    vlTOPp->ripple__DOT__genblk1__BRA__6__KET____DOT__fainst__DOT__HA1_Sum 
        = (1U & (((IData)(vlTOPp->A) ^ (IData)(vlTOPp->B)) 
                 >> 6U));
    vlTOPp->ripple__DOT__genblk1__BRA__7__KET____DOT__fainst__DOT__HA1_Sum 
        = (1U & (((IData)(vlTOPp->A) ^ (IData)(vlTOPp->B)) 
                 >> 7U));
    vlTOPp->ripple__DOT__genblk1__BRA__8__KET____DOT__fainst__DOT__HA1_Sum 
        = (1U & (((IData)(vlTOPp->A) ^ (IData)(vlTOPp->B)) 
                 >> 8U));
    vlTOPp->ripple__DOT__genblk1__BRA__9__KET____DOT__fainst__DOT__HA1_Sum 
        = (1U & (((IData)(vlTOPp->A) ^ (IData)(vlTOPp->B)) 
                 >> 9U));
    vlTOPp->ripple__DOT__genblk1__BRA__10__KET____DOT__fainst__DOT__HA1_Sum 
        = (1U & (((IData)(vlTOPp->A) ^ (IData)(vlTOPp->B)) 
                 >> 0xaU));
    vlTOPp->ripple__DOT__genblk1__BRA__11__KET____DOT__fainst__DOT__HA1_Sum 
        = (1U & (((IData)(vlTOPp->A) ^ (IData)(vlTOPp->B)) 
                 >> 0xbU));
    vlTOPp->ripple__DOT__genblk1__BRA__12__KET____DOT__fainst__DOT__HA1_Sum 
        = (1U & (((IData)(vlTOPp->A) ^ (IData)(vlTOPp->B)) 
                 >> 0xcU));
    vlTOPp->ripple__DOT__genblk1__BRA__13__KET____DOT__fainst__DOT__HA1_Sum 
        = (1U & (((IData)(vlTOPp->A) ^ (IData)(vlTOPp->B)) 
                 >> 0xdU));
    vlTOPp->ripple__DOT__genblk1__BRA__14__KET____DOT__fainst__DOT__HA1_Sum 
        = (1U & (((IData)(vlTOPp->A) ^ (IData)(vlTOPp->B)) 
                 >> 0xeU));
    vlTOPp->ripple__DOT__genblk1__BRA__15__KET____DOT__fainst__DOT__HA1_Sum 
        = (1U & (((IData)(vlTOPp->A) ^ (IData)(vlTOPp->B)) 
                 >> 0xfU));
    vlTOPp->ripple__DOT__genblk1__BRA__0__KET____DOT__fainst__DOT__HA2_Cout 
        = ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__0__KET____DOT__fainst__DOT__HA1_Sum) 
           & vlTOPp->ripple__DOT__m_carry);
    vlTOPp->ripple__DOT__m_sum = ((0xfffeU & (IData)(vlTOPp->ripple__DOT__m_sum)) 
                                  | (1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__0__KET____DOT__fainst__DOT__HA1_Sum) 
                                           ^ vlTOPp->ripple__DOT__m_carry)));
    vlTOPp->ripple__DOT__genblk1__BRA__1__KET____DOT__fainst__DOT__HA2_Cout 
        = ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__1__KET____DOT__fainst__DOT__HA1_Sum) 
           & (vlTOPp->ripple__DOT__m_carry >> 1U));
    vlTOPp->ripple__DOT__m_sum = ((0xfffdU & (IData)(vlTOPp->ripple__DOT__m_sum)) 
                                  | (2U & (((IData)(vlTOPp->ripple__DOT__genblk1__BRA__1__KET____DOT__fainst__DOT__HA1_Sum) 
                                            << 1U) 
                                           ^ (0xfffffffeU 
                                              & vlTOPp->ripple__DOT__m_carry))));
    vlTOPp->ripple__DOT__genblk1__BRA__2__KET____DOT__fainst__DOT__HA2_Cout 
        = ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__2__KET____DOT__fainst__DOT__HA1_Sum) 
           & (vlTOPp->ripple__DOT__m_carry >> 2U));
    vlTOPp->ripple__DOT__m_sum = ((0xfffbU & (IData)(vlTOPp->ripple__DOT__m_sum)) 
                                  | (4U & (((IData)(vlTOPp->ripple__DOT__genblk1__BRA__2__KET____DOT__fainst__DOT__HA1_Sum) 
                                            << 2U) 
                                           ^ (0xfffffffcU 
                                              & vlTOPp->ripple__DOT__m_carry))));
    vlTOPp->ripple__DOT__genblk1__BRA__3__KET____DOT__fainst__DOT__HA2_Cout 
        = ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__3__KET____DOT__fainst__DOT__HA1_Sum) 
           & (vlTOPp->ripple__DOT__m_carry >> 3U));
    vlTOPp->ripple__DOT__m_sum = ((0xfff7U & (IData)(vlTOPp->ripple__DOT__m_sum)) 
                                  | (8U & (((IData)(vlTOPp->ripple__DOT__genblk1__BRA__3__KET____DOT__fainst__DOT__HA1_Sum) 
                                            << 3U) 
                                           ^ (0xfffffff8U 
                                              & vlTOPp->ripple__DOT__m_carry))));
    vlTOPp->ripple__DOT__genblk1__BRA__4__KET____DOT__fainst__DOT__HA2_Cout 
        = ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__4__KET____DOT__fainst__DOT__HA1_Sum) 
           & (vlTOPp->ripple__DOT__m_carry >> 4U));
    vlTOPp->ripple__DOT__m_sum = ((0xffefU & (IData)(vlTOPp->ripple__DOT__m_sum)) 
                                  | (0x10U & (((IData)(vlTOPp->ripple__DOT__genblk1__BRA__4__KET____DOT__fainst__DOT__HA1_Sum) 
                                               << 4U) 
                                              ^ (0xfffffff0U 
                                                 & vlTOPp->ripple__DOT__m_carry))));
    vlTOPp->ripple__DOT__genblk1__BRA__5__KET____DOT__fainst__DOT__HA2_Cout 
        = ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__5__KET____DOT__fainst__DOT__HA1_Sum) 
           & (vlTOPp->ripple__DOT__m_carry >> 5U));
    vlTOPp->ripple__DOT__m_sum = ((0xffdfU & (IData)(vlTOPp->ripple__DOT__m_sum)) 
                                  | (0x20U & (((IData)(vlTOPp->ripple__DOT__genblk1__BRA__5__KET____DOT__fainst__DOT__HA1_Sum) 
                                               << 5U) 
                                              ^ (0xffffffe0U 
                                                 & vlTOPp->ripple__DOT__m_carry))));
    vlTOPp->ripple__DOT__genblk1__BRA__6__KET____DOT__fainst__DOT__HA2_Cout 
        = ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__6__KET____DOT__fainst__DOT__HA1_Sum) 
           & (vlTOPp->ripple__DOT__m_carry >> 6U));
    vlTOPp->ripple__DOT__m_sum = ((0xffbfU & (IData)(vlTOPp->ripple__DOT__m_sum)) 
                                  | (0x40U & (((IData)(vlTOPp->ripple__DOT__genblk1__BRA__6__KET____DOT__fainst__DOT__HA1_Sum) 
                                               << 6U) 
                                              ^ (0xffffffc0U 
                                                 & vlTOPp->ripple__DOT__m_carry))));
    vlTOPp->ripple__DOT__genblk1__BRA__7__KET____DOT__fainst__DOT__HA2_Cout 
        = ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__7__KET____DOT__fainst__DOT__HA1_Sum) 
           & (vlTOPp->ripple__DOT__m_carry >> 7U));
    vlTOPp->ripple__DOT__m_sum = ((0xff7fU & (IData)(vlTOPp->ripple__DOT__m_sum)) 
                                  | (0x80U & (((IData)(vlTOPp->ripple__DOT__genblk1__BRA__7__KET____DOT__fainst__DOT__HA1_Sum) 
                                               << 7U) 
                                              ^ (0xffffff80U 
                                                 & vlTOPp->ripple__DOT__m_carry))));
    vlTOPp->ripple__DOT__genblk1__BRA__8__KET____DOT__fainst__DOT__HA2_Cout 
        = ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__8__KET____DOT__fainst__DOT__HA1_Sum) 
           & (vlTOPp->ripple__DOT__m_carry >> 8U));
    vlTOPp->ripple__DOT__m_sum = ((0xfeffU & (IData)(vlTOPp->ripple__DOT__m_sum)) 
                                  | (0x100U & (((IData)(vlTOPp->ripple__DOT__genblk1__BRA__8__KET____DOT__fainst__DOT__HA1_Sum) 
                                                << 8U) 
                                               ^ (0xffffff00U 
                                                  & vlTOPp->ripple__DOT__m_carry))));
    vlTOPp->ripple__DOT__genblk1__BRA__9__KET____DOT__fainst__DOT__HA2_Cout 
        = ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__9__KET____DOT__fainst__DOT__HA1_Sum) 
           & (vlTOPp->ripple__DOT__m_carry >> 9U));
    vlTOPp->ripple__DOT__m_sum = ((0xfdffU & (IData)(vlTOPp->ripple__DOT__m_sum)) 
                                  | (0x200U & (((IData)(vlTOPp->ripple__DOT__genblk1__BRA__9__KET____DOT__fainst__DOT__HA1_Sum) 
                                                << 9U) 
                                               ^ (0xfffffe00U 
                                                  & vlTOPp->ripple__DOT__m_carry))));
    vlTOPp->ripple__DOT__genblk1__BRA__10__KET____DOT__fainst__DOT__HA2_Cout 
        = ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__10__KET____DOT__fainst__DOT__HA1_Sum) 
           & (vlTOPp->ripple__DOT__m_carry >> 0xaU));
    vlTOPp->ripple__DOT__m_sum = ((0xfbffU & (IData)(vlTOPp->ripple__DOT__m_sum)) 
                                  | (0x400U & (((IData)(vlTOPp->ripple__DOT__genblk1__BRA__10__KET____DOT__fainst__DOT__HA1_Sum) 
                                                << 0xaU) 
                                               ^ (0xfffffc00U 
                                                  & vlTOPp->ripple__DOT__m_carry))));
    vlTOPp->ripple__DOT__genblk1__BRA__11__KET____DOT__fainst__DOT__HA2_Cout 
        = ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__11__KET____DOT__fainst__DOT__HA1_Sum) 
           & (vlTOPp->ripple__DOT__m_carry >> 0xbU));
    vlTOPp->ripple__DOT__m_sum = ((0xf7ffU & (IData)(vlTOPp->ripple__DOT__m_sum)) 
                                  | (0x800U & (((IData)(vlTOPp->ripple__DOT__genblk1__BRA__11__KET____DOT__fainst__DOT__HA1_Sum) 
                                                << 0xbU) 
                                               ^ (0xfffff800U 
                                                  & vlTOPp->ripple__DOT__m_carry))));
    vlTOPp->ripple__DOT__genblk1__BRA__12__KET____DOT__fainst__DOT__HA2_Cout 
        = ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__12__KET____DOT__fainst__DOT__HA1_Sum) 
           & (vlTOPp->ripple__DOT__m_carry >> 0xcU));
    vlTOPp->ripple__DOT__m_sum = ((0xefffU & (IData)(vlTOPp->ripple__DOT__m_sum)) 
                                  | (0x1000U & (((IData)(vlTOPp->ripple__DOT__genblk1__BRA__12__KET____DOT__fainst__DOT__HA1_Sum) 
                                                 << 0xcU) 
                                                ^ (0xfffff000U 
                                                   & vlTOPp->ripple__DOT__m_carry))));
    vlTOPp->ripple__DOT__genblk1__BRA__13__KET____DOT__fainst__DOT__HA2_Cout 
        = ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__13__KET____DOT__fainst__DOT__HA1_Sum) 
           & (vlTOPp->ripple__DOT__m_carry >> 0xdU));
    vlTOPp->ripple__DOT__m_sum = ((0xdfffU & (IData)(vlTOPp->ripple__DOT__m_sum)) 
                                  | (0x2000U & (((IData)(vlTOPp->ripple__DOT__genblk1__BRA__13__KET____DOT__fainst__DOT__HA1_Sum) 
                                                 << 0xdU) 
                                                ^ (0xffffe000U 
                                                   & vlTOPp->ripple__DOT__m_carry))));
    vlTOPp->ripple__DOT__genblk1__BRA__14__KET____DOT__fainst__DOT__HA2_Cout 
        = ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__14__KET____DOT__fainst__DOT__HA1_Sum) 
           & (vlTOPp->ripple__DOT__m_carry >> 0xeU));
    vlTOPp->ripple__DOT__m_sum = ((0xbfffU & (IData)(vlTOPp->ripple__DOT__m_sum)) 
                                  | (0x4000U & (((IData)(vlTOPp->ripple__DOT__genblk1__BRA__14__KET____DOT__fainst__DOT__HA1_Sum) 
                                                 << 0xeU) 
                                                ^ (0xffffc000U 
                                                   & vlTOPp->ripple__DOT__m_carry))));
    vlTOPp->ripple__DOT__genblk1__BRA__15__KET____DOT__fainst__DOT__HA2_Cout 
        = ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__15__KET____DOT__fainst__DOT__HA1_Sum) 
           & (vlTOPp->ripple__DOT__m_carry >> 0xfU));
    vlTOPp->ripple__DOT__m_sum = ((0x7fffU & (IData)(vlTOPp->ripple__DOT__m_sum)) 
                                  | (0x8000U & (((IData)(vlTOPp->ripple__DOT__genblk1__BRA__15__KET____DOT__fainst__DOT__HA1_Sum) 
                                                 << 0xfU) 
                                                ^ (0xffff8000U 
                                                   & vlTOPp->ripple__DOT__m_carry))));
    vlTOPp->ripple__DOT__m_carry = ((0x1fffdU & vlTOPp->ripple__DOT__m_carry) 
                                    | (2U & ((((IData)(vlTOPp->A) 
                                               & (IData)(vlTOPp->B)) 
                                              | (IData)(vlTOPp->ripple__DOT__genblk1__BRA__0__KET____DOT__fainst__DOT__HA2_Cout)) 
                                             << 1U)));
    vlTOPp->ripple__DOT__m_carry = ((0x1fffbU & vlTOPp->ripple__DOT__m_carry) 
                                    | (4U & ((0xfffffffcU 
                                              & (((IData)(vlTOPp->A) 
                                                  & (IData)(vlTOPp->B)) 
                                                 << 1U)) 
                                             | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__1__KET____DOT__fainst__DOT__HA2_Cout) 
                                                << 2U))));
    vlTOPp->ripple__DOT__m_carry = ((0x1fff7U & vlTOPp->ripple__DOT__m_carry) 
                                    | (8U & ((0xfffffff8U 
                                              & (((IData)(vlTOPp->A) 
                                                  & (IData)(vlTOPp->B)) 
                                                 << 1U)) 
                                             | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__2__KET____DOT__fainst__DOT__HA2_Cout) 
                                                << 3U))));
    vlTOPp->ripple__DOT__m_carry = ((0x1ffefU & vlTOPp->ripple__DOT__m_carry) 
                                    | (0x10U & ((0xfffffff0U 
                                                 & (((IData)(vlTOPp->A) 
                                                     & (IData)(vlTOPp->B)) 
                                                    << 1U)) 
                                                | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__3__KET____DOT__fainst__DOT__HA2_Cout) 
                                                   << 4U))));
    vlTOPp->ripple__DOT__m_carry = ((0x1ffdfU & vlTOPp->ripple__DOT__m_carry) 
                                    | (0x20U & ((0xffffffe0U 
                                                 & (((IData)(vlTOPp->A) 
                                                     & (IData)(vlTOPp->B)) 
                                                    << 1U)) 
                                                | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__4__KET____DOT__fainst__DOT__HA2_Cout) 
                                                   << 5U))));
    vlTOPp->ripple__DOT__m_carry = ((0x1ffbfU & vlTOPp->ripple__DOT__m_carry) 
                                    | (0x40U & ((0xffffffc0U 
                                                 & (((IData)(vlTOPp->A) 
                                                     & (IData)(vlTOPp->B)) 
                                                    << 1U)) 
                                                | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__5__KET____DOT__fainst__DOT__HA2_Cout) 
                                                   << 6U))));
    vlTOPp->ripple__DOT__m_carry = ((0x1ff7fU & vlTOPp->ripple__DOT__m_carry) 
                                    | (0x80U & ((0xffffff80U 
                                                 & (((IData)(vlTOPp->A) 
                                                     & (IData)(vlTOPp->B)) 
                                                    << 1U)) 
                                                | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__6__KET____DOT__fainst__DOT__HA2_Cout) 
                                                   << 7U))));
    vlTOPp->ripple__DOT__m_carry = ((0x1feffU & vlTOPp->ripple__DOT__m_carry) 
                                    | (0x100U & ((0xffffff00U 
                                                  & (((IData)(vlTOPp->A) 
                                                      & (IData)(vlTOPp->B)) 
                                                     << 1U)) 
                                                 | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__7__KET____DOT__fainst__DOT__HA2_Cout) 
                                                    << 8U))));
    vlTOPp->ripple__DOT__m_carry = ((0x1fdffU & vlTOPp->ripple__DOT__m_carry) 
                                    | (0x200U & ((0xfffffe00U 
                                                  & (((IData)(vlTOPp->A) 
                                                      & (IData)(vlTOPp->B)) 
                                                     << 1U)) 
                                                 | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__8__KET____DOT__fainst__DOT__HA2_Cout) 
                                                    << 9U))));
    vlTOPp->ripple__DOT__m_carry = ((0x1fbffU & vlTOPp->ripple__DOT__m_carry) 
                                    | (0x400U & ((0xfffffc00U 
                                                  & (((IData)(vlTOPp->A) 
                                                      & (IData)(vlTOPp->B)) 
                                                     << 1U)) 
                                                 | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__9__KET____DOT__fainst__DOT__HA2_Cout) 
                                                    << 0xaU))));
    vlTOPp->ripple__DOT__m_carry = ((0x1f7ffU & vlTOPp->ripple__DOT__m_carry) 
                                    | (0x800U & ((0xfffff800U 
                                                  & (((IData)(vlTOPp->A) 
                                                      & (IData)(vlTOPp->B)) 
                                                     << 1U)) 
                                                 | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__10__KET____DOT__fainst__DOT__HA2_Cout) 
                                                    << 0xbU))));
    vlTOPp->ripple__DOT__m_carry = ((0x1efffU & vlTOPp->ripple__DOT__m_carry) 
                                    | (0x1000U & ((0xfffff000U 
                                                   & (((IData)(vlTOPp->A) 
                                                       & (IData)(vlTOPp->B)) 
                                                      << 1U)) 
                                                  | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__11__KET____DOT__fainst__DOT__HA2_Cout) 
                                                     << 0xcU))));
    vlTOPp->ripple__DOT__m_carry = ((0x1dfffU & vlTOPp->ripple__DOT__m_carry) 
                                    | (0x2000U & ((0xffffe000U 
                                                   & (((IData)(vlTOPp->A) 
                                                       & (IData)(vlTOPp->B)) 
                                                      << 1U)) 
                                                  | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__12__KET____DOT__fainst__DOT__HA2_Cout) 
                                                     << 0xdU))));
    vlTOPp->ripple__DOT__m_carry = ((0x1bfffU & vlTOPp->ripple__DOT__m_carry) 
                                    | (0x4000U & ((0xffffc000U 
                                                   & (((IData)(vlTOPp->A) 
                                                       & (IData)(vlTOPp->B)) 
                                                      << 1U)) 
                                                  | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__13__KET____DOT__fainst__DOT__HA2_Cout) 
                                                     << 0xeU))));
    vlTOPp->ripple__DOT__m_carry = ((0x17fffU & vlTOPp->ripple__DOT__m_carry) 
                                    | (0x8000U & ((0xffff8000U 
                                                   & (((IData)(vlTOPp->A) 
                                                       & (IData)(vlTOPp->B)) 
                                                      << 1U)) 
                                                  | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__14__KET____DOT__fainst__DOT__HA2_Cout) 
                                                     << 0xfU))));
    vlTOPp->ripple__DOT__m_carry = ((0xffffU & vlTOPp->ripple__DOT__m_carry) 
                                    | (0x10000U & (
                                                   (0xffff0000U 
                                                    & (((IData)(vlTOPp->A) 
                                                        & (IData)(vlTOPp->B)) 
                                                       << 1U)) 
                                                   | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__15__KET____DOT__fainst__DOT__HA2_Cout) 
                                                      << 0x10U))));
    vlTOPp->Sum = ((0x10000U & vlTOPp->ripple__DOT__m_carry) 
                   | (IData)(vlTOPp->ripple__DOT__m_sum));
}

void Vripple::_eval(Vripple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vripple::_eval\n"); );
    Vripple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__2(vlSymsp);
    vlTOPp->__Vm_traceActivity[1U] = 1U;
}

VL_INLINE_OPT QData Vripple::_change_request(Vripple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vripple::_change_request\n"); );
    Vripple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vripple::_change_request_1(Vripple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vripple::_change_request_1\n"); );
    Vripple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    __req |= ((vlTOPp->ripple__DOT__m_carry ^ vlTOPp->__Vchglast__TOP__ripple__DOT__m_carry));
    VL_DEBUG_IF( if(__req && ((vlTOPp->ripple__DOT__m_carry ^ vlTOPp->__Vchglast__TOP__ripple__DOT__m_carry))) VL_DBG_MSGF("        CHANGE: ripple.v:8: ripple.m_carry\n"); );
    // Final
    vlTOPp->__Vchglast__TOP__ripple__DOT__m_carry = vlTOPp->ripple__DOT__m_carry;
    return __req;
}

#ifdef VL_DEBUG
void Vripple::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vripple::_eval_debug_assertions\n"); );
}
#endif  // VL_DEBUG
