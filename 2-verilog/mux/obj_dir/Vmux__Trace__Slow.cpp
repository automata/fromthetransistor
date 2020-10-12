// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vmux__Syms.h"


//======================

void Vmux::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, __VlSymsp);
    traceRegister(tfp->spTrace());
}

void Vmux::traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vmux__Syms* __restrict vlSymsp = static_cast<Vmux__Syms*>(userp);
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vmux::traceInitTop(vlSymsp, tracep);
    tracep->scopeEscape('.');
}

//======================


void Vmux::traceInitTop(void* userp, VerilatedVcd* tracep) {
    Vmux__Syms* __restrict vlSymsp = static_cast<Vmux__Syms*>(userp);
    Vmux* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceInitSub0(userp, tracep);
    }
}

void Vmux::traceInitSub0(void* userp, VerilatedVcd* tracep) {
    Vmux__Syms* __restrict vlSymsp = static_cast<Vmux__Syms*>(userp);
    Vmux* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBus(c+1,"in", false,-1, 3,0);
        tracep->declBus(c+2,"sel", false,-1, 1,0);
        tracep->declBit(c+3,"out", false,-1);
        tracep->declBus(c+1,"mux in", false,-1, 3,0);
        tracep->declBus(c+2,"mux sel", false,-1, 1,0);
        tracep->declBit(c+3,"mux out", false,-1);
    }
}

void Vmux::traceRegister(VerilatedVcd* tracep) {
    // Body
    {
        tracep->addFullCb(&traceFullTop0, __VlSymsp);
        tracep->addChgCb(&traceChgTop0, __VlSymsp);
        tracep->addCleanupCb(&traceCleanup, __VlSymsp);
    }
}

void Vmux::traceFullTop0(void* userp, VerilatedVcd* tracep) {
    Vmux__Syms* __restrict vlSymsp = static_cast<Vmux__Syms*>(userp);
    Vmux* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceFullSub0(userp, tracep);
    }
}

void Vmux::traceFullSub0(void* userp, VerilatedVcd* tracep) {
    Vmux__Syms* __restrict vlSymsp = static_cast<Vmux__Syms*>(userp);
    Vmux* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullCData(oldp+1,(vlTOPp->in),4);
        tracep->fullCData(oldp+2,(vlTOPp->sel),2);
        tracep->fullBit(oldp+3,(vlTOPp->out));
    }
}
