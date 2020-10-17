// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vregister__Syms.h"


void Vregister::traceChgTop0(void* userp, VerilatedVcd* tracep) {
    Vregister__Syms* __restrict vlSymsp = static_cast<Vregister__Syms*>(userp);
    Vregister* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        vlTOPp->traceChgSub0(userp, tracep);
    }
}

void Vregister::traceChgSub0(void* userp, VerilatedVcd* tracep) {
    Vregister__Syms* __restrict vlSymsp = static_cast<Vregister__Syms*>(userp);
    Vregister* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->chgBit(oldp+0,(vlTOPp->enable));
        tracep->chgBit(oldp+1,(vlTOPp->reset));
        tracep->chgBit(oldp+2,(vlTOPp->clk));
        tracep->chgCData(oldp+3,(vlTOPp->signals),8);
        tracep->chgCData(oldp+4,(vlTOPp->bits),8);
    }
}

void Vregister::traceCleanup(void* userp, VerilatedVcd* /*unused*/) {
    Vregister__Syms* __restrict vlSymsp = static_cast<Vregister__Syms*>(userp);
    Vregister* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlTOPp->__Vm_traceActivity[0U] = 0U;
    }
}
