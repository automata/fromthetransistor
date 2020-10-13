// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vdlatch__Syms.h"


void Vdlatch::traceChgTop0(void* userp, VerilatedVcd* tracep) {
    Vdlatch__Syms* __restrict vlSymsp = static_cast<Vdlatch__Syms*>(userp);
    Vdlatch* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        vlTOPp->traceChgSub0(userp, tracep);
    }
}

void Vdlatch::traceChgSub0(void* userp, VerilatedVcd* tracep) {
    Vdlatch__Syms* __restrict vlSymsp = static_cast<Vdlatch__Syms*>(userp);
    Vdlatch* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->chgBit(oldp+0,(vlTOPp->dlatch__02Eclk));
        tracep->chgBit(oldp+1,(vlTOPp->dlatch__02ED));
        tracep->chgBit(oldp+2,(vlTOPp->dlatch__02EQ));
        tracep->chgBit(oldp+3,(vlTOPp->dlatch__02EQn));
        tracep->chgBit(oldp+4,(vlTOPp->dflipflop__02EQ));
        tracep->chgBit(oldp+5,(vlTOPp->dflipflop__02EQn));
        tracep->chgBit(oldp+6,(vlTOPp->dflipflop__02ED));
        tracep->chgBit(oldp+7,(vlTOPp->dflipflop__02Eclk));
        tracep->chgBit(oldp+8,(vlTOPp->reset));
    }
}

void Vdlatch::traceCleanup(void* userp, VerilatedVcd* /*unused*/) {
    Vdlatch__Syms* __restrict vlSymsp = static_cast<Vdlatch__Syms*>(userp);
    Vdlatch* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlTOPp->__Vm_traceActivity[0U] = 0U;
    }
}
