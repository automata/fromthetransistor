// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vfull_adder__Syms.h"


void Vfull_adder::traceChgTop0(void* userp, VerilatedVcd* tracep) {
    Vfull_adder__Syms* __restrict vlSymsp = static_cast<Vfull_adder__Syms*>(userp);
    Vfull_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        vlTOPp->traceChgSub0(userp, tracep);
    }
}

void Vfull_adder::traceChgSub0(void* userp, VerilatedVcd* tracep) {
    Vfull_adder__Syms* __restrict vlSymsp = static_cast<Vfull_adder__Syms*>(userp);
    Vfull_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->chgBit(oldp+0,(vlTOPp->Sum));
        tracep->chgBit(oldp+1,(vlTOPp->Cout));
        tracep->chgBit(oldp+2,(vlTOPp->A));
        tracep->chgBit(oldp+3,(vlTOPp->B));
        tracep->chgBit(oldp+4,(vlTOPp->Cin));
        tracep->chgBit(oldp+5,(vlTOPp->full_adder__DOT__HA1_Sum));
        tracep->chgBit(oldp+6,(((IData)(vlTOPp->A) 
                                & (IData)(vlTOPp->B))));
        tracep->chgBit(oldp+7,(((IData)(vlTOPp->full_adder__DOT__HA1_Sum) 
                                & (IData)(vlTOPp->Cin))));
    }
}

void Vfull_adder::traceCleanup(void* userp, VerilatedVcd* /*unused*/) {
    Vfull_adder__Syms* __restrict vlSymsp = static_cast<Vfull_adder__Syms*>(userp);
    Vfull_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlTOPp->__Vm_traceActivity[0U] = 0U;
    }
}
