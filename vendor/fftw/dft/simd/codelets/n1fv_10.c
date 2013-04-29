/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * See the file COPYING for license information.
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Mon Nov 10 20:33:31 EST 2008 */

#include "codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_notw_c -fma -reorder-insns -schedule-for-pipeline -simd -compact -variables 4 -pipeline-latency 8 -n 10 -name n1fv_10 -include n1f.h */

/*
 * This function contains 42 FP additions, 22 FP multiplications,
 * (or, 24 additions, 4 multiplications, 18 fused multiply/add),
 * 43 stack variables, 4 constants, and 20 memory accesses
 */
#include "n1f.h"

static void n1fv_10(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     DVK(KP559016994, +0.559016994374947424102293417182819058860154590);
     DVK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DVK(KP618033988, +0.618033988749894848204586834365638117720309180);
     DVK(KP951056516, +0.951056516295153572116439333379382143405698634);
     INT i;
     const R *xi;
     R *xo;
     xi = ri;
     xo = ro;
     for (i = v; i > 0; i = i - VL, xi = xi + (VL * ivs), xo = xo + (VL * ovs), MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  V Tb, Tr, T3, Ts, T6, Tw, Tg, Tt, T9, Tc, T1, T2;
	  T1 = LD(&(xi[0]), ivs, &(xi[0]));
	  T2 = LD(&(xi[WS(is, 5)]), ivs, &(xi[WS(is, 1)]));
	  {
	       V T4, T5, Te, Tf, T7, T8;
	       T4 = LD(&(xi[WS(is, 2)]), ivs, &(xi[0]));
	       T5 = LD(&(xi[WS(is, 7)]), ivs, &(xi[WS(is, 1)]));
	       Te = LD(&(xi[WS(is, 6)]), ivs, &(xi[0]));
	       Tf = LD(&(xi[WS(is, 1)]), ivs, &(xi[WS(is, 1)]));
	       T7 = LD(&(xi[WS(is, 8)]), ivs, &(xi[0]));
	       T8 = LD(&(xi[WS(is, 3)]), ivs, &(xi[WS(is, 1)]));
	       Tb = LD(&(xi[WS(is, 4)]), ivs, &(xi[0]));
	       Tr = VADD(T1, T2);
	       T3 = VSUB(T1, T2);
	       Ts = VADD(T4, T5);
	       T6 = VSUB(T4, T5);
	       Tw = VADD(Te, Tf);
	       Tg = VSUB(Te, Tf);
	       Tt = VADD(T7, T8);
	       T9 = VSUB(T7, T8);
	       Tc = LD(&(xi[WS(is, 9)]), ivs, &(xi[WS(is, 1)]));
	  }
	  {
	       V TD, Tu, Tm, Ta, Td, Tv;
	       TD = VSUB(Ts, Tt);
	       Tu = VADD(Ts, Tt);
	       Tm = VSUB(T6, T9);
	       Ta = VADD(T6, T9);
	       Td = VSUB(Tb, Tc);
	       Tv = VADD(Tb, Tc);
	       {
		    V TC, Tx, Tn, Th;
		    TC = VSUB(Tv, Tw);
		    Tx = VADD(Tv, Tw);
		    Tn = VSUB(Td, Tg);
		    Th = VADD(Td, Tg);
		    {
			 V Ty, TA, TE, TG, Ti, Tk, To, Tq, Tz, Tj;
			 Ty = VADD(Tu, Tx);
			 TA = VSUB(Tu, Tx);
			 TE = VMUL(LDK(KP951056516), VFNMS(LDK(KP618033988), TD, TC));
			 TG = VMUL(LDK(KP951056516), VFMA(LDK(KP618033988), TC, TD));
			 Ti = VADD(Ta, Th);
			 Tk = VSUB(Ta, Th);
			 To = VMUL(LDK(KP951056516), VFMA(LDK(KP618033988), Tn, Tm));
			 Tq = VMUL(LDK(KP951056516), VFNMS(LDK(KP618033988), Tm, Tn));
			 Tz = VFNMS(LDK(KP250000000), Ty, Tr);
			 ST(&(xo[0]), VADD(Tr, Ty), ovs, &(xo[0]));
			 Tj = VFNMS(LDK(KP250000000), Ti, T3);
			 ST(&(xo[WS(os, 5)]), VADD(T3, Ti), ovs, &(xo[WS(os, 1)]));
			 {
			      V TB, TF, Tl, Tp;
			      TB = VFNMS(LDK(KP559016994), TA, Tz);
			      TF = VFMA(LDK(KP559016994), TA, Tz);
			      Tl = VFMA(LDK(KP559016994), Tk, Tj);
			      Tp = VFNMS(LDK(KP559016994), Tk, Tj);
			      ST(&(xo[WS(os, 4)]), VFMAI(TG, TF), ovs, &(xo[0]));
			      ST(&(xo[WS(os, 6)]), VFNMSI(TG, TF), ovs, &(xo[0]));
			      ST(&(xo[WS(os, 8)]), VFNMSI(TE, TB), ovs, &(xo[0]));
			      ST(&(xo[WS(os, 2)]), VFMAI(TE, TB), ovs, &(xo[0]));
			      ST(&(xo[WS(os, 3)]), VFNMSI(Tq, Tp), ovs, &(xo[WS(os, 1)]));
			      ST(&(xo[WS(os, 7)]), VFMAI(Tq, Tp), ovs, &(xo[WS(os, 1)]));
			      ST(&(xo[WS(os, 9)]), VFMAI(To, Tl), ovs, &(xo[WS(os, 1)]));
			      ST(&(xo[WS(os, 1)]), VFNMSI(To, Tl), ovs, &(xo[WS(os, 1)]));
			 }
		    }
	       }
	  }
     }
}

static const kdft_desc desc = { 10, "n1fv_10", {24, 4, 18, 0}, &GENUS, 0, 0, 0, 0 };
void X(codelet_n1fv_10) (planner *p) {
     X(kdft_register) (p, n1fv_10, &desc);
}

#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_notw_c -simd -compact -variables 4 -pipeline-latency 8 -n 10 -name n1fv_10 -include n1f.h */

/*
 * This function contains 42 FP additions, 12 FP multiplications,
 * (or, 36 additions, 6 multiplications, 6 fused multiply/add),
 * 33 stack variables, 4 constants, and 20 memory accesses
 */
#include "n1f.h"

static void n1fv_10(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     DVK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DVK(KP559016994, +0.559016994374947424102293417182819058860154590);
     DVK(KP587785252, +0.587785252292473129168705954639072768597652438);
     DVK(KP951056516, +0.951056516295153572116439333379382143405698634);
     INT i;
     const R *xi;
     R *xo;
     xi = ri;
     xo = ro;
     for (i = v; i > 0; i = i - VL, xi = xi + (VL * ivs), xo = xo + (VL * ovs), MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  V Ti, Ty, Tm, Tn, Tw, Tt, Tz, TA, TB, T7, Te, Tj, Tg, Th;
	  Tg = LD(&(xi[0]), ivs, &(xi[0]));
	  Th = LD(&(xi[WS(is, 5)]), ivs, &(xi[WS(is, 1)]));
	  Ti = VSUB(Tg, Th);
	  Ty = VADD(Tg, Th);
	  {
	       V T3, Tu, Td, Ts, T6, Tv, Ta, Tr;
	       {
		    V T1, T2, Tb, Tc;
		    T1 = LD(&(xi[WS(is, 2)]), ivs, &(xi[0]));
		    T2 = LD(&(xi[WS(is, 7)]), ivs, &(xi[WS(is, 1)]));
		    T3 = VSUB(T1, T2);
		    Tu = VADD(T1, T2);
		    Tb = LD(&(xi[WS(is, 6)]), ivs, &(xi[0]));
		    Tc = LD(&(xi[WS(is, 1)]), ivs, &(xi[WS(is, 1)]));
		    Td = VSUB(Tb, Tc);
		    Ts = VADD(Tb, Tc);
	       }
	       {
		    V T4, T5, T8, T9;
		    T4 = LD(&(xi[WS(is, 8)]), ivs, &(xi[0]));
		    T5 = LD(&(xi[WS(is, 3)]), ivs, &(xi[WS(is, 1)]));
		    T6 = VSUB(T4, T5);
		    Tv = VADD(T4, T5);
		    T8 = LD(&(xi[WS(is, 4)]), ivs, &(xi[0]));
		    T9 = LD(&(xi[WS(is, 9)]), ivs, &(xi[WS(is, 1)]));
		    Ta = VSUB(T8, T9);
		    Tr = VADD(T8, T9);
	       }
	       Tm = VSUB(T3, T6);
	       Tn = VSUB(Ta, Td);
	       Tw = VSUB(Tu, Tv);
	       Tt = VSUB(Tr, Ts);
	       Tz = VADD(Tu, Tv);
	       TA = VADD(Tr, Ts);
	       TB = VADD(Tz, TA);
	       T7 = VADD(T3, T6);
	       Te = VADD(Ta, Td);
	       Tj = VADD(T7, Te);
	  }
	  ST(&(xo[WS(os, 5)]), VADD(Ti, Tj), ovs, &(xo[WS(os, 1)]));
	  ST(&(xo[0]), VADD(Ty, TB), ovs, &(xo[0]));
	  {
	       V To, Tq, Tl, Tp, Tf, Tk;
	       To = VBYI(VFMA(LDK(KP951056516), Tm, VMUL(LDK(KP587785252), Tn)));
	       Tq = VBYI(VFNMS(LDK(KP587785252), Tm, VMUL(LDK(KP951056516), Tn)));
	       Tf = VMUL(LDK(KP559016994), VSUB(T7, Te));
	       Tk = VFNMS(LDK(KP250000000), Tj, Ti);
	       Tl = VADD(Tf, Tk);
	       Tp = VSUB(Tk, Tf);
	       ST(&(xo[WS(os, 1)]), VSUB(Tl, To), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 7)]), VADD(Tq, Tp), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 9)]), VADD(To, Tl), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 3)]), VSUB(Tp, Tq), ovs, &(xo[WS(os, 1)]));
	  }
	  {
	       V Tx, TF, TE, TG, TC, TD;
	       Tx = VBYI(VFNMS(LDK(KP587785252), Tw, VMUL(LDK(KP951056516), Tt)));
	       TF = VBYI(VFMA(LDK(KP951056516), Tw, VMUL(LDK(KP587785252), Tt)));
	       TC = VFNMS(LDK(KP250000000), TB, Ty);
	       TD = VMUL(LDK(KP559016994), VSUB(Tz, TA));
	       TE = VSUB(TC, TD);
	       TG = VADD(TD, TC);
	       ST(&(xo[WS(os, 2)]), VADD(Tx, TE), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 6)]), VSUB(TG, TF), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 8)]), VSUB(TE, Tx), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 4)]), VADD(TF, TG), ovs, &(xo[0]));
	  }
     }
}

static const kdft_desc desc = { 10, "n1fv_10", {36, 6, 6, 0}, &GENUS, 0, 0, 0, 0 };
void X(codelet_n1fv_10) (planner *p) {
     X(kdft_register) (p, n1fv_10, &desc);
}

#endif				/* HAVE_FMA */
