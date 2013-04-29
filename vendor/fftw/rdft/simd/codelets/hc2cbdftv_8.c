/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * See the file COPYING for license information.
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Mon Nov 10 21:03:19 EST 2008 */

#include "codelet-rdft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_hc2cdft_c -fma -reorder-insns -schedule-for-pipeline -simd -compact -variables 4 -pipeline-latency 8 -trivial-stores -variables 32 -no-generate-bytw -n 8 -dif -sign 1 -name hc2cbdftv_8 -include hc2cbv.h */

/*
 * This function contains 41 FP additions, 32 FP multiplications,
 * (or, 23 additions, 14 multiplications, 18 fused multiply/add),
 * 51 stack variables, 1 constants, and 16 memory accesses
 */
#include "hc2cbv.h"

static void hc2cbdftv_8(R *Rp, R *Ip, R *Rm, R *Im, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DVK(KP707106781, +0.707106781186547524400844362104849039284835938);
     INT m;
     for (m = mb, W = W + ((mb - 1) * ((TWVL / VL) * 14)); m < me; m = m + VL, Rp = Rp + (VL * ms), Ip = Ip + (VL * ms), Rm = Rm - (VL * ms), Im = Im - (VL * ms), W = W + (TWVL * 14), MAKE_VOLATILE_STRIDE(rs)) {
	  V TJ, T4, Tf, TB, TD, TE, Tm, T1, Tj, TF, Tp, Tb, Tg, Tt, Tx;
	  V T2, T3, Td, Te, T5, T6, T8, T9, Tn, T7, To, Ta, Tk, Tl, TG;
	  V TL, Tq, Tc, Tu, Th, Tv, Ty, Tw, TC, Ti, TK, TA, Tz, TI, TH;
	  V Ts, Tr, TN, TM;
	  T2 = LD(&(Rp[0]), ms, &(Rp[0]));
	  T3 = LD(&(Rm[WS(rs, 3)]), -ms, &(Rm[WS(rs, 1)]));
	  Td = LD(&(Rp[WS(rs, 2)]), ms, &(Rp[0]));
	  Te = LD(&(Rm[WS(rs, 1)]), -ms, &(Rm[WS(rs, 1)]));
	  T5 = LD(&(Rp[WS(rs, 1)]), ms, &(Rp[WS(rs, 1)]));
	  T6 = LD(&(Rm[WS(rs, 2)]), -ms, &(Rm[0]));
	  T8 = LD(&(Rp[WS(rs, 3)]), ms, &(Rp[WS(rs, 1)]));
	  T9 = LD(&(Rm[0]), -ms, &(Rm[0]));
	  TJ = LDW(&(W[0]));
	  Tk = VFMACONJ(T3, T2);
	  T4 = VFNMSCONJ(T3, T2);
	  Tl = VFMACONJ(Te, Td);
	  Tf = VFNMSCONJ(Te, Td);
	  Tn = VFMACONJ(T6, T5);
	  T7 = VFNMSCONJ(T6, T5);
	  To = VFMACONJ(T9, T8);
	  Ta = VFMSCONJ(T9, T8);
	  TB = LDW(&(W[TWVL * 8]));
	  TD = LDW(&(W[TWVL * 6]));
	  TE = VADD(Tk, Tl);
	  Tm = VSUB(Tk, Tl);
	  T1 = LDW(&(W[TWVL * 12]));
	  Tj = LDW(&(W[TWVL * 10]));
	  TF = VADD(Tn, To);
	  Tp = VSUB(Tn, To);
	  Tb = VADD(T7, Ta);
	  Tg = VSUB(T7, Ta);
	  Tt = LDW(&(W[TWVL * 4]));
	  Tx = LDW(&(W[TWVL * 2]));
	  TG = VZMUL(TD, VSUB(TE, TF));
	  TL = VADD(TE, TF);
	  Tq = VZMUL(Tj, VFNMSI(Tp, Tm));
	  Tc = VFMA(LDK(KP707106781), Tb, T4);
	  Tu = VFNMS(LDK(KP707106781), Tb, T4);
	  Th = VFMA(LDK(KP707106781), Tg, Tf);
	  Tv = VFNMS(LDK(KP707106781), Tg, Tf);
	  Ty = VZMUL(Tx, VFMAI(Tp, Tm));
	  Tw = VZMULI(Tt, VFNMSI(Tv, Tu));
	  TC = VZMULI(TB, VFMAI(Tv, Tu));
	  Ti = VZMULI(T1, VFNMSI(Th, Tc));
	  TK = VZMULI(TJ, VFMAI(Th, Tc));
	  TA = VCONJ(VSUB(Ty, Tw));
	  Tz = VADD(Tw, Ty);
	  TI = VCONJ(VSUB(TG, TC));
	  TH = VADD(TC, TG);
	  Ts = VCONJ(VSUB(Tq, Ti));
	  Tr = VADD(Ti, Tq);
	  TN = VCONJ(VSUB(TL, TK));
	  TM = VADD(TK, TL);
	  ST(&(Rm[WS(rs, 1)]), TA, -ms, &(Rm[WS(rs, 1)]));
	  ST(&(Rp[WS(rs, 1)]), Tz, ms, &(Rp[WS(rs, 1)]));
	  ST(&(Rm[WS(rs, 2)]), TI, -ms, &(Rm[0]));
	  ST(&(Rp[WS(rs, 2)]), TH, ms, &(Rp[0]));
	  ST(&(Rm[WS(rs, 3)]), Ts, -ms, &(Rm[WS(rs, 1)]));
	  ST(&(Rp[WS(rs, 3)]), Tr, ms, &(Rp[WS(rs, 1)]));
	  ST(&(Rm[0]), TN, -ms, &(Rm[0]));
	  ST(&(Rp[0]), TM, ms, &(Rp[0]));
     }
}

static const tw_instr twinstr[] = {
     VTW(1, 1),
     VTW(1, 2),
     VTW(1, 3),
     VTW(1, 4),
     VTW(1, 5),
     VTW(1, 6),
     VTW(1, 7),
     {TW_NEXT, VL, 0}
};

static const hc2c_desc desc = { 8, "hc2cbdftv_8", twinstr, &GENUS, {23, 14, 18, 0} };

void X(codelet_hc2cbdftv_8) (planner *p) {
     X(khc2c_register) (p, hc2cbdftv_8, &desc, HC2C_VIA_DFT);
}
#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_hc2cdft_c -simd -compact -variables 4 -pipeline-latency 8 -trivial-stores -variables 32 -no-generate-bytw -n 8 -dif -sign 1 -name hc2cbdftv_8 -include hc2cbv.h */

/*
 * This function contains 41 FP additions, 16 FP multiplications,
 * (or, 41 additions, 16 multiplications, 0 fused multiply/add),
 * 55 stack variables, 1 constants, and 16 memory accesses
 */
#include "hc2cbv.h"

static void hc2cbdftv_8(R *Rp, R *Ip, R *Rm, R *Im, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DVK(KP707106781, +0.707106781186547524400844362104849039284835938);
     INT m;
     for (m = mb, W = W + ((mb - 1) * ((TWVL / VL) * 14)); m < me; m = m + VL, Rp = Rp + (VL * ms), Ip = Ip + (VL * ms), Rm = Rm - (VL * ms), Im = Im - (VL * ms), W = W + (TWVL * 14), MAKE_VOLATILE_STRIDE(rs)) {
	  V T5, Tj, Tq, TI, Te, Tk, Tt, TJ, T2, Tg, T4, Ti, T3, Th, To;
	  V Tp, T6, Tc, T8, Tb, T7, Ta, T9, Td, Tr, Ts, TP, Tu, Tm, TO;
	  V Tn, Tf, Tl, T1, TN, Tv, TR, Tw, TQ, TC, TK, TA, TG, TB, TH;
	  V Ty, Tz, Tx, TF, TD, TM, TE, TL;
	  T2 = LD(&(Rp[0]), ms, &(Rp[0]));
	  Tg = LD(&(Rp[WS(rs, 2)]), ms, &(Rp[0]));
	  T3 = LD(&(Rm[WS(rs, 3)]), -ms, &(Rm[WS(rs, 1)]));
	  T4 = VCONJ(T3);
	  Th = LD(&(Rm[WS(rs, 1)]), -ms, &(Rm[WS(rs, 1)]));
	  Ti = VCONJ(Th);
	  T5 = VSUB(T2, T4);
	  Tj = VSUB(Tg, Ti);
	  To = VADD(T2, T4);
	  Tp = VADD(Tg, Ti);
	  Tq = VSUB(To, Tp);
	  TI = VADD(To, Tp);
	  T6 = LD(&(Rp[WS(rs, 1)]), ms, &(Rp[WS(rs, 1)]));
	  Tc = LD(&(Rp[WS(rs, 3)]), ms, &(Rp[WS(rs, 1)]));
	  T7 = LD(&(Rm[WS(rs, 2)]), -ms, &(Rm[0]));
	  T8 = VCONJ(T7);
	  Ta = LD(&(Rm[0]), -ms, &(Rm[0]));
	  Tb = VCONJ(Ta);
	  T9 = VSUB(T6, T8);
	  Td = VSUB(Tb, Tc);
	  Te = VMUL(LDK(KP707106781), VADD(T9, Td));
	  Tk = VMUL(LDK(KP707106781), VSUB(T9, Td));
	  Tr = VADD(T6, T8);
	  Ts = VADD(Tb, Tc);
	  Tt = VBYI(VSUB(Tr, Ts));
	  TJ = VADD(Tr, Ts);
	  TP = VADD(TI, TJ);
	  Tn = LDW(&(W[TWVL * 10]));
	  Tu = VZMUL(Tn, VSUB(Tq, Tt));
	  Tf = VADD(T5, Te);
	  Tl = VBYI(VADD(Tj, Tk));
	  T1 = LDW(&(W[TWVL * 12]));
	  Tm = VZMULI(T1, VSUB(Tf, Tl));
	  TN = LDW(&(W[0]));
	  TO = VZMULI(TN, VADD(Tl, Tf));
	  Tv = VADD(Tm, Tu);
	  ST(&(Rp[WS(rs, 3)]), Tv, ms, &(Rp[WS(rs, 1)]));
	  TR = VCONJ(VSUB(TP, TO));
	  ST(&(Rm[0]), TR, -ms, &(Rm[0]));
	  Tw = VCONJ(VSUB(Tu, Tm));
	  ST(&(Rm[WS(rs, 3)]), Tw, -ms, &(Rm[WS(rs, 1)]));
	  TQ = VADD(TO, TP);
	  ST(&(Rp[0]), TQ, ms, &(Rp[0]));
	  TB = LDW(&(W[TWVL * 2]));
	  TC = VZMUL(TB, VADD(Tq, Tt));
	  TH = LDW(&(W[TWVL * 6]));
	  TK = VZMUL(TH, VSUB(TI, TJ));
	  Ty = VBYI(VSUB(Tk, Tj));
	  Tz = VSUB(T5, Te);
	  Tx = LDW(&(W[TWVL * 4]));
	  TA = VZMULI(Tx, VADD(Ty, Tz));
	  TF = LDW(&(W[TWVL * 8]));
	  TG = VZMULI(TF, VSUB(Tz, Ty));
	  TD = VADD(TA, TC);
	  ST(&(Rp[WS(rs, 1)]), TD, ms, &(Rp[WS(rs, 1)]));
	  TM = VCONJ(VSUB(TK, TG));
	  ST(&(Rm[WS(rs, 2)]), TM, -ms, &(Rm[0]));
	  TE = VCONJ(VSUB(TC, TA));
	  ST(&(Rm[WS(rs, 1)]), TE, -ms, &(Rm[WS(rs, 1)]));
	  TL = VADD(TG, TK);
	  ST(&(Rp[WS(rs, 2)]), TL, ms, &(Rp[0]));
     }
}

static const tw_instr twinstr[] = {
     VTW(1, 1),
     VTW(1, 2),
     VTW(1, 3),
     VTW(1, 4),
     VTW(1, 5),
     VTW(1, 6),
     VTW(1, 7),
     {TW_NEXT, VL, 0}
};

static const hc2c_desc desc = { 8, "hc2cbdftv_8", twinstr, &GENUS, {41, 16, 0, 0} };

void X(codelet_hc2cbdftv_8) (planner *p) {
     X(khc2c_register) (p, hc2cbdftv_8, &desc, HC2C_VIA_DFT);
}
#endif				/* HAVE_FMA */
