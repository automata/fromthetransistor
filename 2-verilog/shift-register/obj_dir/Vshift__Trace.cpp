// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vshift__Syms.h"


void Vshift::traceChgTop0(void* userp, VerilatedVcd* tracep) {
    Vshift__Syms* __restrict vlSymsp = static_cast<Vshift__Syms*>(userp);
    Vshift* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        vlTOPp->traceChgSub0(userp, tracep);
    }
}

void Vshift::traceChgSub0(void* userp, VerilatedVcd* tracep) {
    Vshift__Syms* __restrict vlSymsp = static_cast<Vshift__Syms*>(userp);
    Vshift* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->chgCData(oldp+0,(vlTOPp->Dout0),4);
        tracep->chgCData(oldp+1,(vlTOPp->Dout1),4);
        tracep->chgCData(oldp+2,(vlTOPp->Dout2),4);
        tracep->chgCData(oldp+3,(vlTOPp->Dout3),4);
        tracep->chgBit(oldp+4,(vlTOPp->enable));
        tracep->chgBit(oldp+5,(vlTOPp->reset));
        tracep->chgBit(oldp+6,(vlTOPp->clk));
        tracep->chgCData(oldp+7,(vlTOPp->Din),4);
    }
}

void Vshift::traceCleanup(void* userp, VerilatedVcd* /*unused*/) {
    Vshift__Syms* __restrict vlSymsp = static_cast<Vshift__Syms*>(userp);
    Vshift* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlTOPp->__Vm_traceActivity[0U] = 0U;
    }
}
