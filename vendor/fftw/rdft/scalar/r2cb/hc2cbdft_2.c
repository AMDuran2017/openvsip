/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * See the file COPYING for license information.
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Mon Nov 10 21:00:59 EST 2008 */

#include "codelet-rdft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_hc2cdft -fma -reorder-insns -schedule-for-pipeline -compact -variables 4 -pipeline-latency 4 -sign 1 -n 2 -dif -name hc2cbdft_2 -include hc2cb.h */

/*
 * This function contains 10 FP additions, 4 FP multiplications,
 * (or, 8 additions, 2 multiplications, 2 fused multiply/add),
 * 11 stack variables, 0 constants, and 8 memory accesses
 */
#include "hc2cb.h"

static void hc2cbdft_2(R *Rp, R *Ip, R *Rm, R *Im, const R *W, stride rs, INT mb, INT me, INT ms)
{
     INT m;
     for (m = mb, W = W + ((mb - 1) * 2); m < me; m = m + 1, Rp = Rp + ms, Ip = Ip + ms, Rm = Rm - ms, Im = Im - ms, W = W + 2, MAKE_VOLATILE_STRIDE(rs)) {
	  E T9, Ta, T3, Tc, T7, T4;
	  {
	       E T1, T2, T5, T6;
	       T1 = Ip[0];
	       T2 = Im[0];
	       T5 = Rp[0];
	       T6 = Rm[0];
	       T9 = W[1];
	       Ta = T1 + T2;
	       T3 = T1 - T2;
	       Tc = T5 + T6;
	       T7 = T5 - T6;
	       T4 = W[0];
	  }
	  {
	       E Td, T8, Te, Tb;
	       Td = T9 * T7;
	       T8 = T4 * T7;
	       Te = FMA(T4, Ta, Td);
	       Tb = FNMS(T9, Ta, T8);
	       Rm[0] = Tc + Te;
	       Rp[0] = Tc - Te;
	       Im[0] = Tb - T3;
	       Ip[0] = T3 + Tb;
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 1, 2},
     {TW_NEXT, 1, 0}
};

static const hc2c_desc desc = { 2, "hc2cbdft_2", twinstr, &GENUS, {8, 2, 2, 0} };

void X(codelet_hc2cbdft_2) (planner *p) {
     X(khc2c_register) (p, hc2cbdft_2, &desc, HC2C_VIA_DFT);
}
#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_hc2cdft -compact -variables 4 -pipeline-latency 4 -sign 1 -n 2 -dif -name hc2cbdft_2 -include hc2cb.h */

/*
 * This function contains 10 FP additions, 4 FP multiplications,
 * (or, 8 additions, 2 multiplications, 2 fused multiply/add),
 * 9 stack variables, 0 constants, and 8 memory accesses
 */
#include "hc2cb.h"

static void hc2cbdft_2(R *Rp, R *Ip, R *Rm, R *Im, const R *W, stride rs, INT mb, INT me, INT ms)
{
     INT m;
     for (m = mb, W = W + ((mb - 1) * 2); m < me; m = m + 1, Rp = Rp + ms, Ip = Ip + ms, Rm = Rm - ms, Im = Im - ms, W = W + 2, MAKE_VOLATILE_STRIDE(rs)) {
	  E T3, T9, T7, Tb;
	  {
	       E T1, T2, T5, T6;
	       T1 = Ip[0];
	       T2 = Im[0];
	       T3 = T1 - T2;
	       T9 = T1 + T2;
	       T5 = Rp[0];
	       T6 = Rm[0];
	       T7 = T5 - T6;
	       Tb = T5 + T6;
	  }
	  {
	       E Ta, Tc, T4, T8;
	       T4 = W[0];
	       T8 = W[1];
	       Ta = FNMS(T8, T9, T4 * T7);
	       Tc = FMA(T8, T7, T4 * T9);
	       Ip[0] = T3 + Ta;
	       Rp[0] = Tb - Tc;
	       Im[0] = Ta - T3;
	       Rm[0] = Tb + Tc;
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 1, 2},
     {TW_NEXT, 1, 0}
};

static const hc2c_desc desc = { 2, "hc2cbdft_2", twinstr, &GENUS, {8, 2, 2, 0} };

void X(codelet_hc2cbdft_2) (planner *p) {
     X(khc2c_register) (p, hc2cbdft_2, &desc, HC2C_VIA_DFT);
}
#endif				/* HAVE_FMA */
