/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * See the file COPYING for license information.
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Mon Nov 10 20:34:59 EST 2008 */

#include "codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_notw_c -fma -reorder-insns -schedule-for-pipeline -simd -compact -variables 4 -pipeline-latency 8 -n 16 -name n2fv_16 -with-ostride 2 -include n2f.h -store-multiple 2 */

/*
 * This function contains 72 FP additions, 34 FP multiplications,
 * (or, 38 additions, 0 multiplications, 34 fused multiply/add),
 * 62 stack variables, 3 constants, and 40 memory accesses
 */
#include "n2f.h"

static void n2fv_16(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     DVK(KP923879532, +0.923879532511286756128183189396788286822416626);
     DVK(KP414213562, +0.414213562373095048801688724209698078569671875);
     DVK(KP707106781, +0.707106781186547524400844362104849039284835938);
     INT i;
     const R *xi;
     R *xo;
     xi = ri;
     xo = ro;
     for (i = v; i > 0; i = i - VL, xi = xi + (VL * ivs), xo = xo + (VL * ovs), MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  V T7, Tu, TF, TB, T13, TL, TO, TX, TC, Te, TP, Th, TQ, Tk, TW;
	  V T16;
	  {
	       V TH, TU, Tz, Tf, TK, TV, TA, TM, Ta, TN, Td, Tg, Ti, Tj;
	       {
		    V T1, T2, T4, T5, To, Tp, Tr, Ts;
		    T1 = LD(&(xi[0]), ivs, &(xi[0]));
		    T2 = LD(&(xi[WS(is, 8)]), ivs, &(xi[0]));
		    T4 = LD(&(xi[WS(is, 4)]), ivs, &(xi[0]));
		    T5 = LD(&(xi[WS(is, 12)]), ivs, &(xi[0]));
		    To = LD(&(xi[WS(is, 14)]), ivs, &(xi[0]));
		    Tp = LD(&(xi[WS(is, 6)]), ivs, &(xi[0]));
		    Tr = LD(&(xi[WS(is, 2)]), ivs, &(xi[0]));
		    Ts = LD(&(xi[WS(is, 10)]), ivs, &(xi[0]));
		    {
			 V T8, TJ, Tq, TI, Tt, T9, Tb, Tc, T3, T6;
			 T8 = LD(&(xi[WS(is, 1)]), ivs, &(xi[WS(is, 1)]));
			 TH = VSUB(T1, T2);
			 T3 = VADD(T1, T2);
			 TU = VSUB(T4, T5);
			 T6 = VADD(T4, T5);
			 TJ = VSUB(To, Tp);
			 Tq = VADD(To, Tp);
			 TI = VSUB(Tr, Ts);
			 Tt = VADD(Tr, Ts);
			 T9 = LD(&(xi[WS(is, 9)]), ivs, &(xi[WS(is, 1)]));
			 Tb = LD(&(xi[WS(is, 5)]), ivs, &(xi[WS(is, 1)]));
			 Tc = LD(&(xi[WS(is, 13)]), ivs, &(xi[WS(is, 1)]));
			 T7 = VSUB(T3, T6);
			 Tz = VADD(T3, T6);
			 Tf = LD(&(xi[WS(is, 15)]), ivs, &(xi[WS(is, 1)]));
			 TK = VADD(TI, TJ);
			 TV = VSUB(TJ, TI);
			 TA = VADD(Tt, Tq);
			 Tu = VSUB(Tq, Tt);
			 TM = VSUB(T8, T9);
			 Ta = VADD(T8, T9);
			 TN = VSUB(Tb, Tc);
			 Td = VADD(Tb, Tc);
			 Tg = LD(&(xi[WS(is, 7)]), ivs, &(xi[WS(is, 1)]));
			 Ti = LD(&(xi[WS(is, 3)]), ivs, &(xi[WS(is, 1)]));
			 Tj = LD(&(xi[WS(is, 11)]), ivs, &(xi[WS(is, 1)]));
		    }
	       }
	       TF = VSUB(Tz, TA);
	       TB = VADD(Tz, TA);
	       T13 = VFNMS(LDK(KP707106781), TK, TH);
	       TL = VFMA(LDK(KP707106781), TK, TH);
	       TO = VFNMS(LDK(KP414213562), TN, TM);
	       TX = VFMA(LDK(KP414213562), TM, TN);
	       TC = VADD(Ta, Td);
	       Te = VSUB(Ta, Td);
	       TP = VSUB(Tf, Tg);
	       Th = VADD(Tf, Tg);
	       TQ = VSUB(Tj, Ti);
	       Tk = VADD(Ti, Tj);
	       TW = VFNMS(LDK(KP707106781), TV, TU);
	       T16 = VFMA(LDK(KP707106781), TV, TU);
	  }
	  {
	       V TY, TR, Tl, TD;
	       TY = VFMA(LDK(KP414213562), TP, TQ);
	       TR = VFNMS(LDK(KP414213562), TQ, TP);
	       Tl = VSUB(Th, Tk);
	       TD = VADD(Th, Tk);
	       {
		    V TS, T17, TZ, T14;
		    TS = VADD(TO, TR);
		    T17 = VSUB(TR, TO);
		    TZ = VSUB(TX, TY);
		    T14 = VADD(TX, TY);
		    {
			 V TE, TG, Tm, Tv;
			 TE = VADD(TC, TD);
			 TG = VSUB(TD, TC);
			 Tm = VADD(Te, Tl);
			 Tv = VSUB(Tl, Te);
			 {
			      V T18, T1a, TT, T11;
			      T18 = VFNMS(LDK(KP923879532), T17, T16);
			      T1a = VFMA(LDK(KP923879532), T17, T16);
			      TT = VFNMS(LDK(KP923879532), TS, TL);
			      T11 = VFMA(LDK(KP923879532), TS, TL);
			      {
				   V T15, T19, T10, T12;
				   T15 = VFNMS(LDK(KP923879532), T14, T13);
				   T19 = VFMA(LDK(KP923879532), T14, T13);
				   T10 = VFNMS(LDK(KP923879532), TZ, TW);
				   T12 = VFMA(LDK(KP923879532), TZ, TW);
				   {
					V T1b, T1c, T1d, T1e;
					T1b = VFMAI(TG, TF);
					STM2(&(xo[8]), T1b, ovs, &(xo[0]));
					T1c = VFNMSI(TG, TF);
					STM2(&(xo[24]), T1c, ovs, &(xo[0]));
					T1d = VADD(TB, TE);
					STM2(&(xo[0]), T1d, ovs, &(xo[0]));
					T1e = VSUB(TB, TE);
					STM2(&(xo[16]), T1e, ovs, &(xo[0]));
					{
					     V Tw, Ty, Tn, Tx;
					     Tw = VFNMS(LDK(KP707106781), Tv, Tu);
					     Ty = VFMA(LDK(KP707106781), Tv, Tu);
					     Tn = VFNMS(LDK(KP707106781), Tm, T7);
					     Tx = VFMA(LDK(KP707106781), Tm, T7);
					     {
						  V T1f, T1g, T1h, T1i;
						  T1f = VFMAI(T1a, T19);
						  STM2(&(xo[6]), T1f, ovs, &(xo[2]));
						  T1g = VFNMSI(T1a, T19);
						  STM2(&(xo[26]), T1g, ovs, &(xo[2]));
						  STN2(&(xo[24]), T1c, T1g, ovs);
						  T1h = VFMAI(T18, T15);
						  STM2(&(xo[22]), T1h, ovs, &(xo[2]));
						  T1i = VFNMSI(T18, T15);
						  STM2(&(xo[10]), T1i, ovs, &(xo[2]));
						  STN2(&(xo[8]), T1b, T1i, ovs);
						  {
						       V T1j, T1k, T1l, T1m;
						       T1j = VFNMSI(T12, T11);
						       STM2(&(xo[2]), T1j, ovs, &(xo[2]));
						       STN2(&(xo[0]), T1d, T1j, ovs);
						       T1k = VFMAI(T12, T11);
						       STM2(&(xo[30]), T1k, ovs, &(xo[2]));
						       T1l = VFMAI(T10, TT);
						       STM2(&(xo[14]), T1l, ovs, &(xo[2]));
						       T1m = VFNMSI(T10, TT);
						       STM2(&(xo[18]), T1m, ovs, &(xo[2]));
						       STN2(&(xo[16]), T1e, T1m, ovs);
						       {
							    V T1n, T1o, T1p, T1q;
							    T1n = VFNMSI(Ty, Tx);
							    STM2(&(xo[28]), T1n, ovs, &(xo[0]));
							    STN2(&(xo[28]), T1n, T1k, ovs);
							    T1o = VFMAI(Ty, Tx);
							    STM2(&(xo[4]), T1o, ovs, &(xo[0]));
							    STN2(&(xo[4]), T1o, T1f, ovs);
							    T1p = VFMAI(Tw, Tn);
							    STM2(&(xo[20]), T1p, ovs, &(xo[0]));
							    STN2(&(xo[20]), T1p, T1h, ovs);
							    T1q = VFNMSI(Tw, Tn);
							    STM2(&(xo[12]), T1q, ovs, &(xo[0]));
							    STN2(&(xo[12]), T1q, T1l, ovs);
						       }
						  }
					     }
					}
				   }
			      }
			 }
		    }
	       }
	  }
     }
}

static const kdft_desc desc = { 16, "n2fv_16", {38, 0, 34, 0}, &GENUS, 0, 2, 0, 0 };
void X(codelet_n2fv_16) (planner *p) {
     X(kdft_register) (p, n2fv_16, &desc);
}

#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_notw_c -simd -compact -variables 4 -pipeline-latency 8 -n 16 -name n2fv_16 -with-ostride 2 -include n2f.h -store-multiple 2 */

/*
 * This function contains 72 FP additions, 12 FP multiplications,
 * (or, 68 additions, 8 multiplications, 4 fused multiply/add),
 * 38 stack variables, 3 constants, and 40 memory accesses
 */
#include "n2f.h"

static void n2fv_16(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     DVK(KP923879532, +0.923879532511286756128183189396788286822416626);
     DVK(KP382683432, +0.382683432365089771728459984030398866761344562);
     DVK(KP707106781, +0.707106781186547524400844362104849039284835938);
     INT i;
     const R *xi;
     R *xo;
     xi = ri;
     xo = ro;
     for (i = v; i > 0; i = i - VL, xi = xi + (VL * ivs), xo = xo + (VL * ovs), MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  V Tp, T13, Tu, TN, Tm, T14, Tv, TY, T7, T17, Ty, TT, Te, T16, Tx;
	  V TQ;
	  {
	       V Tn, To, TM, Ts, Tt, TL;
	       Tn = LD(&(xi[WS(is, 4)]), ivs, &(xi[0]));
	       To = LD(&(xi[WS(is, 12)]), ivs, &(xi[0]));
	       TM = VADD(Tn, To);
	       Ts = LD(&(xi[0]), ivs, &(xi[0]));
	       Tt = LD(&(xi[WS(is, 8)]), ivs, &(xi[0]));
	       TL = VADD(Ts, Tt);
	       Tp = VSUB(Tn, To);
	       T13 = VADD(TL, TM);
	       Tu = VSUB(Ts, Tt);
	       TN = VSUB(TL, TM);
	  }
	  {
	       V Ti, TW, Tl, TX;
	       {
		    V Tg, Th, Tj, Tk;
		    Tg = LD(&(xi[WS(is, 14)]), ivs, &(xi[0]));
		    Th = LD(&(xi[WS(is, 6)]), ivs, &(xi[0]));
		    Ti = VSUB(Tg, Th);
		    TW = VADD(Tg, Th);
		    Tj = LD(&(xi[WS(is, 2)]), ivs, &(xi[0]));
		    Tk = LD(&(xi[WS(is, 10)]), ivs, &(xi[0]));
		    Tl = VSUB(Tj, Tk);
		    TX = VADD(Tj, Tk);
	       }
	       Tm = VMUL(LDK(KP707106781), VSUB(Ti, Tl));
	       T14 = VADD(TX, TW);
	       Tv = VMUL(LDK(KP707106781), VADD(Tl, Ti));
	       TY = VSUB(TW, TX);
	  }
	  {
	       V T3, TR, T6, TS;
	       {
		    V T1, T2, T4, T5;
		    T1 = LD(&(xi[WS(is, 15)]), ivs, &(xi[WS(is, 1)]));
		    T2 = LD(&(xi[WS(is, 7)]), ivs, &(xi[WS(is, 1)]));
		    T3 = VSUB(T1, T2);
		    TR = VADD(T1, T2);
		    T4 = LD(&(xi[WS(is, 3)]), ivs, &(xi[WS(is, 1)]));
		    T5 = LD(&(xi[WS(is, 11)]), ivs, &(xi[WS(is, 1)]));
		    T6 = VSUB(T4, T5);
		    TS = VADD(T4, T5);
	       }
	       T7 = VFNMS(LDK(KP923879532), T6, VMUL(LDK(KP382683432), T3));
	       T17 = VADD(TR, TS);
	       Ty = VFMA(LDK(KP923879532), T3, VMUL(LDK(KP382683432), T6));
	       TT = VSUB(TR, TS);
	  }
	  {
	       V Ta, TO, Td, TP;
	       {
		    V T8, T9, Tb, Tc;
		    T8 = LD(&(xi[WS(is, 1)]), ivs, &(xi[WS(is, 1)]));
		    T9 = LD(&(xi[WS(is, 9)]), ivs, &(xi[WS(is, 1)]));
		    Ta = VSUB(T8, T9);
		    TO = VADD(T8, T9);
		    Tb = LD(&(xi[WS(is, 5)]), ivs, &(xi[WS(is, 1)]));
		    Tc = LD(&(xi[WS(is, 13)]), ivs, &(xi[WS(is, 1)]));
		    Td = VSUB(Tb, Tc);
		    TP = VADD(Tb, Tc);
	       }
	       Te = VFMA(LDK(KP382683432), Ta, VMUL(LDK(KP923879532), Td));
	       T16 = VADD(TO, TP);
	       Tx = VFNMS(LDK(KP382683432), Td, VMUL(LDK(KP923879532), Ta));
	       TQ = VSUB(TO, TP);
	  }
	  {
	       V T1b, T1c, T1d, T1e;
	       {
		    V T15, T18, T19, T1a;
		    T15 = VADD(T13, T14);
		    T18 = VADD(T16, T17);
		    T1b = VSUB(T15, T18);
		    STM2(&(xo[16]), T1b, ovs, &(xo[0]));
		    T1c = VADD(T15, T18);
		    STM2(&(xo[0]), T1c, ovs, &(xo[0]));
		    T19 = VSUB(T13, T14);
		    T1a = VBYI(VSUB(T17, T16));
		    T1d = VSUB(T19, T1a);
		    STM2(&(xo[24]), T1d, ovs, &(xo[0]));
		    T1e = VADD(T19, T1a);
		    STM2(&(xo[8]), T1e, ovs, &(xo[0]));
	       }
	       {
		    V T1f, T1g, T1h, T1i;
		    {
			 V TV, T11, T10, T12, TU, TZ;
			 TU = VMUL(LDK(KP707106781), VADD(TQ, TT));
			 TV = VADD(TN, TU);
			 T11 = VSUB(TN, TU);
			 TZ = VMUL(LDK(KP707106781), VSUB(TT, TQ));
			 T10 = VBYI(VADD(TY, TZ));
			 T12 = VBYI(VSUB(TZ, TY));
			 T1f = VSUB(TV, T10);
			 STM2(&(xo[28]), T1f, ovs, &(xo[0]));
			 T1g = VADD(T11, T12);
			 STM2(&(xo[12]), T1g, ovs, &(xo[0]));
			 T1h = VADD(TV, T10);
			 STM2(&(xo[4]), T1h, ovs, &(xo[0]));
			 T1i = VSUB(T11, T12);
			 STM2(&(xo[20]), T1i, ovs, &(xo[0]));
		    }
		    {
			 V Tr, TB, TA, TC;
			 {
			      V Tf, Tq, Tw, Tz;
			      Tf = VSUB(T7, Te);
			      Tq = VSUB(Tm, Tp);
			      Tr = VBYI(VSUB(Tf, Tq));
			      TB = VBYI(VADD(Tq, Tf));
			      Tw = VADD(Tu, Tv);
			      Tz = VADD(Tx, Ty);
			      TA = VSUB(Tw, Tz);
			      TC = VADD(Tw, Tz);
			 }
			 {
			      V T1j, T1k, T1l, T1m;
			      T1j = VADD(Tr, TA);
			      STM2(&(xo[14]), T1j, ovs, &(xo[2]));
			      STN2(&(xo[12]), T1g, T1j, ovs);
			      T1k = VSUB(TC, TB);
			      STM2(&(xo[30]), T1k, ovs, &(xo[2]));
			      STN2(&(xo[28]), T1f, T1k, ovs);
			      T1l = VSUB(TA, Tr);
			      STM2(&(xo[18]), T1l, ovs, &(xo[2]));
			      STN2(&(xo[16]), T1b, T1l, ovs);
			      T1m = VADD(TB, TC);
			      STM2(&(xo[2]), T1m, ovs, &(xo[2]));
			      STN2(&(xo[0]), T1c, T1m, ovs);
			 }
		    }
		    {
			 V TF, TJ, TI, TK;
			 {
			      V TD, TE, TG, TH;
			      TD = VSUB(Tu, Tv);
			      TE = VADD(Te, T7);
			      TF = VADD(TD, TE);
			      TJ = VSUB(TD, TE);
			      TG = VADD(Tp, Tm);
			      TH = VSUB(Ty, Tx);
			      TI = VBYI(VADD(TG, TH));
			      TK = VBYI(VSUB(TH, TG));
			 }
			 {
			      V T1n, T1o, T1p, T1q;
			      T1n = VSUB(TF, TI);
			      STM2(&(xo[26]), T1n, ovs, &(xo[2]));
			      STN2(&(xo[24]), T1d, T1n, ovs);
			      T1o = VADD(TJ, TK);
			      STM2(&(xo[10]), T1o, ovs, &(xo[2]));
			      STN2(&(xo[8]), T1e, T1o, ovs);
			      T1p = VADD(TF, TI);
			      STM2(&(xo[6]), T1p, ovs, &(xo[2]));
			      STN2(&(xo[4]), T1h, T1p, ovs);
			      T1q = VSUB(TJ, TK);
			      STM2(&(xo[22]), T1q, ovs, &(xo[2]));
			      STN2(&(xo[20]), T1i, T1q, ovs);
			 }
		    }
	       }
	  }
     }
}

static const kdft_desc desc = { 16, "n2fv_16", {68, 8, 4, 0}, &GENUS, 0, 2, 0, 0 };
void X(codelet_n2fv_16) (planner *p) {
     X(kdft_register) (p, n2fv_16, &desc);
}

#endif				/* HAVE_FMA */
