// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vripple__Syms.h"


//======================

void Vripple::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, __VlSymsp);
    traceRegister(tfp->spTrace());
}

void Vripple::traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vripple__Syms* __restrict vlSymsp = static_cast<Vripple__Syms*>(userp);
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vripple::traceInitTop(vlSymsp, tracep);
    tracep->scopeEscape('.');
}

//======================


void Vripple::traceInitTop(void* userp, VerilatedVcd* tracep) {
    Vripple__Syms* __restrict vlSymsp = static_cast<Vripple__Syms*>(userp);
    Vripple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceInitSub0(userp, tracep);
    }
}

void Vripple::traceInitSub0(void* userp, VerilatedVcd* tracep) {
    Vripple__Syms* __restrict vlSymsp = static_cast<Vripple__Syms*>(userp);
    Vripple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBus(c+67,"Sum", false,-1, 16,0);
        tracep->declBus(c+68,"A", false,-1, 15,0);
        tracep->declBus(c+69,"B", false,-1, 15,0);
        tracep->declBus(c+134,"ripple N", false,-1, 31,0);
        tracep->declBus(c+67,"ripple Sum", false,-1, 16,0);
        tracep->declBus(c+68,"ripple A", false,-1, 15,0);
        tracep->declBus(c+69,"ripple B", false,-1, 15,0);
        tracep->declBus(c+1,"ripple m_carry", false,-1, 16,0);
        tracep->declBus(c+2,"ripple m_sum", false,-1, 15,0);
        tracep->declBit(c+3,"ripple genblk1[0] fainst Sum", false,-1);
        tracep->declBit(c+70,"ripple genblk1[0] fainst Cout", false,-1);
        tracep->declBit(c+71,"ripple genblk1[0] fainst A", false,-1);
        tracep->declBit(c+72,"ripple genblk1[0] fainst B", false,-1);
        tracep->declBit(c+4,"ripple genblk1[0] fainst Cin", false,-1);
        tracep->declBit(c+5,"ripple genblk1[0] fainst HA1_Sum", false,-1);
        tracep->declBit(c+73,"ripple genblk1[0] fainst HA1_Cout", false,-1);
        tracep->declBit(c+6,"ripple genblk1[0] fainst HA2_Cout", false,-1);
        tracep->declBit(c+5,"ripple genblk1[0] fainst U1 Sum", false,-1);
        tracep->declBit(c+73,"ripple genblk1[0] fainst U1 Cout", false,-1);
        tracep->declBit(c+71,"ripple genblk1[0] fainst U1 A", false,-1);
        tracep->declBit(c+72,"ripple genblk1[0] fainst U1 B", false,-1);
        tracep->declBit(c+3,"ripple genblk1[0] fainst U2 Sum", false,-1);
        tracep->declBit(c+6,"ripple genblk1[0] fainst U2 Cout", false,-1);
        tracep->declBit(c+5,"ripple genblk1[0] fainst U2 A", false,-1);
        tracep->declBit(c+4,"ripple genblk1[0] fainst U2 B", false,-1);
        tracep->declBit(c+7,"ripple genblk1[1] fainst Sum", false,-1);
        tracep->declBit(c+74,"ripple genblk1[1] fainst Cout", false,-1);
        tracep->declBit(c+75,"ripple genblk1[1] fainst A", false,-1);
        tracep->declBit(c+76,"ripple genblk1[1] fainst B", false,-1);
        tracep->declBit(c+8,"ripple genblk1[1] fainst Cin", false,-1);
        tracep->declBit(c+9,"ripple genblk1[1] fainst HA1_Sum", false,-1);
        tracep->declBit(c+77,"ripple genblk1[1] fainst HA1_Cout", false,-1);
        tracep->declBit(c+10,"ripple genblk1[1] fainst HA2_Cout", false,-1);
        tracep->declBit(c+9,"ripple genblk1[1] fainst U1 Sum", false,-1);
        tracep->declBit(c+77,"ripple genblk1[1] fainst U1 Cout", false,-1);
        tracep->declBit(c+75,"ripple genblk1[1] fainst U1 A", false,-1);
        tracep->declBit(c+76,"ripple genblk1[1] fainst U1 B", false,-1);
        tracep->declBit(c+7,"ripple genblk1[1] fainst U2 Sum", false,-1);
        tracep->declBit(c+10,"ripple genblk1[1] fainst U2 Cout", false,-1);
        tracep->declBit(c+9,"ripple genblk1[1] fainst U2 A", false,-1);
        tracep->declBit(c+8,"ripple genblk1[1] fainst U2 B", false,-1);
        tracep->declBit(c+11,"ripple genblk1[2] fainst Sum", false,-1);
        tracep->declBit(c+78,"ripple genblk1[2] fainst Cout", false,-1);
        tracep->declBit(c+79,"ripple genblk1[2] fainst A", false,-1);
        tracep->declBit(c+80,"ripple genblk1[2] fainst B", false,-1);
        tracep->declBit(c+12,"ripple genblk1[2] fainst Cin", false,-1);
        tracep->declBit(c+13,"ripple genblk1[2] fainst HA1_Sum", false,-1);
        tracep->declBit(c+81,"ripple genblk1[2] fainst HA1_Cout", false,-1);
        tracep->declBit(c+14,"ripple genblk1[2] fainst HA2_Cout", false,-1);
        tracep->declBit(c+13,"ripple genblk1[2] fainst U1 Sum", false,-1);
        tracep->declBit(c+81,"ripple genblk1[2] fainst U1 Cout", false,-1);
        tracep->declBit(c+79,"ripple genblk1[2] fainst U1 A", false,-1);
        tracep->declBit(c+80,"ripple genblk1[2] fainst U1 B", false,-1);
        tracep->declBit(c+11,"ripple genblk1[2] fainst U2 Sum", false,-1);
        tracep->declBit(c+14,"ripple genblk1[2] fainst U2 Cout", false,-1);
        tracep->declBit(c+13,"ripple genblk1[2] fainst U2 A", false,-1);
        tracep->declBit(c+12,"ripple genblk1[2] fainst U2 B", false,-1);
        tracep->declBit(c+15,"ripple genblk1[3] fainst Sum", false,-1);
        tracep->declBit(c+82,"ripple genblk1[3] fainst Cout", false,-1);
        tracep->declBit(c+83,"ripple genblk1[3] fainst A", false,-1);
        tracep->declBit(c+84,"ripple genblk1[3] fainst B", false,-1);
        tracep->declBit(c+16,"ripple genblk1[3] fainst Cin", false,-1);
        tracep->declBit(c+17,"ripple genblk1[3] fainst HA1_Sum", false,-1);
        tracep->declBit(c+85,"ripple genblk1[3] fainst HA1_Cout", false,-1);
        tracep->declBit(c+18,"ripple genblk1[3] fainst HA2_Cout", false,-1);
        tracep->declBit(c+17,"ripple genblk1[3] fainst U1 Sum", false,-1);
        tracep->declBit(c+85,"ripple genblk1[3] fainst U1 Cout", false,-1);
        tracep->declBit(c+83,"ripple genblk1[3] fainst U1 A", false,-1);
        tracep->declBit(c+84,"ripple genblk1[3] fainst U1 B", false,-1);
        tracep->declBit(c+15,"ripple genblk1[3] fainst U2 Sum", false,-1);
        tracep->declBit(c+18,"ripple genblk1[3] fainst U2 Cout", false,-1);
        tracep->declBit(c+17,"ripple genblk1[3] fainst U2 A", false,-1);
        tracep->declBit(c+16,"ripple genblk1[3] fainst U2 B", false,-1);
        tracep->declBit(c+19,"ripple genblk1[4] fainst Sum", false,-1);
        tracep->declBit(c+86,"ripple genblk1[4] fainst Cout", false,-1);
        tracep->declBit(c+87,"ripple genblk1[4] fainst A", false,-1);
        tracep->declBit(c+88,"ripple genblk1[4] fainst B", false,-1);
        tracep->declBit(c+20,"ripple genblk1[4] fainst Cin", false,-1);
        tracep->declBit(c+21,"ripple genblk1[4] fainst HA1_Sum", false,-1);
        tracep->declBit(c+89,"ripple genblk1[4] fainst HA1_Cout", false,-1);
        tracep->declBit(c+22,"ripple genblk1[4] fainst HA2_Cout", false,-1);
        tracep->declBit(c+21,"ripple genblk1[4] fainst U1 Sum", false,-1);
        tracep->declBit(c+89,"ripple genblk1[4] fainst U1 Cout", false,-1);
        tracep->declBit(c+87,"ripple genblk1[4] fainst U1 A", false,-1);
        tracep->declBit(c+88,"ripple genblk1[4] fainst U1 B", false,-1);
        tracep->declBit(c+19,"ripple genblk1[4] fainst U2 Sum", false,-1);
        tracep->declBit(c+22,"ripple genblk1[4] fainst U2 Cout", false,-1);
        tracep->declBit(c+21,"ripple genblk1[4] fainst U2 A", false,-1);
        tracep->declBit(c+20,"ripple genblk1[4] fainst U2 B", false,-1);
        tracep->declBit(c+23,"ripple genblk1[5] fainst Sum", false,-1);
        tracep->declBit(c+90,"ripple genblk1[5] fainst Cout", false,-1);
        tracep->declBit(c+91,"ripple genblk1[5] fainst A", false,-1);
        tracep->declBit(c+92,"ripple genblk1[5] fainst B", false,-1);
        tracep->declBit(c+24,"ripple genblk1[5] fainst Cin", false,-1);
        tracep->declBit(c+25,"ripple genblk1[5] fainst HA1_Sum", false,-1);
        tracep->declBit(c+93,"ripple genblk1[5] fainst HA1_Cout", false,-1);
        tracep->declBit(c+26,"ripple genblk1[5] fainst HA2_Cout", false,-1);
        tracep->declBit(c+25,"ripple genblk1[5] fainst U1 Sum", false,-1);
        tracep->declBit(c+93,"ripple genblk1[5] fainst U1 Cout", false,-1);
        tracep->declBit(c+91,"ripple genblk1[5] fainst U1 A", false,-1);
        tracep->declBit(c+92,"ripple genblk1[5] fainst U1 B", false,-1);
        tracep->declBit(c+23,"ripple genblk1[5] fainst U2 Sum", false,-1);
        tracep->declBit(c+26,"ripple genblk1[5] fainst U2 Cout", false,-1);
        tracep->declBit(c+25,"ripple genblk1[5] fainst U2 A", false,-1);
        tracep->declBit(c+24,"ripple genblk1[5] fainst U2 B", false,-1);
        tracep->declBit(c+27,"ripple genblk1[6] fainst Sum", false,-1);
        tracep->declBit(c+94,"ripple genblk1[6] fainst Cout", false,-1);
        tracep->declBit(c+95,"ripple genblk1[6] fainst A", false,-1);
        tracep->declBit(c+96,"ripple genblk1[6] fainst B", false,-1);
        tracep->declBit(c+28,"ripple genblk1[6] fainst Cin", false,-1);
        tracep->declBit(c+29,"ripple genblk1[6] fainst HA1_Sum", false,-1);
        tracep->declBit(c+97,"ripple genblk1[6] fainst HA1_Cout", false,-1);
        tracep->declBit(c+30,"ripple genblk1[6] fainst HA2_Cout", false,-1);
        tracep->declBit(c+29,"ripple genblk1[6] fainst U1 Sum", false,-1);
        tracep->declBit(c+97,"ripple genblk1[6] fainst U1 Cout", false,-1);
        tracep->declBit(c+95,"ripple genblk1[6] fainst U1 A", false,-1);
        tracep->declBit(c+96,"ripple genblk1[6] fainst U1 B", false,-1);
        tracep->declBit(c+27,"ripple genblk1[6] fainst U2 Sum", false,-1);
        tracep->declBit(c+30,"ripple genblk1[6] fainst U2 Cout", false,-1);
        tracep->declBit(c+29,"ripple genblk1[6] fainst U2 A", false,-1);
        tracep->declBit(c+28,"ripple genblk1[6] fainst U2 B", false,-1);
        tracep->declBit(c+31,"ripple genblk1[7] fainst Sum", false,-1);
        tracep->declBit(c+98,"ripple genblk1[7] fainst Cout", false,-1);
        tracep->declBit(c+99,"ripple genblk1[7] fainst A", false,-1);
        tracep->declBit(c+100,"ripple genblk1[7] fainst B", false,-1);
        tracep->declBit(c+32,"ripple genblk1[7] fainst Cin", false,-1);
        tracep->declBit(c+33,"ripple genblk1[7] fainst HA1_Sum", false,-1);
        tracep->declBit(c+101,"ripple genblk1[7] fainst HA1_Cout", false,-1);
        tracep->declBit(c+34,"ripple genblk1[7] fainst HA2_Cout", false,-1);
        tracep->declBit(c+33,"ripple genblk1[7] fainst U1 Sum", false,-1);
        tracep->declBit(c+101,"ripple genblk1[7] fainst U1 Cout", false,-1);
        tracep->declBit(c+99,"ripple genblk1[7] fainst U1 A", false,-1);
        tracep->declBit(c+100,"ripple genblk1[7] fainst U1 B", false,-1);
        tracep->declBit(c+31,"ripple genblk1[7] fainst U2 Sum", false,-1);
        tracep->declBit(c+34,"ripple genblk1[7] fainst U2 Cout", false,-1);
        tracep->declBit(c+33,"ripple genblk1[7] fainst U2 A", false,-1);
        tracep->declBit(c+32,"ripple genblk1[7] fainst U2 B", false,-1);
        tracep->declBit(c+35,"ripple genblk1[8] fainst Sum", false,-1);
        tracep->declBit(c+102,"ripple genblk1[8] fainst Cout", false,-1);
        tracep->declBit(c+103,"ripple genblk1[8] fainst A", false,-1);
        tracep->declBit(c+104,"ripple genblk1[8] fainst B", false,-1);
        tracep->declBit(c+36,"ripple genblk1[8] fainst Cin", false,-1);
        tracep->declBit(c+37,"ripple genblk1[8] fainst HA1_Sum", false,-1);
        tracep->declBit(c+105,"ripple genblk1[8] fainst HA1_Cout", false,-1);
        tracep->declBit(c+38,"ripple genblk1[8] fainst HA2_Cout", false,-1);
        tracep->declBit(c+37,"ripple genblk1[8] fainst U1 Sum", false,-1);
        tracep->declBit(c+105,"ripple genblk1[8] fainst U1 Cout", false,-1);
        tracep->declBit(c+103,"ripple genblk1[8] fainst U1 A", false,-1);
        tracep->declBit(c+104,"ripple genblk1[8] fainst U1 B", false,-1);
        tracep->declBit(c+35,"ripple genblk1[8] fainst U2 Sum", false,-1);
        tracep->declBit(c+38,"ripple genblk1[8] fainst U2 Cout", false,-1);
        tracep->declBit(c+37,"ripple genblk1[8] fainst U2 A", false,-1);
        tracep->declBit(c+36,"ripple genblk1[8] fainst U2 B", false,-1);
        tracep->declBit(c+39,"ripple genblk1[9] fainst Sum", false,-1);
        tracep->declBit(c+106,"ripple genblk1[9] fainst Cout", false,-1);
        tracep->declBit(c+107,"ripple genblk1[9] fainst A", false,-1);
        tracep->declBit(c+108,"ripple genblk1[9] fainst B", false,-1);
        tracep->declBit(c+40,"ripple genblk1[9] fainst Cin", false,-1);
        tracep->declBit(c+41,"ripple genblk1[9] fainst HA1_Sum", false,-1);
        tracep->declBit(c+109,"ripple genblk1[9] fainst HA1_Cout", false,-1);
        tracep->declBit(c+42,"ripple genblk1[9] fainst HA2_Cout", false,-1);
        tracep->declBit(c+41,"ripple genblk1[9] fainst U1 Sum", false,-1);
        tracep->declBit(c+109,"ripple genblk1[9] fainst U1 Cout", false,-1);
        tracep->declBit(c+107,"ripple genblk1[9] fainst U1 A", false,-1);
        tracep->declBit(c+108,"ripple genblk1[9] fainst U1 B", false,-1);
        tracep->declBit(c+39,"ripple genblk1[9] fainst U2 Sum", false,-1);
        tracep->declBit(c+42,"ripple genblk1[9] fainst U2 Cout", false,-1);
        tracep->declBit(c+41,"ripple genblk1[9] fainst U2 A", false,-1);
        tracep->declBit(c+40,"ripple genblk1[9] fainst U2 B", false,-1);
        tracep->declBit(c+43,"ripple genblk1[10] fainst Sum", false,-1);
        tracep->declBit(c+110,"ripple genblk1[10] fainst Cout", false,-1);
        tracep->declBit(c+111,"ripple genblk1[10] fainst A", false,-1);
        tracep->declBit(c+112,"ripple genblk1[10] fainst B", false,-1);
        tracep->declBit(c+44,"ripple genblk1[10] fainst Cin", false,-1);
        tracep->declBit(c+45,"ripple genblk1[10] fainst HA1_Sum", false,-1);
        tracep->declBit(c+113,"ripple genblk1[10] fainst HA1_Cout", false,-1);
        tracep->declBit(c+46,"ripple genblk1[10] fainst HA2_Cout", false,-1);
        tracep->declBit(c+45,"ripple genblk1[10] fainst U1 Sum", false,-1);
        tracep->declBit(c+113,"ripple genblk1[10] fainst U1 Cout", false,-1);
        tracep->declBit(c+111,"ripple genblk1[10] fainst U1 A", false,-1);
        tracep->declBit(c+112,"ripple genblk1[10] fainst U1 B", false,-1);
        tracep->declBit(c+43,"ripple genblk1[10] fainst U2 Sum", false,-1);
        tracep->declBit(c+46,"ripple genblk1[10] fainst U2 Cout", false,-1);
        tracep->declBit(c+45,"ripple genblk1[10] fainst U2 A", false,-1);
        tracep->declBit(c+44,"ripple genblk1[10] fainst U2 B", false,-1);
        tracep->declBit(c+47,"ripple genblk1[11] fainst Sum", false,-1);
        tracep->declBit(c+114,"ripple genblk1[11] fainst Cout", false,-1);
        tracep->declBit(c+115,"ripple genblk1[11] fainst A", false,-1);
        tracep->declBit(c+116,"ripple genblk1[11] fainst B", false,-1);
        tracep->declBit(c+48,"ripple genblk1[11] fainst Cin", false,-1);
        tracep->declBit(c+49,"ripple genblk1[11] fainst HA1_Sum", false,-1);
        tracep->declBit(c+117,"ripple genblk1[11] fainst HA1_Cout", false,-1);
        tracep->declBit(c+50,"ripple genblk1[11] fainst HA2_Cout", false,-1);
        tracep->declBit(c+49,"ripple genblk1[11] fainst U1 Sum", false,-1);
        tracep->declBit(c+117,"ripple genblk1[11] fainst U1 Cout", false,-1);
        tracep->declBit(c+115,"ripple genblk1[11] fainst U1 A", false,-1);
        tracep->declBit(c+116,"ripple genblk1[11] fainst U1 B", false,-1);
        tracep->declBit(c+47,"ripple genblk1[11] fainst U2 Sum", false,-1);
        tracep->declBit(c+50,"ripple genblk1[11] fainst U2 Cout", false,-1);
        tracep->declBit(c+49,"ripple genblk1[11] fainst U2 A", false,-1);
        tracep->declBit(c+48,"ripple genblk1[11] fainst U2 B", false,-1);
        tracep->declBit(c+51,"ripple genblk1[12] fainst Sum", false,-1);
        tracep->declBit(c+118,"ripple genblk1[12] fainst Cout", false,-1);
        tracep->declBit(c+119,"ripple genblk1[12] fainst A", false,-1);
        tracep->declBit(c+120,"ripple genblk1[12] fainst B", false,-1);
        tracep->declBit(c+52,"ripple genblk1[12] fainst Cin", false,-1);
        tracep->declBit(c+53,"ripple genblk1[12] fainst HA1_Sum", false,-1);
        tracep->declBit(c+121,"ripple genblk1[12] fainst HA1_Cout", false,-1);
        tracep->declBit(c+54,"ripple genblk1[12] fainst HA2_Cout", false,-1);
        tracep->declBit(c+53,"ripple genblk1[12] fainst U1 Sum", false,-1);
        tracep->declBit(c+121,"ripple genblk1[12] fainst U1 Cout", false,-1);
        tracep->declBit(c+119,"ripple genblk1[12] fainst U1 A", false,-1);
        tracep->declBit(c+120,"ripple genblk1[12] fainst U1 B", false,-1);
        tracep->declBit(c+51,"ripple genblk1[12] fainst U2 Sum", false,-1);
        tracep->declBit(c+54,"ripple genblk1[12] fainst U2 Cout", false,-1);
        tracep->declBit(c+53,"ripple genblk1[12] fainst U2 A", false,-1);
        tracep->declBit(c+52,"ripple genblk1[12] fainst U2 B", false,-1);
        tracep->declBit(c+55,"ripple genblk1[13] fainst Sum", false,-1);
        tracep->declBit(c+122,"ripple genblk1[13] fainst Cout", false,-1);
        tracep->declBit(c+123,"ripple genblk1[13] fainst A", false,-1);
        tracep->declBit(c+124,"ripple genblk1[13] fainst B", false,-1);
        tracep->declBit(c+56,"ripple genblk1[13] fainst Cin", false,-1);
        tracep->declBit(c+57,"ripple genblk1[13] fainst HA1_Sum", false,-1);
        tracep->declBit(c+125,"ripple genblk1[13] fainst HA1_Cout", false,-1);
        tracep->declBit(c+58,"ripple genblk1[13] fainst HA2_Cout", false,-1);
        tracep->declBit(c+57,"ripple genblk1[13] fainst U1 Sum", false,-1);
        tracep->declBit(c+125,"ripple genblk1[13] fainst U1 Cout", false,-1);
        tracep->declBit(c+123,"ripple genblk1[13] fainst U1 A", false,-1);
        tracep->declBit(c+124,"ripple genblk1[13] fainst U1 B", false,-1);
        tracep->declBit(c+55,"ripple genblk1[13] fainst U2 Sum", false,-1);
        tracep->declBit(c+58,"ripple genblk1[13] fainst U2 Cout", false,-1);
        tracep->declBit(c+57,"ripple genblk1[13] fainst U2 A", false,-1);
        tracep->declBit(c+56,"ripple genblk1[13] fainst U2 B", false,-1);
        tracep->declBit(c+59,"ripple genblk1[14] fainst Sum", false,-1);
        tracep->declBit(c+126,"ripple genblk1[14] fainst Cout", false,-1);
        tracep->declBit(c+127,"ripple genblk1[14] fainst A", false,-1);
        tracep->declBit(c+128,"ripple genblk1[14] fainst B", false,-1);
        tracep->declBit(c+60,"ripple genblk1[14] fainst Cin", false,-1);
        tracep->declBit(c+61,"ripple genblk1[14] fainst HA1_Sum", false,-1);
        tracep->declBit(c+129,"ripple genblk1[14] fainst HA1_Cout", false,-1);
        tracep->declBit(c+62,"ripple genblk1[14] fainst HA2_Cout", false,-1);
        tracep->declBit(c+61,"ripple genblk1[14] fainst U1 Sum", false,-1);
        tracep->declBit(c+129,"ripple genblk1[14] fainst U1 Cout", false,-1);
        tracep->declBit(c+127,"ripple genblk1[14] fainst U1 A", false,-1);
        tracep->declBit(c+128,"ripple genblk1[14] fainst U1 B", false,-1);
        tracep->declBit(c+59,"ripple genblk1[14] fainst U2 Sum", false,-1);
        tracep->declBit(c+62,"ripple genblk1[14] fainst U2 Cout", false,-1);
        tracep->declBit(c+61,"ripple genblk1[14] fainst U2 A", false,-1);
        tracep->declBit(c+60,"ripple genblk1[14] fainst U2 B", false,-1);
        tracep->declBit(c+63,"ripple genblk1[15] fainst Sum", false,-1);
        tracep->declBit(c+130,"ripple genblk1[15] fainst Cout", false,-1);
        tracep->declBit(c+131,"ripple genblk1[15] fainst A", false,-1);
        tracep->declBit(c+132,"ripple genblk1[15] fainst B", false,-1);
        tracep->declBit(c+64,"ripple genblk1[15] fainst Cin", false,-1);
        tracep->declBit(c+65,"ripple genblk1[15] fainst HA1_Sum", false,-1);
        tracep->declBit(c+133,"ripple genblk1[15] fainst HA1_Cout", false,-1);
        tracep->declBit(c+66,"ripple genblk1[15] fainst HA2_Cout", false,-1);
        tracep->declBit(c+65,"ripple genblk1[15] fainst U1 Sum", false,-1);
        tracep->declBit(c+133,"ripple genblk1[15] fainst U1 Cout", false,-1);
        tracep->declBit(c+131,"ripple genblk1[15] fainst U1 A", false,-1);
        tracep->declBit(c+132,"ripple genblk1[15] fainst U1 B", false,-1);
        tracep->declBit(c+63,"ripple genblk1[15] fainst U2 Sum", false,-1);
        tracep->declBit(c+66,"ripple genblk1[15] fainst U2 Cout", false,-1);
        tracep->declBit(c+65,"ripple genblk1[15] fainst U2 A", false,-1);
        tracep->declBit(c+64,"ripple genblk1[15] fainst U2 B", false,-1);
    }
}

void Vripple::traceRegister(VerilatedVcd* tracep) {
    // Body
    {
        tracep->addFullCb(&traceFullTop0, __VlSymsp);
        tracep->addChgCb(&traceChgTop0, __VlSymsp);
        tracep->addCleanupCb(&traceCleanup, __VlSymsp);
    }
}

void Vripple::traceFullTop0(void* userp, VerilatedVcd* tracep) {
    Vripple__Syms* __restrict vlSymsp = static_cast<Vripple__Syms*>(userp);
    Vripple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceFullSub0(userp, tracep);
    }
}

void Vripple::traceFullSub0(void* userp, VerilatedVcd* tracep) {
    Vripple__Syms* __restrict vlSymsp = static_cast<Vripple__Syms*>(userp);
    Vripple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullIData(oldp+1,(vlTOPp->ripple__DOT__m_carry),17);
        tracep->fullSData(oldp+2,(vlTOPp->ripple__DOT__m_sum),16);
        tracep->fullBit(oldp+3,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__0__KET____DOT__fainst__DOT__HA1_Sum) 
                                       ^ vlTOPp->ripple__DOT__m_carry))));
        tracep->fullBit(oldp+4,((1U & vlTOPp->ripple__DOT__m_carry)));
        tracep->fullBit(oldp+5,(vlTOPp->ripple__DOT__genblk1__BRA__0__KET____DOT__fainst__DOT__HA1_Sum));
        tracep->fullBit(oldp+6,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__0__KET____DOT__fainst__DOT__HA1_Sum) 
                                 & vlTOPp->ripple__DOT__m_carry)));
        tracep->fullBit(oldp+7,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__1__KET____DOT__fainst__DOT__HA1_Sum) 
                                       ^ (vlTOPp->ripple__DOT__m_carry 
                                          >> 1U)))));
        tracep->fullBit(oldp+8,((1U & (vlTOPp->ripple__DOT__m_carry 
                                       >> 1U))));
        tracep->fullBit(oldp+9,(vlTOPp->ripple__DOT__genblk1__BRA__1__KET____DOT__fainst__DOT__HA1_Sum));
        tracep->fullBit(oldp+10,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__1__KET____DOT__fainst__DOT__HA1_Sum) 
                                  & (vlTOPp->ripple__DOT__m_carry 
                                     >> 1U))));
        tracep->fullBit(oldp+11,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__2__KET____DOT__fainst__DOT__HA1_Sum) 
                                        ^ (vlTOPp->ripple__DOT__m_carry 
                                           >> 2U)))));
        tracep->fullBit(oldp+12,((1U & (vlTOPp->ripple__DOT__m_carry 
                                        >> 2U))));
        tracep->fullBit(oldp+13,(vlTOPp->ripple__DOT__genblk1__BRA__2__KET____DOT__fainst__DOT__HA1_Sum));
        tracep->fullBit(oldp+14,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__2__KET____DOT__fainst__DOT__HA1_Sum) 
                                  & (vlTOPp->ripple__DOT__m_carry 
                                     >> 2U))));
        tracep->fullBit(oldp+15,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__3__KET____DOT__fainst__DOT__HA1_Sum) 
                                        ^ (vlTOPp->ripple__DOT__m_carry 
                                           >> 3U)))));
        tracep->fullBit(oldp+16,((1U & (vlTOPp->ripple__DOT__m_carry 
                                        >> 3U))));
        tracep->fullBit(oldp+17,(vlTOPp->ripple__DOT__genblk1__BRA__3__KET____DOT__fainst__DOT__HA1_Sum));
        tracep->fullBit(oldp+18,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__3__KET____DOT__fainst__DOT__HA1_Sum) 
                                  & (vlTOPp->ripple__DOT__m_carry 
                                     >> 3U))));
        tracep->fullBit(oldp+19,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__4__KET____DOT__fainst__DOT__HA1_Sum) 
                                        ^ (vlTOPp->ripple__DOT__m_carry 
                                           >> 4U)))));
        tracep->fullBit(oldp+20,((1U & (vlTOPp->ripple__DOT__m_carry 
                                        >> 4U))));
        tracep->fullBit(oldp+21,(vlTOPp->ripple__DOT__genblk1__BRA__4__KET____DOT__fainst__DOT__HA1_Sum));
        tracep->fullBit(oldp+22,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__4__KET____DOT__fainst__DOT__HA1_Sum) 
                                  & (vlTOPp->ripple__DOT__m_carry 
                                     >> 4U))));
        tracep->fullBit(oldp+23,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__5__KET____DOT__fainst__DOT__HA1_Sum) 
                                        ^ (vlTOPp->ripple__DOT__m_carry 
                                           >> 5U)))));
        tracep->fullBit(oldp+24,((1U & (vlTOPp->ripple__DOT__m_carry 
                                        >> 5U))));
        tracep->fullBit(oldp+25,(vlTOPp->ripple__DOT__genblk1__BRA__5__KET____DOT__fainst__DOT__HA1_Sum));
        tracep->fullBit(oldp+26,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__5__KET____DOT__fainst__DOT__HA1_Sum) 
                                  & (vlTOPp->ripple__DOT__m_carry 
                                     >> 5U))));
        tracep->fullBit(oldp+27,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__6__KET____DOT__fainst__DOT__HA1_Sum) 
                                        ^ (vlTOPp->ripple__DOT__m_carry 
                                           >> 6U)))));
        tracep->fullBit(oldp+28,((1U & (vlTOPp->ripple__DOT__m_carry 
                                        >> 6U))));
        tracep->fullBit(oldp+29,(vlTOPp->ripple__DOT__genblk1__BRA__6__KET____DOT__fainst__DOT__HA1_Sum));
        tracep->fullBit(oldp+30,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__6__KET____DOT__fainst__DOT__HA1_Sum) 
                                  & (vlTOPp->ripple__DOT__m_carry 
                                     >> 6U))));
        tracep->fullBit(oldp+31,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__7__KET____DOT__fainst__DOT__HA1_Sum) 
                                        ^ (vlTOPp->ripple__DOT__m_carry 
                                           >> 7U)))));
        tracep->fullBit(oldp+32,((1U & (vlTOPp->ripple__DOT__m_carry 
                                        >> 7U))));
        tracep->fullBit(oldp+33,(vlTOPp->ripple__DOT__genblk1__BRA__7__KET____DOT__fainst__DOT__HA1_Sum));
        tracep->fullBit(oldp+34,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__7__KET____DOT__fainst__DOT__HA1_Sum) 
                                  & (vlTOPp->ripple__DOT__m_carry 
                                     >> 7U))));
        tracep->fullBit(oldp+35,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__8__KET____DOT__fainst__DOT__HA1_Sum) 
                                        ^ (vlTOPp->ripple__DOT__m_carry 
                                           >> 8U)))));
        tracep->fullBit(oldp+36,((1U & (vlTOPp->ripple__DOT__m_carry 
                                        >> 8U))));
        tracep->fullBit(oldp+37,(vlTOPp->ripple__DOT__genblk1__BRA__8__KET____DOT__fainst__DOT__HA1_Sum));
        tracep->fullBit(oldp+38,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__8__KET____DOT__fainst__DOT__HA1_Sum) 
                                  & (vlTOPp->ripple__DOT__m_carry 
                                     >> 8U))));
        tracep->fullBit(oldp+39,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__9__KET____DOT__fainst__DOT__HA1_Sum) 
                                        ^ (vlTOPp->ripple__DOT__m_carry 
                                           >> 9U)))));
        tracep->fullBit(oldp+40,((1U & (vlTOPp->ripple__DOT__m_carry 
                                        >> 9U))));
        tracep->fullBit(oldp+41,(vlTOPp->ripple__DOT__genblk1__BRA__9__KET____DOT__fainst__DOT__HA1_Sum));
        tracep->fullBit(oldp+42,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__9__KET____DOT__fainst__DOT__HA1_Sum) 
                                  & (vlTOPp->ripple__DOT__m_carry 
                                     >> 9U))));
        tracep->fullBit(oldp+43,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__10__KET____DOT__fainst__DOT__HA1_Sum) 
                                        ^ (vlTOPp->ripple__DOT__m_carry 
                                           >> 0xaU)))));
        tracep->fullBit(oldp+44,((1U & (vlTOPp->ripple__DOT__m_carry 
                                        >> 0xaU))));
        tracep->fullBit(oldp+45,(vlTOPp->ripple__DOT__genblk1__BRA__10__KET____DOT__fainst__DOT__HA1_Sum));
        tracep->fullBit(oldp+46,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__10__KET____DOT__fainst__DOT__HA1_Sum) 
                                  & (vlTOPp->ripple__DOT__m_carry 
                                     >> 0xaU))));
        tracep->fullBit(oldp+47,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__11__KET____DOT__fainst__DOT__HA1_Sum) 
                                        ^ (vlTOPp->ripple__DOT__m_carry 
                                           >> 0xbU)))));
        tracep->fullBit(oldp+48,((1U & (vlTOPp->ripple__DOT__m_carry 
                                        >> 0xbU))));
        tracep->fullBit(oldp+49,(vlTOPp->ripple__DOT__genblk1__BRA__11__KET____DOT__fainst__DOT__HA1_Sum));
        tracep->fullBit(oldp+50,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__11__KET____DOT__fainst__DOT__HA1_Sum) 
                                  & (vlTOPp->ripple__DOT__m_carry 
                                     >> 0xbU))));
        tracep->fullBit(oldp+51,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__12__KET____DOT__fainst__DOT__HA1_Sum) 
                                        ^ (vlTOPp->ripple__DOT__m_carry 
                                           >> 0xcU)))));
        tracep->fullBit(oldp+52,((1U & (vlTOPp->ripple__DOT__m_carry 
                                        >> 0xcU))));
        tracep->fullBit(oldp+53,(vlTOPp->ripple__DOT__genblk1__BRA__12__KET____DOT__fainst__DOT__HA1_Sum));
        tracep->fullBit(oldp+54,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__12__KET____DOT__fainst__DOT__HA1_Sum) 
                                  & (vlTOPp->ripple__DOT__m_carry 
                                     >> 0xcU))));
        tracep->fullBit(oldp+55,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__13__KET____DOT__fainst__DOT__HA1_Sum) 
                                        ^ (vlTOPp->ripple__DOT__m_carry 
                                           >> 0xdU)))));
        tracep->fullBit(oldp+56,((1U & (vlTOPp->ripple__DOT__m_carry 
                                        >> 0xdU))));
        tracep->fullBit(oldp+57,(vlTOPp->ripple__DOT__genblk1__BRA__13__KET____DOT__fainst__DOT__HA1_Sum));
        tracep->fullBit(oldp+58,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__13__KET____DOT__fainst__DOT__HA1_Sum) 
                                  & (vlTOPp->ripple__DOT__m_carry 
                                     >> 0xdU))));
        tracep->fullBit(oldp+59,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__14__KET____DOT__fainst__DOT__HA1_Sum) 
                                        ^ (vlTOPp->ripple__DOT__m_carry 
                                           >> 0xeU)))));
        tracep->fullBit(oldp+60,((1U & (vlTOPp->ripple__DOT__m_carry 
                                        >> 0xeU))));
        tracep->fullBit(oldp+61,(vlTOPp->ripple__DOT__genblk1__BRA__14__KET____DOT__fainst__DOT__HA1_Sum));
        tracep->fullBit(oldp+62,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__14__KET____DOT__fainst__DOT__HA1_Sum) 
                                  & (vlTOPp->ripple__DOT__m_carry 
                                     >> 0xeU))));
        tracep->fullBit(oldp+63,((1U & ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__15__KET____DOT__fainst__DOT__HA1_Sum) 
                                        ^ (vlTOPp->ripple__DOT__m_carry 
                                           >> 0xfU)))));
        tracep->fullBit(oldp+64,((1U & (vlTOPp->ripple__DOT__m_carry 
                                        >> 0xfU))));
        tracep->fullBit(oldp+65,(vlTOPp->ripple__DOT__genblk1__BRA__15__KET____DOT__fainst__DOT__HA1_Sum));
        tracep->fullBit(oldp+66,(((IData)(vlTOPp->ripple__DOT__genblk1__BRA__15__KET____DOT__fainst__DOT__HA1_Sum) 
                                  & (vlTOPp->ripple__DOT__m_carry 
                                     >> 0xfU))));
        tracep->fullIData(oldp+67,(vlTOPp->Sum),17);
        tracep->fullSData(oldp+68,(vlTOPp->A),16);
        tracep->fullSData(oldp+69,(vlTOPp->B),16);
        tracep->fullBit(oldp+70,((1U & (((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__0__KET____DOT__fainst__DOT__HA1_Sum) 
                                           & vlTOPp->ripple__DOT__m_carry)))));
        tracep->fullBit(oldp+71,((1U & (IData)(vlTOPp->A))));
        tracep->fullBit(oldp+72,((1U & (IData)(vlTOPp->B))));
        tracep->fullBit(oldp+73,((1U & ((IData)(vlTOPp->A) 
                                        & (IData)(vlTOPp->B)))));
        tracep->fullBit(oldp+74,((1U & ((((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 1U) | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__1__KET____DOT__fainst__DOT__HA1_Sum) 
                                                   & (vlTOPp->ripple__DOT__m_carry 
                                                      >> 1U))))));
        tracep->fullBit(oldp+75,((1U & ((IData)(vlTOPp->A) 
                                        >> 1U))));
        tracep->fullBit(oldp+76,((1U & ((IData)(vlTOPp->B) 
                                        >> 1U))));
        tracep->fullBit(oldp+77,((1U & (((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 1U))));
        tracep->fullBit(oldp+78,((1U & ((((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 2U) | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__2__KET____DOT__fainst__DOT__HA1_Sum) 
                                                   & (vlTOPp->ripple__DOT__m_carry 
                                                      >> 2U))))));
        tracep->fullBit(oldp+79,((1U & ((IData)(vlTOPp->A) 
                                        >> 2U))));
        tracep->fullBit(oldp+80,((1U & ((IData)(vlTOPp->B) 
                                        >> 2U))));
        tracep->fullBit(oldp+81,((1U & (((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 2U))));
        tracep->fullBit(oldp+82,((1U & ((((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 3U) | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__3__KET____DOT__fainst__DOT__HA1_Sum) 
                                                   & (vlTOPp->ripple__DOT__m_carry 
                                                      >> 3U))))));
        tracep->fullBit(oldp+83,((1U & ((IData)(vlTOPp->A) 
                                        >> 3U))));
        tracep->fullBit(oldp+84,((1U & ((IData)(vlTOPp->B) 
                                        >> 3U))));
        tracep->fullBit(oldp+85,((1U & (((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 3U))));
        tracep->fullBit(oldp+86,((1U & ((((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 4U) | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__4__KET____DOT__fainst__DOT__HA1_Sum) 
                                                   & (vlTOPp->ripple__DOT__m_carry 
                                                      >> 4U))))));
        tracep->fullBit(oldp+87,((1U & ((IData)(vlTOPp->A) 
                                        >> 4U))));
        tracep->fullBit(oldp+88,((1U & ((IData)(vlTOPp->B) 
                                        >> 4U))));
        tracep->fullBit(oldp+89,((1U & (((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 4U))));
        tracep->fullBit(oldp+90,((1U & ((((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 5U) | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__5__KET____DOT__fainst__DOT__HA1_Sum) 
                                                   & (vlTOPp->ripple__DOT__m_carry 
                                                      >> 5U))))));
        tracep->fullBit(oldp+91,((1U & ((IData)(vlTOPp->A) 
                                        >> 5U))));
        tracep->fullBit(oldp+92,((1U & ((IData)(vlTOPp->B) 
                                        >> 5U))));
        tracep->fullBit(oldp+93,((1U & (((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 5U))));
        tracep->fullBit(oldp+94,((1U & ((((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 6U) | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__6__KET____DOT__fainst__DOT__HA1_Sum) 
                                                   & (vlTOPp->ripple__DOT__m_carry 
                                                      >> 6U))))));
        tracep->fullBit(oldp+95,((1U & ((IData)(vlTOPp->A) 
                                        >> 6U))));
        tracep->fullBit(oldp+96,((1U & ((IData)(vlTOPp->B) 
                                        >> 6U))));
        tracep->fullBit(oldp+97,((1U & (((IData)(vlTOPp->A) 
                                         & (IData)(vlTOPp->B)) 
                                        >> 6U))));
        tracep->fullBit(oldp+98,((1U & ((((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 7U) | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__7__KET____DOT__fainst__DOT__HA1_Sum) 
                                                   & (vlTOPp->ripple__DOT__m_carry 
                                                      >> 7U))))));
        tracep->fullBit(oldp+99,((1U & ((IData)(vlTOPp->A) 
                                        >> 7U))));
        tracep->fullBit(oldp+100,((1U & ((IData)(vlTOPp->B) 
                                         >> 7U))));
        tracep->fullBit(oldp+101,((1U & (((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 7U))));
        tracep->fullBit(oldp+102,((1U & ((((IData)(vlTOPp->A) 
                                           & (IData)(vlTOPp->B)) 
                                          >> 8U) | 
                                         ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__8__KET____DOT__fainst__DOT__HA1_Sum) 
                                          & (vlTOPp->ripple__DOT__m_carry 
                                             >> 8U))))));
        tracep->fullBit(oldp+103,((1U & ((IData)(vlTOPp->A) 
                                         >> 8U))));
        tracep->fullBit(oldp+104,((1U & ((IData)(vlTOPp->B) 
                                         >> 8U))));
        tracep->fullBit(oldp+105,((1U & (((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 8U))));
        tracep->fullBit(oldp+106,((1U & ((((IData)(vlTOPp->A) 
                                           & (IData)(vlTOPp->B)) 
                                          >> 9U) | 
                                         ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__9__KET____DOT__fainst__DOT__HA1_Sum) 
                                          & (vlTOPp->ripple__DOT__m_carry 
                                             >> 9U))))));
        tracep->fullBit(oldp+107,((1U & ((IData)(vlTOPp->A) 
                                         >> 9U))));
        tracep->fullBit(oldp+108,((1U & ((IData)(vlTOPp->B) 
                                         >> 9U))));
        tracep->fullBit(oldp+109,((1U & (((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 9U))));
        tracep->fullBit(oldp+110,((1U & ((((IData)(vlTOPp->A) 
                                           & (IData)(vlTOPp->B)) 
                                          >> 0xaU) 
                                         | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__10__KET____DOT__fainst__DOT__HA1_Sum) 
                                            & (vlTOPp->ripple__DOT__m_carry 
                                               >> 0xaU))))));
        tracep->fullBit(oldp+111,((1U & ((IData)(vlTOPp->A) 
                                         >> 0xaU))));
        tracep->fullBit(oldp+112,((1U & ((IData)(vlTOPp->B) 
                                         >> 0xaU))));
        tracep->fullBit(oldp+113,((1U & (((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 0xaU))));
        tracep->fullBit(oldp+114,((1U & ((((IData)(vlTOPp->A) 
                                           & (IData)(vlTOPp->B)) 
                                          >> 0xbU) 
                                         | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__11__KET____DOT__fainst__DOT__HA1_Sum) 
                                            & (vlTOPp->ripple__DOT__m_carry 
                                               >> 0xbU))))));
        tracep->fullBit(oldp+115,((1U & ((IData)(vlTOPp->A) 
                                         >> 0xbU))));
        tracep->fullBit(oldp+116,((1U & ((IData)(vlTOPp->B) 
                                         >> 0xbU))));
        tracep->fullBit(oldp+117,((1U & (((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 0xbU))));
        tracep->fullBit(oldp+118,((1U & ((((IData)(vlTOPp->A) 
                                           & (IData)(vlTOPp->B)) 
                                          >> 0xcU) 
                                         | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__12__KET____DOT__fainst__DOT__HA1_Sum) 
                                            & (vlTOPp->ripple__DOT__m_carry 
                                               >> 0xcU))))));
        tracep->fullBit(oldp+119,((1U & ((IData)(vlTOPp->A) 
                                         >> 0xcU))));
        tracep->fullBit(oldp+120,((1U & ((IData)(vlTOPp->B) 
                                         >> 0xcU))));
        tracep->fullBit(oldp+121,((1U & (((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 0xcU))));
        tracep->fullBit(oldp+122,((1U & ((((IData)(vlTOPp->A) 
                                           & (IData)(vlTOPp->B)) 
                                          >> 0xdU) 
                                         | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__13__KET____DOT__fainst__DOT__HA1_Sum) 
                                            & (vlTOPp->ripple__DOT__m_carry 
                                               >> 0xdU))))));
        tracep->fullBit(oldp+123,((1U & ((IData)(vlTOPp->A) 
                                         >> 0xdU))));
        tracep->fullBit(oldp+124,((1U & ((IData)(vlTOPp->B) 
                                         >> 0xdU))));
        tracep->fullBit(oldp+125,((1U & (((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 0xdU))));
        tracep->fullBit(oldp+126,((1U & ((((IData)(vlTOPp->A) 
                                           & (IData)(vlTOPp->B)) 
                                          >> 0xeU) 
                                         | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__14__KET____DOT__fainst__DOT__HA1_Sum) 
                                            & (vlTOPp->ripple__DOT__m_carry 
                                               >> 0xeU))))));
        tracep->fullBit(oldp+127,((1U & ((IData)(vlTOPp->A) 
                                         >> 0xeU))));
        tracep->fullBit(oldp+128,((1U & ((IData)(vlTOPp->B) 
                                         >> 0xeU))));
        tracep->fullBit(oldp+129,((1U & (((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 0xeU))));
        tracep->fullBit(oldp+130,((1U & ((((IData)(vlTOPp->A) 
                                           & (IData)(vlTOPp->B)) 
                                          >> 0xfU) 
                                         | ((IData)(vlTOPp->ripple__DOT__genblk1__BRA__15__KET____DOT__fainst__DOT__HA1_Sum) 
                                            & (vlTOPp->ripple__DOT__m_carry 
                                               >> 0xfU))))));
        tracep->fullBit(oldp+131,((1U & ((IData)(vlTOPp->A) 
                                         >> 0xfU))));
        tracep->fullBit(oldp+132,((1U & ((IData)(vlTOPp->B) 
                                         >> 0xfU))));
        tracep->fullBit(oldp+133,((1U & (((IData)(vlTOPp->A) 
                                          & (IData)(vlTOPp->B)) 
                                         >> 0xfU))));
        tracep->fullIData(oldp+134,(0x10U),32);
    }
}
