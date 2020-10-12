// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vripple__Syms.h"


void Vripple::traceChgTop0(void* userp, VerilatedVcd* tracep) {
    Vripple__Syms* __restrict vlSymsp = static_cast<Vripple__Syms*>(userp);
    Vripple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        vlTOPp->traceChgSub0(userp, tracep);
    }
}

void Vripple::traceChgSub0(void* userp, VerilatedVcd* tracep) {
    Vripple__Syms* __restrict vlSymsp = static_cast<Vripple__Syms*>(userp);
    Vripple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        if (VL_UNLIKELY(vlTOPp->__Vm_traceActivity[1U])) {
            tracep->chgIData(oldp+0,(vlTOPp->ripple__DOT__m_carry),17);
            tracep->chgSData(oldp+1,(vlTOPp->ripple__DOT__m_sum),16);
            tracep->chgBit(oldp+2,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__0__KET____DOT__fainst__DOT__HA1_Sum) 
                                          ^ vlTOPp->ripple__DOT__m_carry))));
            tracep->chgBit(oldp+3,((1U & vlTOPp->ripple__DOT__m_carry)));
            tracep->chgBit(oldp+4,(vlTOPp->ripple__DOT__genblk1__BRA__0__KET____DOT__fainst__DOT__HA1_Sum));
            tracep->chgBit(oldp+5,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__0__KET____DOT__fainst__DOT__HA1_Sum) 
                                    & vlTOPp->ripple__DOT__m_carry)));
            tracep->chgBit(oldp+6,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__1__KET____DOT__fainst__DOT__HA1_Sum) 
                                          ^ (vlTOPp->ripple__DOT__m_carry 
                                             >> 1U)))));
            tracep->chgBit(oldp+7,((1U & (vlTOPp->ripple__DOT__m_carry 
                                          >> 1U))));
            tracep->chgBit(oldp+8,(vlTOPp->ripple__DOT__genblk1__BRA__1__KET____DOT__fainst__DOT__HA1_Sum));
            tracep->chgBit(oldp+9,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__1__KET____DOT__fainst__DOT__HA1_Sum) 
                                    & (vlTOPp->ripple__DOT__m_carry 
                                       >> 1U))));
            tracep->chgBit(oldp+10,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__2__KET____DOT__fainst__DOT__HA1_Sum) 
                                           ^ (vlTOPp->ripple__DOT__m_carry 
                                              >> 2U)))));
            tracep->chgBit(oldp+11,((1U & (vlTOPp->ripple__DOT__m_carry 
                                           >> 2U))));
            tracep->chgBit(oldp+12,(vlTOPp->ripple__DOT__genblk1__BRA__2__KET____DOT__fainst__DOT__HA1_Sum));
            tracep->chgBit(oldp+13,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__2__KET____DOT__fainst__DOT__HA1_Sum) 
                                     & (vlTOPp->ripple__DOT__m_carry 
                                        >> 2U))));
            tracep->chgBit(oldp+14,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__3__KET____DOT__fainst__DOT__HA1_Sum) 
                                           ^ (vlTOPp->ripple__DOT__m_carry 
                                              >> 3U)))));
            tracep->chgBit(oldp+15,((1U & (vlTOPp->ripple__DOT__m_carry 
                                           >> 3U))));
            tracep->chgBit(oldp+16,(vlTOPp->ripple__DOT__genblk1__BRA__3__KET____DOT__fainst__DOT__HA1_Sum));
            tracep->chgBit(oldp+17,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__3__KET____DOT__fainst__DOT__HA1_Sum) 
                                     & (vlTOPp->ripple__DOT__m_carry 
                                        >> 3U))));
            tracep->chgBit(oldp+18,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__4__KET____DOT__fainst__DOT__HA1_Sum) 
                                           ^ (vlTOPp->ripple__DOT__m_carry 
                                              >> 4U)))));
            tracep->chgBit(oldp+19,((1U & (vlTOPp->ripple__DOT__m_carry 
                                           >> 4U))));
            tracep->chgBit(oldp+20,(vlTOPp->ripple__DOT__genblk1__BRA__4__KET____DOT__fainst__DOT__HA1_Sum));
            tracep->chgBit(oldp+21,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__4__KET____DOT__fainst__DOT__HA1_Sum) 
                                     & (vlTOPp->ripple__DOT__m_carry 
                                        >> 4U))));
            tracep->chgBit(oldp+22,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__5__KET____DOT__fainst__DOT__HA1_Sum) 
                                           ^ (vlTOPp->ripple__DOT__m_carry 
                                              >> 5U)))));
            tracep->chgBit(oldp+23,((1U & (vlTOPp->ripple__DOT__m_carry 
                                           >> 5U))));
            tracep->chgBit(oldp+24,(vlTOPp->ripple__DOT__genblk1__BRA__5__KET____DOT__fainst__DOT__HA1_Sum));
            tracep->chgBit(oldp+25,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__5__KET____DOT__fainst__DOT__HA1_Sum) 
                                     & (vlTOPp->ripple__DOT__m_carry 
                                        >> 5U))));
            tracep->chgBit(oldp+26,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__6__KET____DOT__fainst__DOT__HA1_Sum) 
                                           ^ (vlTOPp->ripple__DOT__m_carry 
                                              >> 6U)))));
            tracep->chgBit(oldp+27,((1U & (vlTOPp->ripple__DOT__m_carry 
                                           >> 6U))));
            tracep->chgBit(oldp+28,(vlTOPp->ripple__DOT__genblk1__BRA__6__KET____DOT__fainst__DOT__HA1_Sum));
            tracep->chgBit(oldp+29,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__6__KET____DOT__fainst__DOT__HA1_Sum) 
                                     & (vlTOPp->ripple__DOT__m_carry 
                                        >> 6U))));
            tracep->chgBit(oldp+30,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__7__KET____DOT__fainst__DOT__HA1_Sum) 
                                           ^ (vlTOPp->ripple__DOT__m_carry 
                                              >> 7U)))));
            tracep->chgBit(oldp+31,((1U & (vlTOPp->ripple__DOT__m_carry 
                                           >> 7U))));
            tracep->chgBit(oldp+32,(vlTOPp->ripple__DOT__genblk1__BRA__7__KET____DOT__fainst__DOT__HA1_Sum));
            tracep->chgBit(oldp+33,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__7__KET____DOT__fainst__DOT__HA1_Sum) 
                                     & (vlTOPp->ripple__DOT__m_carry 
                                        >> 7U))));
            tracep->chgBit(oldp+34,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__8__KET____DOT__fainst__DOT__HA1_Sum) 
                                           ^ (vlTOPp->ripple__DOT__m_carry 
                                              >> 8U)))));
            tracep->chgBit(oldp+35,((1U & (vlTOPp->ripple__DOT__m_carry 
                                           >> 8U))));
            tracep->chgBit(oldp+36,(vlTOPp->ripple__DOT__genblk1__BRA__8__KET____DOT__fainst__DOT__HA1_Sum));
            tracep->chgBit(oldp+37,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__8__KET____DOT__fainst__DOT__HA1_Sum) 
                                     & (vlTOPp->ripple__DOT__m_carry 
                                        >> 8U))));
            tracep->chgBit(oldp+38,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__9__KET____DOT__fainst__DOT__HA1_Sum) 
                                           ^ (vlTOPp->ripple__DOT__m_carry 
                                              >> 9U)))));
            tracep->chgBit(oldp+39,((1U & (vlTOPp->ripple__DOT__m_carry 
                                           >> 9U))));
            tracep->chgBit(oldp+40,(vlTOPp->ripple__DOT__genblk1__BRA__9__KET____DOT__fainst__DOT__HA1_Sum));
            tracep->chgBit(oldp+41,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__9__KET____DOT__fainst__DOT__HA1_Sum) 
                                     & (vlTOPp->ripple__DOT__m_carry 
                                        >> 9U))));
            tracep->chgBit(oldp+42,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__10__KET____DOT__fainst__DOT__HA1_Sum) 
                                           ^ (vlTOPp->ripple__DOT__m_carry 
                                              >> 0xaU)))));
            tracep->chgBit(oldp+43,((1U & (vlTOPp->ripple__DOT__m_carry 
                                           >> 0xaU))));
            tracep->chgBit(oldp+44,(vlTOPp->ripple__DOT__genblk1__BRA__10__KET____DOT__fainst__DOT__HA1_Sum));
            tracep->chgBit(oldp+45,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__10__KET____DOT__fainst__DOT__HA1_Sum) 
                                     & (vlTOPp->ripple__DOT__m_carry 
                                        >> 0xaU))));
            tracep->chgBit(oldp+46,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__11__KET____DOT__fainst__DOT__HA1_Sum) 
                                           ^ (vlTOPp->ripple__DOT__m_carry 
                                              >> 0xbU)))));
            tracep->chgBit(oldp+47,((1U & (vlTOPp->ripple__DOT__m_carry 
                                           >> 0xbU))));
            tracep->chgBit(oldp+48,(vlTOPp->ripple__DOT__genblk1__BRA__11__KET____DOT__fainst__DOT__HA1_Sum));
            tracep->chgBit(oldp+49,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__11__KET____DOT__fainst__DOT__HA1_Sum) 
                                     & (vlTOPp->ripple__DOT__m_carry 
                                        >> 0xbU))));
            tracep->chgBit(oldp+50,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__12__KET____DOT__fainst__DOT__HA1_Sum) 
                                           ^ (vlTOPp->ripple__DOT__m_carry 
                                              >> 0xcU)))));
            tracep->chgBit(oldp+51,((1U & (vlTOPp->ripple__DOT__m_carry 
                                           >> 0xcU))));
            tracep->chgBit(oldp+52,(vlTOPp->ripple__DOT__genblk1__BRA__12__KET____DOT__fainst__DOT__HA1_Sum));
            tracep->chgBit(oldp+53,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__12__KET____DOT__fainst__DOT__HA1_Sum) 
                                     & (vlTOPp->ripple__DOT__m_carry 
                                        >> 0xcU))));
            tracep->chgBit(oldp+54,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__13__KET____DOT__fainst__DOT__HA1_Sum) 
                                           ^ (vlTOPp->ripple__DOT__m_carry 
                                              >> 0xdU)))));
            tracep->chgBit(oldp+55,((1U & (vlTOPp->ripple__DOT__m_carry 
                                           >> 0xdU))));
            tracep->chgBit(oldp+56,(vlTOPp->ripple__DOT__genblk1__BRA__13__KET____DOT__fainst__DOT__HA1_Sum));
            tracep->chgBit(oldp+57,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__13__KET____DOT__fainst__DOT__HA1_Sum) 
                                     & (vlTOPp->ripple__DOT__m_carry 
                                        >> 0xdU))));
            tracep->chgBit(oldp+58,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__14__KET____DOT__fainst__DOT__HA1_Sum) 
                                           ^ (vlTOPp->ripple__DOT__m_carry 
                                              >> 0xeU)))));
            tracep->chgBit(oldp+59,((1U & (vlTOPp->ripple__DOT__m_carry 
                                           >> 0xeU))));
            tracep->chgBit(oldp+60,(vlTOPp->ripple__DOT__genblk1__BRA__14__KET____DOT__fainst__DOT__HA1_Sum));
            tracep->chgBit(oldp+61,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__14__KET____DOT__fainst__DOT__HA1_Sum) 
                                     & (vlTOPp->ripple__DOT__m_carry 
                                        >> 0xeU))));
            tracep->chgBit(oldp+62,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__15__KET____DOT__fainst__DOT__HA1_Sum) 
                                           ^ (vlTOPp->ripple__DOT__m_carry 
                                              >> 0xfU)))));
            tracep->chgBit(oldp+63,((1U & (vlTOPp->ripple__DOT__m_carry 
                                           >> 0xfU))));
            tracep->chgBit(oldp+64,(vlTOPp->ripple__DOT__genblk1__BRA__15__KET____DOT__fainst__DOT__HA1_Sum));
            tracep->chgBit(oldp+65,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__15__KET____DOT__fainst__DOT__HA1_Sum) 
                                     & (vlTOPp->ripple__DOT__m_carry 
                                        >> 0xfU))));
        }
        tracep->chgIData(oldp+66,(vlTOPp->Sum),17);
        tracep->chgSData(oldp+67,(vlTOPp->A),16);
        tracep->chgSData(oldp+68,(vlTOPp->B),16);
        tracep->chgBit(oldp+69,((1U & (((IData)(vlTOPp->A) 
                                        & (IData)(vlTOPp->B)) 
                                       | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__0__KET____DOT__fainst__DOT__HA1_Sum) 
                                          & vlTOPp->ripple__DOT__m_carry)))));
        tracep->chgBit(oldp+70,((1U & (IData)(vlTOPp->A))));
        tracep->chgBit(oldp+71,((1U & (IData)(vlTOPp->B))));
        tracep->chgBit(oldp+72,((1U & ((IData)(vlTOPp->A) 
                                       & (IData)(vlTOPp->B)))));
        tracep->chgBit(oldp+73,((1U & ((((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 1U) | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__1__KET____DOT__fainst__DOT__HA1_Sum) 
                                                  & (vlTOPp->ripple__DOT__m_carry 
                                                     >> 1U))))));
        tracep->chgBit(oldp+74,((1U & ((IData)(vlTOPp->A) 
                                       >> 1U))));
        tracep->chgBit(oldp+75,((1U & ((IData)(vlTOPp->B) 
                                       >> 1U))));
        tracep->chgBit(oldp+76,((1U & (((IData)(vlTOPp->A) 
                                        & (IData)(vlTOPp->B)) 
                                       >> 1U))));
        tracep->chgBit(oldp+77,((1U & ((((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 2U) | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__2__KET____DOT__fainst__DOT__HA1_Sum) 
                                                  & (vlTOPp->ripple__DOT__m_carry 
                                                     >> 2U))))));
        tracep->chgBit(oldp+78,((1U & ((IData)(vlTOPp->A) 
                                       >> 2U))));
        tracep->chgBit(oldp+79,((1U & ((IData)(vlTOPp->B) 
                                       >> 2U))));
        tracep->chgBit(oldp+80,((1U & (((IData)(vlTOPp->A) 
                                        & (IData)(vlTOPp->B)) 
                                       >> 2U))));
        tracep->chgBit(oldp+81,((1U & ((((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 3U) | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__3__KET____DOT__fainst__DOT__HA1_Sum) 
                                                  & (vlTOPp->ripple__DOT__m_carry 
                                                     >> 3U))))));
        tracep->chgBit(oldp+82,((1U & ((IData)(vlTOPp->A) 
                                       >> 3U))));
        tracep->chgBit(oldp+83,((1U & ((IData)(vlTOPp->B) 
                                       >> 3U))));
        tracep->chgBit(oldp+84,((1U & (((IData)(vlTOPp->A) 
                                        & (IData)(vlTOPp->B)) 
                                       >> 3U))));
        tracep->chgBit(oldp+85,((1U & ((((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 4U) | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__4__KET____DOT__fainst__DOT__HA1_Sum) 
                                                  & (vlTOPp->ripple__DOT__m_carry 
                                                     >> 4U))))));
        tracep->chgBit(oldp+86,((1U & ((IData)(vlTOPp->A) 
                                       >> 4U))));
        tracep->chgBit(oldp+87,((1U & ((IData)(vlTOPp->B) 
                                       >> 4U))));
        tracep->chgBit(oldp+88,((1U & (((IData)(vlTOPp->A) 
                                        & (IData)(vlTOPp->B)) 
                                       >> 4U))));
        tracep->chgBit(oldp+89,((1U & ((((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 5U) | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__5__KET____DOT__fainst__DOT__HA1_Sum) 
                                                  & (vlTOPp->ripple__DOT__m_carry 
                                                     >> 5U))))));
        tracep->chgBit(oldp+90,((1U & ((IData)(vlTOPp->A) 
                                       >> 5U))));
        tracep->chgBit(oldp+91,((1U & ((IData)(vlTOPp->B) 
                                       >> 5U))));
        tracep->chgBit(oldp+92,((1U & (((IData)(vlTOPp->A) 
                                        & (IData)(vlTOPp->B)) 
                                       >> 5U))));
        tracep->chgBit(oldp+93,((1U & ((((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 6U) | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__6__KET____DOT__fainst__DOT__HA1_Sum) 
                                                  & (vlTOPp->ripple__DOT__m_carry 
                                                     >> 6U))))));
        tracep->chgBit(oldp+94,((1U & ((IData)(vlTOPp->A) 
                                       >> 6U))));
        tracep->chgBit(oldp+95,((1U & ((IData)(vlTOPp->B) 
                                       >> 6U))));
        tracep->chgBit(oldp+96,((1U & (((IData)(vlTOPp->A) 
                                        & (IData)(vlTOPp->B)) 
                                       >> 6U))));
        tracep->chgBit(oldp+97,((1U & ((((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 7U) | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__7__KET____DOT__fainst__DOT__HA1_Sum) 
                                                  & (vlTOPp->ripple__DOT__m_carry 
                                                     >> 7U))))));
        tracep->chgBit(oldp+98,((1U & ((IData)(vlTOPp->A) 
                                       >> 7U))));
        tracep->chgBit(oldp+99,((1U & ((IData)(vlTOPp->B) 
                                       >> 7U))));
        tracep->chgBit(oldp+100,((1U & (((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 7U))));
        tracep->chgBit(oldp+101,((1U & ((((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 8U) | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__8__KET____DOT__fainst__DOT__HA1_Sum) 
                                                   & (vlTOPp->ripple__DOT__m_carry 
                                                      >> 8U))))));
        tracep->chgBit(oldp+102,((1U & ((IData)(vlTOPp->A) 
                                        >> 8U))));
        tracep->chgBit(oldp+103,((1U & ((IData)(vlTOPp->B) 
                                        >> 8U))));
        tracep->chgBit(oldp+104,((1U & (((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 8U))));
        tracep->chgBit(oldp+105,((1U & ((((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 9U) | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__9__KET____DOT__fainst__DOT__HA1_Sum) 
                                                   & (vlTOPp->ripple__DOT__m_carry 
                                                      >> 9U))))));
        tracep->chgBit(oldp+106,((1U & ((IData)(vlTOPp->A) 
                                        >> 9U))));
        tracep->chgBit(oldp+107,((1U & ((IData)(vlTOPp->B) 
                                        >> 9U))));
        tracep->chgBit(oldp+108,((1U & (((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 9U))));
        tracep->chgBit(oldp+109,((1U & ((((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 0xaU) | 
                                        ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__10__KET____DOT__fainst__DOT__HA1_Sum) 
                                         & (vlTOPp->ripple__DOT__m_carry 
                                            >> 0xaU))))));
        tracep->chgBit(oldp+110,((1U & ((IData)(vlTOPp->A) 
                                        >> 0xaU))));
        tracep->chgBit(oldp+111,((1U & ((IData)(vlTOPp->B) 
                                        >> 0xaU))));
        tracep->chgBit(oldp+112,((1U & (((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 0xaU))));
        tracep->chgBit(oldp+113,((1U & ((((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 0xbU) | 
                                        ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__11__KET____DOT__fainst__DOT__HA1_Sum) 
                                         & (vlTOPp->ripple__DOT__m_carry 
                                            >> 0xbU))))));
        tracep->chgBit(oldp+114,((1U & ((IData)(vlTOPp->A) 
                                        >> 0xbU))));
        tracep->chgBit(oldp+115,((1U & ((IData)(vlTOPp->B) 
                                        >> 0xbU))));
        tracep->chgBit(oldp+116,((1U & (((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 0xbU))));
        tracep->chgBit(oldp+117,((1U & ((((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 0xcU) | 
                                        ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__12__KET____DOT__fainst__DOT__HA1_Sum) 
                                         & (vlTOPp->ripple__DOT__m_carry 
                                            >> 0xcU))))));
        tracep->chgBit(oldp+118,((1U & ((IData)(vlTOPp->A) 
                                        >> 0xcU))));
        tracep->chgBit(oldp+119,((1U & ((IData)(vlTOPp->B) 
                                        >> 0xcU))));
        tracep->chgBit(oldp+120,((1U & (((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 0xcU))));
        tracep->chgBit(oldp+121,((1U & ((((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 0xdU) | 
                                        ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__13__KET____DOT__fainst__DOT__HA1_Sum) 
                                         & (vlTOPp->ripple__DOT__m_carry 
                                            >> 0xdU))))));
        tracep->chgBit(oldp+122,((1U & ((IData)(vlTOPp->A) 
                                        >> 0xdU))));
        tracep->chgBit(oldp+123,((1U & ((IData)(vlTOPp->B) 
                                        >> 0xdU))));
        tracep->chgBit(oldp+124,((1U & (((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 0xdU))));
        tracep->chgBit(oldp+125,((1U & ((((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 0xeU) | 
                                        ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__14__KET____DOT__fainst__DOT__HA1_Sum) 
                                         & (vlTOPp->ripple__DOT__m_carry 
                                            >> 0xeU))))));
        tracep->chgBit(oldp+126,((1U & ((IData)(vlTOPp->A) 
                                        >> 0xeU))));
        tracep->chgBit(oldp+127,((1U & ((IData)(vlTOPp->B) 
                                        >> 0xeU))));
        tracep->chgBit(oldp+128,((1U & (((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 0xeU))));
        tracep->chgBit(oldp+129,((1U & ((((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 0xfU) | 
                                        ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__15__KET____DOT__fainst__DOT__HA1_Sum) 
                                         & (vlTOPp->ripple__DOT__m_carry 
                                            >> 0xfU))))));
        tracep->chgBit(oldp+130,((1U & ((IData)(vlTOPp->A) 
                                        >> 0xfU))));
        tracep->chgBit(oldp+131,((1U & ((IData)(vlTOPp->B) 
                                        >> 0xfU))));
        tracep->chgBit(oldp+132,((1U & (((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 0xfU))));
    }
}

void Vripple::traceCleanup(void* userp, VerilatedVcd* /*unused*/) {
    Vripple__Syms* __restrict vlSymsp = static_cast<Vripple__Syms*>(userp);
    Vripple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlTOPp->__Vm_traceActivity[0U] = 0U;
        vlTOPp->__Vm_traceActivity[1U] = 0U;
    }
}
