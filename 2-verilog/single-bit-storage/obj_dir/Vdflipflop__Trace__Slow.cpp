// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vdflipflop__Syms.h"


//======================

void Vdflipflop::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, __VlSymsp);
    traceRegister(tfp->spTrace());
}

void Vdflipflop::traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vdflipflop__Syms* __restrict vlSymsp = static_cast<Vdflipflop__Syms*>(userp);
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vdflipflop::traceInitTop(vlSymsp, tracep);
    tracep->scopeEscape('.');
}

//======================


void Vdflipflop::traceInitTop(void* userp, VerilatedVcd* tracep) {
    Vdflipflop__Syms* __restrict vlSymsp = static_cast<Vdflipflop__Syms*>(userp);
    Vdflipflop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceInitSub0(userp, tracep);
    }
}

void Vdflipflop::traceInitSub0(void* userp, VerilatedVcd* tracep) {
    Vdflipflop__Syms* __restrict vlSymsp = static_cast<Vdflipflop__Syms*>(userp);
    Vdflipflop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBit(c+1,"Q", false,-1);
        tracep->declBit(c+2,"Qn", false,-1);
        tracep->declBit(c+3,"D", false,-1);
        tracep->declBit(c+4,"clk", false,-1);
        tracep->declBit(c+5,"reset", false,-1);
        tracep->declBit(c+6,"preset", false,-1);
        tracep->declBit(c+7,"enable", false,-1);
        tracep->declBit(c+1,"dflipflop Q", false,-1);
        tracep->declBit(c+2,"dflipflop Qn", false,-1);
        tracep->declBit(c+3,"dflipflop D", false,-1);
        tracep->declBit(c+4,"dflipflop clk", false,-1);
        tracep->declBit(c+5,"dflipflop reset", false,-1);
        tracep->declBit(c+6,"dflipflop preset", false,-1);
        tracep->declBit(c+7,"dflipflop enable", false,-1);
    }
}

void Vdflipflop::traceRegister(VerilatedVcd* tracep) {
    // Body
    {
        tracep->addFullCb(&traceFullTop0, __VlSymsp);
        tracep->addChgCb(&traceChgTop0, __VlSymsp);
        tracep->addCleanupCb(&traceCleanup, __VlSymsp);
    }
}

void Vdflipflop::traceFullTop0(void* userp, VerilatedVcd* tracep) {
    Vdflipflop__Syms* __restrict vlSymsp = static_cast<Vdflipflop__Syms*>(userp);
    Vdflipflop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceFullSub0(userp, tracep);
    }
}

void Vdflipflop::traceFullSub0(void* userp, VerilatedVcd* tracep) {
    Vdflipflop__Syms* __restrict vlSymsp = static_cast<Vdflipflop__Syms*>(userp);
    Vdflipflop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullBit(oldp+1,(vlTOPp->Q));
        tracep->fullBit(oldp+2,(vlTOPp->Qn));
        tracep->fullBit(oldp+3,(vlTOPp->D));
        tracep->fullBit(oldp+4,(vlTOPp->clk));
        tracep->fullBit(oldp+5,(vlTOPp->reset));
        tracep->fullBit(oldp+6,(vlTOPp->preset));
        tracep->fullBit(oldp+7,(vlTOPp->enable));
    }
}
