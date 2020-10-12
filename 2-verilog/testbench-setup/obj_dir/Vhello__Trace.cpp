// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vhello__Syms.h"


void Vhello::traceChgTop0(void* userp, VerilatedVcd* tracep) {
    Vhello__Syms* __restrict vlSymsp = static_cast<Vhello__Syms*>(userp);
    Vhello* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        vlTOPp->traceChgSub0(userp, tracep);
    }
}

void Vhello::traceChgSub0(void* userp, VerilatedVcd* tracep) {
    Vhello__Syms* __restrict vlSymsp = static_cast<Vhello__Syms*>(userp);
    Vhello* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->chgBit(oldp+0,(vlTOPp->i_clk));
        tracep->chgBit(oldp+1,(vlTOPp->i_reset));
        tracep->chgBit(oldp+2,(vlTOPp->test));
    }
}

void Vhello::traceCleanup(void* userp, VerilatedVcd* /*unused*/) {
    Vhello__Syms* __restrict vlSymsp = static_cast<Vhello__Syms*>(userp);
    Vhello* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlTOPp->__Vm_traceActivity[0U] = 0U;
    }
}
