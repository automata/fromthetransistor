// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vshift__Syms.h"


//======================

void Vshift::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, __VlSymsp);
    traceRegister(tfp->spTrace());
}

void Vshift::traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vshift__Syms* __restrict vlSymsp = static_cast<Vshift__Syms*>(userp);
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vshift::traceInitTop(vlSymsp, tracep);
    tracep->scopeEscape('.');
}

//======================


void Vshift::traceInitTop(void* userp, VerilatedVcd* tracep) {
    Vshift__Syms* __restrict vlSymsp = static_cast<Vshift__Syms*>(userp);
    Vshift* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceInitSub0(userp, tracep);
    }
}

void Vshift::traceInitSub0(void* userp, VerilatedVcd* tracep) {
    Vshift__Syms* __restrict vlSymsp = static_cast<Vshift__Syms*>(userp);
    Vshift* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBus(c+1,"Dout0", false,-1, 3,0);
        tracep->declBus(c+2,"Dout1", false,-1, 3,0);
        tracep->declBus(c+3,"Dout2", false,-1, 3,0);
        tracep->declBus(c+4,"Dout3", false,-1, 3,0);
        tracep->declBit(c+5,"enable", false,-1);
        tracep->declBit(c+6,"reset", false,-1);
        tracep->declBit(c+7,"clk", false,-1);
        tracep->declBus(c+8,"Din", false,-1, 3,0);
        tracep->declBus(c+1,"shift Dout0", false,-1, 3,0);
        tracep->declBus(c+2,"shift Dout1", false,-1, 3,0);
        tracep->declBus(c+3,"shift Dout2", false,-1, 3,0);
        tracep->declBus(c+4,"shift Dout3", false,-1, 3,0);
        tracep->declBit(c+5,"shift enable", false,-1);
        tracep->declBit(c+6,"shift reset", false,-1);
        tracep->declBit(c+7,"shift clk", false,-1);
        tracep->declBus(c+8,"shift Din", false,-1, 3,0);
    }
}

void Vshift::traceRegister(VerilatedVcd* tracep) {
    // Body
    {
        tracep->addFullCb(&traceFullTop0, __VlSymsp);
        tracep->addChgCb(&traceChgTop0, __VlSymsp);
        tracep->addCleanupCb(&traceCleanup, __VlSymsp);
    }
}

void Vshift::traceFullTop0(void* userp, VerilatedVcd* tracep) {
    Vshift__Syms* __restrict vlSymsp = static_cast<Vshift__Syms*>(userp);
    Vshift* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceFullSub0(userp, tracep);
    }
}

void Vshift::traceFullSub0(void* userp, VerilatedVcd* tracep) {
    Vshift__Syms* __restrict vlSymsp = static_cast<Vshift__Syms*>(userp);
    Vshift* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullCData(oldp+1,(vlTOPp->Dout0),4);
        tracep->fullCData(oldp+2,(vlTOPp->Dout1),4);
        tracep->fullCData(oldp+3,(vlTOPp->Dout2),4);
        tracep->fullCData(oldp+4,(vlTOPp->Dout3),4);
        tracep->fullBit(oldp+5,(vlTOPp->enable));
        tracep->fullBit(oldp+6,(vlTOPp->reset));
        tracep->fullBit(oldp+7,(vlTOPp->clk));
        tracep->fullCData(oldp+8,(vlTOPp->Din),4);
    }
}
