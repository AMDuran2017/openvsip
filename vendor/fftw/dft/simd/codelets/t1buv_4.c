/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * See the file COPYING for license information.
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Mon Nov 10 20:40:53 EST 2008 */

#include "codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_twiddle_c -fma -reorder-insns -schedule-for-pipeline -simd -compact -variables 4 -pipeline-latency 8 -n 4 -name t1buv_4 -include t1bu.h -sign 1 */

/*
 * This function contains 11 FP additions, 8 FP multiplications,
 * (or, 9 additions, 6 multiplications, 2 fused multiply/add),
 * 13 stack variables, 0 constants, and 8 memory accesses
 */
#include "t1bu.h"

static void t1buv_4(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     INT m;
     R *x;
     x = ii;
     for (m = mb, W = W + (mb * ((TWVL / VL) * 6)); m < me; m = m + VL, x = x + (VL * ms), W = W + (TWVL * 6), MAKE_VOLATILE_STRIDE(rs)) {
	  V T1, T7, T2, T5, T8, T3, T6;
	  T1 = LD(&(x[0]), ms, &(x[0]));
	  T7 = LD(&(x[WS(rs, 3)]), ms, &(x[WS(rs, 1)]));
	  T2 = LD(&(x[WS(rs, 2)]), ms, &(x[0]));
	  T5 = LD(&(x[WS(rs, 1)]), ms, &(x[WS(rs, 1)]));
	  T8 = BYTW(&(W[TWVL * 4]), T7);
	  T3 = BYTW(&(W[TWVL * 2]), T2);
	  T6 = BYTW(&(W[0]), T5);
	  {
	       V Ta, T4, Tb, T9;
	       Ta = VADD(T1, T3);
	       T4 = VSUB(T1, T3);
	       Tb = VADD(T6, T8);
	       T9 = VSUB(T6, T8);
	       ST(&(x[0]), VADD(Ta, Tb), ms, &(x[0]));
	       ST(&(x[WS(rs, 2)]), VSUB(Ta, Tb), ms, &(x[0]));
	       ST(&(x[WS(rs, 1)]), VFMAI(T9, T4), ms, &(x[WS(rs, 1)]));
	       ST(&(x[WS(rs, 3)]), VFNMSI(T9, T4), ms, &(x[WS(rs, 1)]));
	  }
     }
}

static const tw_instr twinstr[] = {
     VTW(0, 1),
     VTW(0, 2),
     VTW(0, 3),
     {TW_NEXT, VL, 0}
};

static const ct_desc desc = { 4, "t1buv_4", twinstr, &GENUS, {9, 6, 2, 0}, 0, 0, 0 };

void X(codelet_t1buv_4) (planner *p) {
     X(kdft_dit_register) (p, t1buv_4, &desc);
}
#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_twiddle_c -simd -compact -variables 4 -pipeline-latency 8 -n 4 -name t1buv_4 -include t1bu.h -sign 1 */

/*
 * This function contains 11 FP additions, 6 FP multiplications,
 * (or, 11 additions, 6 multiplications, 0 fused multiply/add),
 * 13 stack variables, 0 constants, and 8 memory accesses
 */
#include "t1bu.h"

static void t1buv_4(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     INT m;
     R *x;
     x = ii;
     for (m = mb, W = W + (mb * ((TWVL / VL) * 6)); m < me; m = m + VL, x = x + (VL * ms), W = W + (TWVL * 6), MAKE_VOLATILE_STRIDE(rs)) {
	  V T1, T8, T3, T6, T7, T2, T5;
	  T1 = LD(&(x[0]), ms, &(x[0]));
	  T7 = LD(&(x[WS(rs, 3)]), ms, &(x[WS(rs, 1)]));
	  T8 = BYTW(&(W[TWVL * 4]), T7);
	  T2 = LD(&(x[WS(rs, 2)]), ms, &(x[0]));
	  T3 = BYTW(&(W[TWVL * 2]), T2);
	  T5 = LD(&(x[WS(rs, 1)]), ms, &(x[WS(rs, 1)]));
	  T6 = BYTW(&(W[0]), T5);
	  {
	       V T4, T9, Ta, Tb;
	       T4 = VSUB(T1, T3);
	       T9 = VBYI(VSUB(T6, T8));
	       ST(&(x[WS(rs, 3)]), VSUB(T4, T9), ms, &(x[WS(rs, 1)]));
	       ST(&(x[WS(rs, 1)]), VADD(T4, T9), ms, &(x[WS(rs, 1)]));
	       Ta = VADD(T1, T3);
	       Tb = VADD(T6, T8);
	       ST(&(x[WS(rs, 2)]), VSUB(Ta, Tb), ms, &(x[0]));
	       ST(&(x[0]), VADD(Ta, Tb), ms, &(x[0]));
	  }
     }
}

static const tw_instr twinstr[] = {
     VTW(0, 1),
     VTW(0, 2),
     VTW(0, 3),
     {TW_NEXT, VL, 0}
};

static const ct_desc desc = { 4, "t1buv_4", twinstr, &GENUS, {11, 6, 0, 0}, 0, 0, 0 };

void X(codelet_t1buv_4) (planner *p) {
     X(kdft_dit_register) (p, t1buv_4, &desc);
}
#endif				/* HAVE_FMA */
