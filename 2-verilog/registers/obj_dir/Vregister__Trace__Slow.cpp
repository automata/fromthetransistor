// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vregister__Syms.h"


//======================

void Vregister::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, __VlSymsp);
    traceRegister(tfp->spTrace());
}

void Vregister::traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vregister__Syms* __restrict vlSymsp = static_cast<Vregister__Syms*>(userp);
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vregister::traceInitTop(vlSymsp, tracep);
    tracep->scopeEscape('.');
}

//======================


void Vregister::traceInitTop(void* userp, VerilatedVcd* tracep) {
    Vregister__Syms* __restrict vlSymsp = static_cast<Vregister__Syms*>(userp);
    Vregister* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceInitSub0(userp, tracep);
    }
}

void Vregister::traceInitSub0(void* userp, VerilatedVcd* tracep) {
    Vregister__Syms* __restrict vlSymsp = static_cast<Vregister__Syms*>(userp);
    Vregister* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBit(c+1,"enable", false,-1);
        tracep->declBit(c+2,"reset", false,-1);
        tracep->declBit(c+3,"clk", false,-1);
        tracep->declBus(c+4,"signals", false,-1, 7,0);
        tracep->declBus(c+5,"bits", false,-1, 7,0);
        tracep->declBit(c+1,"register enable", false,-1);
        tracep->declBit(c+2,"register reset", false,-1);
        tracep->declBit(c+3,"register clk", false,-1);
        tracep->declBus(c+4,"register signals", false,-1, 7,0);
        tracep->declBus(c+5,"register bits", false,-1, 7,0);
    }
}

void Vregister::traceRegister(VerilatedVcd* tracep) {
    // Body
    {
        tracep->addFullCb(&traceFullTop0, __VlSymsp);
        tracep->addChgCb(&traceChgTop0, __VlSymsp);
        tracep->addCleanupCb(&traceCleanup, __VlSymsp);
    }
}

void Vregister::traceFullTop0(void* userp, VerilatedVcd* tracep) {
    Vregister__Syms* __restrict vlSymsp = static_cast<Vregister__Syms*>(userp);
    Vregister* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceFullSub0(userp, tracep);
    }
}

void Vregister::traceFullSub0(void* userp, VerilatedVcd* tracep) {
    Vregister__Syms* __restrict vlSymsp = static_cast<Vregister__Syms*>(userp);
    Vregister* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullBit(oldp+1,(vlTOPp->enable));
        tracep->fullBit(oldp+2,(vlTOPp->reset));
        tracep->fullBit(oldp+3,(vlTOPp->clk));
        tracep->fullCData(oldp+4,(vlTOPp->signals),8);
        tracep->fullCData(oldp+5,(vlTOPp->bits),8);
    }
}
