// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vfull_adder__Syms.h"


//======================

void Vfull_adder::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, __VlSymsp);
    traceRegister(tfp->spTrace());
}

void Vfull_adder::traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vfull_adder__Syms* __restrict vlSymsp = static_cast<Vfull_adder__Syms*>(userp);
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vfull_adder::traceInitTop(vlSymsp, tracep);
    tracep->scopeEscape('.');
}

//======================


void Vfull_adder::traceInitTop(void* userp, VerilatedVcd* tracep) {
    Vfull_adder__Syms* __restrict vlSymsp = static_cast<Vfull_adder__Syms*>(userp);
    Vfull_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceInitSub0(userp, tracep);
    }
}

void Vfull_adder::traceInitSub0(void* userp, VerilatedVcd* tracep) {
    Vfull_adder__Syms* __restrict vlSymsp = static_cast<Vfull_adder__Syms*>(userp);
    Vfull_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBit(c+1,"Sum", false,-1);
        tracep->declBit(c+2,"Cout", false,-1);
        tracep->declBit(c+3,"A", false,-1);
        tracep->declBit(c+4,"B", false,-1);
        tracep->declBit(c+5,"Cin", false,-1);
        tracep->declBit(c+1,"full_adder Sum", false,-1);
        tracep->declBit(c+2,"full_adder Cout", false,-1);
        tracep->declBit(c+3,"full_adder A", false,-1);
        tracep->declBit(c+4,"full_adder B", false,-1);
        tracep->declBit(c+5,"full_adder Cin", false,-1);
        tracep->declBit(c+6,"full_adder HA1_Sum", false,-1);
        tracep->declBit(c+7,"full_adder HA1_Cout", false,-1);
        tracep->declBit(c+8,"full_adder HA2_Cout", false,-1);
        tracep->declBit(c+6,"full_adder U1 Sum", false,-1);
        tracep->declBit(c+7,"full_adder U1 Cout", false,-1);
        tracep->declBit(c+3,"full_adder U1 A", false,-1);
        tracep->declBit(c+4,"full_adder U1 B", false,-1);
        tracep->declBit(c+1,"full_adder U2 Sum", false,-1);
        tracep->declBit(c+8,"full_adder U2 Cout", false,-1);
        tracep->declBit(c+6,"full_adder U2 A", false,-1);
        tracep->declBit(c+5,"full_adder U2 B", false,-1);
    }
}

void Vfull_adder::traceRegister(VerilatedVcd* tracep) {
    // Body
    {
        tracep->addFullCb(&traceFullTop0, __VlSymsp);
        tracep->addChgCb(&traceChgTop0, __VlSymsp);
        tracep->addCleanupCb(&traceCleanup, __VlSymsp);
    }
}

void Vfull_adder::traceFullTop0(void* userp, VerilatedVcd* tracep) {
    Vfull_adder__Syms* __restrict vlSymsp = static_cast<Vfull_adder__Syms*>(userp);
    Vfull_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceFullSub0(userp, tracep);
    }
}

void Vfull_adder::traceFullSub0(void* userp, VerilatedVcd* tracep) {
    Vfull_adder__Syms* __restrict vlSymsp = static_cast<Vfull_adder__Syms*>(userp);
    Vfull_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullBit(oldp+1,(vlTOPp->Sum));
        tracep->fullBit(oldp+2,(vlTOPp->Cout));
        tracep->fullBit(oldp+3,(vlTOPp->A));
        tracep->fullBit(oldp+4,(vlTOPp->B));
        tracep->fullBit(oldp+5,(vlTOPp->Cin));
        tracep->fullBit(oldp+6,(vlTOPp->full_adder__DOT__HA1_Sum));
        tracep->fullBit(oldp+7,(((IData)(vlTOPp->A) 
                                 & (IData)(vlTOPp->B))));
        tracep->fullBit(oldp+8,(((IData)(vlTOPp->full_adder__DOT__HA1_Sum) 
                                 & (IData)(vlTOPp->Cin))));
    }
}
