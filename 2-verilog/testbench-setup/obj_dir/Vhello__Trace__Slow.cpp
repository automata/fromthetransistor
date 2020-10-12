// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vhello__Syms.h"


//======================

void Vhello::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, __VlSymsp);
    traceRegister(tfp->spTrace());
}

void Vhello::traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vhello__Syms* __restrict vlSymsp = static_cast<Vhello__Syms*>(userp);
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vhello::traceInitTop(vlSymsp, tracep);
    tracep->scopeEscape('.');
}

//======================


void Vhello::traceInitTop(void* userp, VerilatedVcd* tracep) {
    Vhello__Syms* __restrict vlSymsp = static_cast<Vhello__Syms*>(userp);
    Vhello* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceInitSub0(userp, tracep);
    }
}

void Vhello::traceInitSub0(void* userp, VerilatedVcd* tracep) {
    Vhello__Syms* __restrict vlSymsp = static_cast<Vhello__Syms*>(userp);
    Vhello* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBit(c+1,"i_clk", false,-1);
        tracep->declBit(c+2,"i_reset", false,-1);
        tracep->declBit(c+3,"test", false,-1);
        tracep->declBit(c+1,"hello i_clk", false,-1);
        tracep->declBit(c+2,"hello i_reset", false,-1);
        tracep->declBit(c+3,"hello test", false,-1);
    }
}

void Vhello::traceRegister(VerilatedVcd* tracep) {
    // Body
    {
        tracep->addFullCb(&traceFullTop0, __VlSymsp);
        tracep->addChgCb(&traceChgTop0, __VlSymsp);
        tracep->addCleanupCb(&traceCleanup, __VlSymsp);
    }
}

void Vhello::traceFullTop0(void* userp, VerilatedVcd* tracep) {
    Vhello__Syms* __restrict vlSymsp = static_cast<Vhello__Syms*>(userp);
    Vhello* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceFullSub0(userp, tracep);
    }
}

void Vhello::traceFullSub0(void* userp, VerilatedVcd* tracep) {
    Vhello__Syms* __restrict vlSymsp = static_cast<Vhello__Syms*>(userp);
    Vhello* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullBit(oldp+1,(vlTOPp->i_clk));
        tracep->fullBit(oldp+2,(vlTOPp->i_reset));
        tracep->fullBit(oldp+3,(vlTOPp->test));
    }
}
