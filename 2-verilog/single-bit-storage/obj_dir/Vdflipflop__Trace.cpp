// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vdflipflop__Syms.h"


void Vdflipflop::traceChgTop0(void* userp, VerilatedVcd* tracep) {
    Vdflipflop__Syms* __restrict vlSymsp = static_cast<Vdflipflop__Syms*>(userp);
    Vdflipflop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        vlTOPp->traceChgSub0(userp, tracep);
    }
}

void Vdflipflop::traceChgSub0(void* userp, VerilatedVcd* tracep) {
    Vdflipflop__Syms* __restrict vlSymsp = static_cast<Vdflipflop__Syms*>(userp);
    Vdflipflop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->chgBit(oldp+0,(vlTOPp->Q));
        tracep->chgBit(oldp+1,(vlTOPp->Qn));
        tracep->chgBit(oldp+2,(vlTOPp->D));
        tracep->chgBit(oldp+3,(vlTOPp->clk));
        tracep->chgBit(oldp+4,(vlTOPp->reset));
        tracep->chgBit(oldp+5,(vlTOPp->preset));
        tracep->chgBit(oldp+6,(vlTOPp->enable));
    }
}

void Vdflipflop::traceCleanup(void* userp, VerilatedVcd* /*unused*/) {
    Vdflipflop__Syms* __restrict vlSymsp = static_cast<Vdflipflop__Syms*>(userp);
    Vdflipflop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlTOPp->__Vm_traceActivity[0U] = 0U;
    }
}
