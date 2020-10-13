// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vdlatch__Syms.h"


//======================

void Vdlatch::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, __VlSymsp);
    traceRegister(tfp->spTrace());
}

void Vdlatch::traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vdlatch__Syms* __restrict vlSymsp = static_cast<Vdlatch__Syms*>(userp);
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vdlatch::traceInitTop(vlSymsp, tracep);
    tracep->scopeEscape('.');
}

//======================


void Vdlatch::traceInitTop(void* userp, VerilatedVcd* tracep) {
    Vdlatch__Syms* __restrict vlSymsp = static_cast<Vdlatch__Syms*>(userp);
    Vdlatch* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceInitSub0(userp, tracep);
    }
}

void Vdlatch::traceInitSub0(void* userp, VerilatedVcd* tracep) {
    Vdlatch__Syms* __restrict vlSymsp = static_cast<Vdlatch__Syms*>(userp);
    Vdlatch* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBit(c+1,"dlatch.clk", false,-1);
        tracep->declBit(c+2,"dlatch.D", false,-1);
        tracep->declBit(c+3,"dlatch.Q", false,-1);
        tracep->declBit(c+4,"dlatch.Qn", false,-1);
        tracep->declBit(c+5,"dflipflop.Q", false,-1);
        tracep->declBit(c+6,"dflipflop.Qn", false,-1);
        tracep->declBit(c+7,"dflipflop.D", false,-1);
        tracep->declBit(c+8,"dflipflop.clk", false,-1);
        tracep->declBit(c+9,"reset", false,-1);
        tracep->declBit(c+1,"dlatch clk", false,-1);
        tracep->declBit(c+2,"dlatch D", false,-1);
        tracep->declBit(c+3,"dlatch Q", false,-1);
        tracep->declBit(c+4,"dlatch Qn", false,-1);
        tracep->declBit(c+5,"dflipflop Q", false,-1);
        tracep->declBit(c+6,"dflipflop Qn", false,-1);
        tracep->declBit(c+7,"dflipflop D", false,-1);
        tracep->declBit(c+8,"dflipflop clk", false,-1);
        tracep->declBit(c+9,"dflipflop reset", false,-1);
    }
}

void Vdlatch::traceRegister(VerilatedVcd* tracep) {
    // Body
    {
        tracep->addFullCb(&traceFullTop0, __VlSymsp);
        tracep->addChgCb(&traceChgTop0, __VlSymsp);
        tracep->addCleanupCb(&traceCleanup, __VlSymsp);
    }
}

void Vdlatch::traceFullTop0(void* userp, VerilatedVcd* tracep) {
    Vdlatch__Syms* __restrict vlSymsp = static_cast<Vdlatch__Syms*>(userp);
    Vdlatch* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceFullSub0(userp, tracep);
    }
}

void Vdlatch::traceFullSub0(void* userp, VerilatedVcd* tracep) {
    Vdlatch__Syms* __restrict vlSymsp = static_cast<Vdlatch__Syms*>(userp);
    Vdlatch* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullBit(oldp+1,(vlTOPp->dlatch__02Eclk));
        tracep->fullBit(oldp+2,(vlTOPp->dlatch__02ED));
        tracep->fullBit(oldp+3,(vlTOPp->dlatch__02EQ));
        tracep->fullBit(oldp+4,(vlTOPp->dlatch__02EQn));
        tracep->fullBit(oldp+5,(vlTOPp->dflipflop__02EQ));
        tracep->fullBit(oldp+6,(vlTOPp->dflipflop__02EQn));
        tracep->fullBit(oldp+7,(vlTOPp->dflipflop__02ED));
        tracep->fullBit(oldp+8,(vlTOPp->dflipflop__02Eclk));
        tracep->fullBit(oldp+9,(vlTOPp->reset));
    }
}
