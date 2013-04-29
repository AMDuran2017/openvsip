/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * See the file COPYING for license information.
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Mon Nov 10 20:26:05 EST 2008 */

#include "codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_notw -fma -reorder-insns -schedule-for-pipeline -compact -variables 4 -pipeline-latency 4 -n 11 -name n1_11 -include n.h */

/*
 * This function contains 140 FP additions, 110 FP multiplications,
 * (or, 30 additions, 0 multiplications, 110 fused multiply/add),
 * 84 stack variables, 10 constants, and 44 memory accesses
 */
#include "n.h"

static void n1_11(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     DK(KP989821441, +0.989821441880932732376092037776718787376519372);
     DK(KP959492973, +0.959492973614497389890368057066327699062454848);
     DK(KP918985947, +0.918985947228994779780736114132655398124909697);
     DK(KP876768831, +0.876768831002589333891339807079336796764054852);
     DK(KP830830026, +0.830830026003772851058548298459246407048009821);
     DK(KP778434453, +0.778434453334651800608337670740821884709317477);
     DK(KP715370323, +0.715370323453429719112414662767260662417897278);
     DK(KP634356270, +0.634356270682424498893150776899916060542806975);
     DK(KP342584725, +0.342584725681637509502641509861112333758894680);
     DK(KP521108558, +0.521108558113202722944698153526659300680427422);
     INT i;
     for (i = v; i > 0; i = i - 1, ri = ri + ivs, ii = ii + ivs, ro = ro + ovs, io = io + ovs, MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  E T1, TA, T1p, T1y, T19, T1d, T1a, T1e;
	  {
	       E T1f, T1u, T4, T1q, Tg, T1t, T7, T1s, Ta, Td, T1r, TP, T1X, T26, Ti;
	       E TG, T1O, T1w, TY, T1F, T17, To, T1i, T1k, T1h, Tr, T1j, Tu, T1g, Tx;
	       E T21, TU, TL, TC, T1S, T1J, T1m, T12, T1z, T1b;
	       T1 = ri[0];
	       T1f = ii[0];
	       {
		    E T1E, T16, Tb, Tc, Tv, Tw;
		    {
			 E T2, T3, Te, Tf;
			 T2 = ri[WS(is, 1)];
			 T3 = ri[WS(is, 10)];
			 Te = ri[WS(is, 5)];
			 Tf = ri[WS(is, 6)];
			 {
			      E T5, T6, T8, T9;
			      T5 = ri[WS(is, 2)];
			      T1u = T3 - T2;
			      T4 = T2 + T3;
			      T1q = Tf - Te;
			      Tg = Te + Tf;
			      T6 = ri[WS(is, 9)];
			      T8 = ri[WS(is, 3)];
			      T9 = ri[WS(is, 8)];
			      Tb = ri[WS(is, 4)];
			      T1t = T6 - T5;
			      T7 = T5 + T6;
			      T1s = T9 - T8;
			      Ta = T8 + T9;
			      Tc = ri[WS(is, 7)];
			 }
		    }
		    {
			 E T25, Th, T1W, TO;
			 T25 = FMA(KP521108558, T1q, T1u);
			 T1W = FMA(KP521108558, T1s, T1q);
			 TO = FNMS(KP342584725, T4, Ta);
			 Th = FNMS(KP342584725, Ta, T7);
			 Td = Tb + Tc;
			 T1r = Tc - Tb;
			 TP = FNMS(KP634356270, TO, Tg);
			 T1X = FNMS(KP715370323, T1W, T1t);
			 T26 = FMA(KP715370323, T25, T1r);
			 {
			      E TF, T1N, T1v, TX;
			      TF = FNMS(KP342584725, Td, T4);
			      Ti = FNMS(KP634356270, Th, Td);
			      T1N = FNMS(KP521108558, T1t, T1r);
			      T1v = FNMS(KP521108558, T1u, T1t);
			      TG = FNMS(KP634356270, TF, T7);
			      TX = FNMS(KP342584725, T7, Tg);
			      T1O = FMA(KP715370323, T1N, T1q);
			      T1w = FNMS(KP715370323, T1v, T1s);
			      T1E = FMA(KP521108558, T1r, T1s);
			      TY = FNMS(KP634356270, TX, T4);
			      T16 = FNMS(KP342584725, Tg, Td);
			 }
		    }
		    {
			 E Ty, Tz, Tm, Tn;
			 Tm = ii[WS(is, 3)];
			 T1F = FMA(KP715370323, T1E, T1u);
			 Tn = ii[WS(is, 8)];
			 T17 = FNMS(KP634356270, T16, Ta);
			 Ty = ii[WS(is, 5)];
			 Tz = ii[WS(is, 6)];
			 To = Tm - Tn;
			 T1i = Tm + Tn;
			 {
			      E Tp, Tq, Ts, Tt;
			      Tp = ii[WS(is, 2)];
			      T1k = Ty + Tz;
			      TA = Ty - Tz;
			      Tq = ii[WS(is, 9)];
			      Ts = ii[WS(is, 4)];
			      Tt = ii[WS(is, 7)];
			      Tv = ii[WS(is, 1)];
			      T1h = Tp + Tq;
			      Tr = Tp - Tq;
			      T1j = Ts + Tt;
			      Tu = Ts - Tt;
			      Tw = ii[WS(is, 10)];
			 }
		    }
		    {
			 E TB, T1R, T20, TK, TT, T1I, T1l;
			 T20 = FNMS(KP342584725, T1i, T1h);
			 TK = FMA(KP521108558, To, TA);
			 TT = FNMS(KP521108558, Tr, Tu);
			 T1g = Tv + Tw;
			 Tx = Tv - Tw;
			 T21 = FNMS(KP634356270, T20, T1j);
			 TU = FMA(KP715370323, TT, TA);
			 TL = FNMS(KP715370323, TK, Tr);
			 TB = FMA(KP521108558, TA, Tx);
			 T1R = FNMS(KP342584725, T1j, T1g);
			 T1I = FNMS(KP342584725, T1g, T1i);
			 T1l = FNMS(KP342584725, T1k, T1j);
			 TC = FMA(KP715370323, TB, Tu);
			 T1S = FNMS(KP634356270, T1R, T1h);
			 T1J = FNMS(KP634356270, T1I, T1k);
			 T1m = FNMS(KP634356270, T1l, T1i);
			 T12 = FMA(KP521108558, Tu, To);
			 T1z = FNMS(KP342584725, T1h, T1k);
			 T1b = FNMS(KP521108558, Tx, Tr);
		    }
	       }
	       {
		    E T13, T1A, T1c, T1Z, T1V, TH, TM, Tj, TD;
		    ro[0] = T1 + T4 + T7 + Ta + Td + Tg;
		    T13 = FMA(KP715370323, T12, Tx);
		    T1A = FNMS(KP634356270, T1z, T1g);
		    T1c = FNMS(KP715370323, T1b, To);
		    io[0] = T1f + T1g + T1h + T1i + T1j + T1k;
		    Tj = FNMS(KP778434453, Ti, T4);
		    TD = FMA(KP830830026, TC, Tr);
		    {
			 E TE, T23, T28, Tl, Tk, T22, T27;
			 T22 = FNMS(KP778434453, T21, T1g);
			 T27 = FMA(KP830830026, T26, T1t);
			 Tk = FNMS(KP876768831, Tj, Tg);
			 TE = FMA(KP918985947, TD, To);
			 T23 = FNMS(KP876768831, T22, T1k);
			 T28 = FMA(KP918985947, T27, T1s);
			 Tl = FNMS(KP959492973, Tk, T1);
			 {
			      E T1U, T1T, T24, T1Y;
			      T1T = FNMS(KP778434453, T1S, T1k);
			      T24 = FNMS(KP959492973, T23, T1f);
			      T1Y = FMA(KP830830026, T1X, T1u);
			      ro[WS(os, 1)] = FMA(KP989821441, TE, Tl);
			      ro[WS(os, 10)] = FNMS(KP989821441, TE, Tl);
			      T1U = FNMS(KP876768831, T1T, T1i);
			      io[WS(os, 10)] = FNMS(KP989821441, T28, T24);
			      io[WS(os, 1)] = FMA(KP989821441, T28, T24);
			      T1Z = FNMS(KP918985947, T1Y, T1r);
			      T1V = FNMS(KP959492973, T1U, T1f);
			 }
			 TH = FNMS(KP778434453, TG, Tg);
			 TM = FMA(KP830830026, TL, Tx);
		    }
		    {
			 E T1M, TZ, T14, T1Q;
			 {
			      E TN, TR, TV, TJ, TI, TQ, T1P;
			      TQ = FNMS(KP778434453, TP, Td);
			      io[WS(os, 9)] = FMA(KP989821441, T1Z, T1V);
			      io[WS(os, 2)] = FNMS(KP989821441, T1Z, T1V);
			      TI = FNMS(KP876768831, TH, Ta);
			      TN = FNMS(KP918985947, TM, Tu);
			      TR = FNMS(KP876768831, TQ, T7);
			      TV = FNMS(KP830830026, TU, To);
			      TJ = FNMS(KP959492973, TI, T1);
			      {
				   E T1L, TS, TW, T1K;
				   T1K = FNMS(KP778434453, T1J, T1j);
				   TS = FNMS(KP959492973, TR, T1);
				   TW = FNMS(KP918985947, TV, Tx);
				   ro[WS(os, 9)] = FMA(KP989821441, TN, TJ);
				   ro[WS(os, 2)] = FNMS(KP989821441, TN, TJ);
				   T1L = FNMS(KP876768831, T1K, T1h);
				   ro[WS(os, 3)] = FMA(KP989821441, TW, TS);
				   ro[WS(os, 8)] = FNMS(KP989821441, TW, TS);
				   T1P = FNMS(KP830830026, T1O, T1s);
				   T1M = FNMS(KP959492973, T1L, T1f);
			      }
			      TZ = FNMS(KP778434453, TY, Ta);
			      T14 = FNMS(KP830830026, T13, TA);
			      T1Q = FNMS(KP918985947, T1P, T1u);
			 }
			 {
			      E T15, T11, T1C, T1G, T1B, T10;
			      T1B = FNMS(KP778434453, T1A, T1i);
			      T10 = FNMS(KP876768831, TZ, Td);
			      T15 = FMA(KP918985947, T14, Tr);
			      io[WS(os, 8)] = FNMS(KP989821441, T1Q, T1M);
			      io[WS(os, 3)] = FMA(KP989821441, T1Q, T1M);
			      T11 = FNMS(KP959492973, T10, T1);
			      T1C = FNMS(KP876768831, T1B, T1j);
			      T1G = FNMS(KP830830026, T1F, T1q);
			      {
				   E T1D, T1H, T1o, T1x, T1n, T18;
				   T1n = FNMS(KP778434453, T1m, T1h);
				   ro[WS(os, 7)] = FMA(KP989821441, T15, T11);
				   ro[WS(os, 4)] = FNMS(KP989821441, T15, T11);
				   T1D = FNMS(KP959492973, T1C, T1f);
				   T1H = FMA(KP918985947, T1G, T1t);
				   T1o = FNMS(KP876768831, T1n, T1g);
				   T1x = FNMS(KP830830026, T1w, T1r);
				   T18 = FNMS(KP778434453, T17, T7);
				   io[WS(os, 7)] = FMA(KP989821441, T1H, T1D);
				   io[WS(os, 4)] = FNMS(KP989821441, T1H, T1D);
				   T1p = FNMS(KP959492973, T1o, T1f);
				   T1y = FNMS(KP918985947, T1x, T1q);
				   T19 = FNMS(KP876768831, T18, T4);
				   T1d = FNMS(KP830830026, T1c, Tu);
			      }
			 }
		    }
	       }
	  }
	  io[WS(os, 6)] = FNMS(KP989821441, T1y, T1p);
	  io[WS(os, 5)] = FMA(KP989821441, T1y, T1p);
	  T1a = FNMS(KP959492973, T19, T1);
	  T1e = FNMS(KP918985947, T1d, TA);
	  ro[WS(os, 5)] = FMA(KP989821441, T1e, T1a);
	  ro[WS(os, 6)] = FNMS(KP989821441, T1e, T1a);
     }
}

static const kdft_desc desc = { 11, "n1_11", {30, 0, 110, 0}, &GENUS, 0, 0, 0, 0 };
void X(codelet_n1_11) (planner *p) {
     X(kdft_register) (p, n1_11, &desc);
}

#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_notw -compact -variables 4 -pipeline-latency 4 -n 11 -name n1_11 -include n.h */

/*
 * This function contains 140 FP additions, 100 FP multiplications,
 * (or, 60 additions, 20 multiplications, 80 fused multiply/add),
 * 41 stack variables, 10 constants, and 44 memory accesses
 */
#include "n.h"

static void n1_11(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     DK(KP654860733, +0.654860733945285064056925072466293553183791199);
     DK(KP142314838, +0.142314838273285140443792668616369668791051361);
     DK(KP959492973, +0.959492973614497389890368057066327699062454848);
     DK(KP415415013, +0.415415013001886425529274149229623203524004910);
     DK(KP841253532, +0.841253532831181168861811648919367717513292498);
     DK(KP989821441, +0.989821441880932732376092037776718787376519372);
     DK(KP909631995, +0.909631995354518371411715383079028460060241051);
     DK(KP281732556, +0.281732556841429697711417915346616899035777899);
     DK(KP540640817, +0.540640817455597582107635954318691695431770608);
     DK(KP755749574, +0.755749574354258283774035843972344420179717445);
     INT i;
     for (i = v; i > 0; i = i - 1, ri = ri + ivs, ii = ii + ivs, ro = ro + ovs, io = io + ovs, MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  E T1, TM, T4, TG, Tk, TR, Tw, TN, T7, TK, Ta, TH, Tn, TQ, Td;
	  E TJ, Tq, TO, Tt, TP, Tg, TI;
	  {
	       E T2, T3, Ti, Tj;
	       T1 = ri[0];
	       TM = ii[0];
	       T2 = ri[WS(is, 1)];
	       T3 = ri[WS(is, 10)];
	       T4 = T2 + T3;
	       TG = T3 - T2;
	       Ti = ii[WS(is, 1)];
	       Tj = ii[WS(is, 10)];
	       Tk = Ti - Tj;
	       TR = Ti + Tj;
	       {
		    E Tu, Tv, T5, T6;
		    Tu = ii[WS(is, 2)];
		    Tv = ii[WS(is, 9)];
		    Tw = Tu - Tv;
		    TN = Tu + Tv;
		    T5 = ri[WS(is, 2)];
		    T6 = ri[WS(is, 9)];
		    T7 = T5 + T6;
		    TK = T6 - T5;
	       }
	  }
	  {
	       E T8, T9, To, Tp;
	       T8 = ri[WS(is, 3)];
	       T9 = ri[WS(is, 8)];
	       Ta = T8 + T9;
	       TH = T9 - T8;
	       {
		    E Tl, Tm, Tb, Tc;
		    Tl = ii[WS(is, 3)];
		    Tm = ii[WS(is, 8)];
		    Tn = Tl - Tm;
		    TQ = Tl + Tm;
		    Tb = ri[WS(is, 4)];
		    Tc = ri[WS(is, 7)];
		    Td = Tb + Tc;
		    TJ = Tc - Tb;
	       }
	       To = ii[WS(is, 4)];
	       Tp = ii[WS(is, 7)];
	       Tq = To - Tp;
	       TO = To + Tp;
	       {
		    E Tr, Ts, Te, Tf;
		    Tr = ii[WS(is, 5)];
		    Ts = ii[WS(is, 6)];
		    Tt = Tr - Ts;
		    TP = Tr + Ts;
		    Te = ri[WS(is, 5)];
		    Tf = ri[WS(is, 6)];
		    Tg = Te + Tf;
		    TI = Tf - Te;
	       }
	  }
	  {
	       E Tx, Th, TZ, T10;
	       ro[0] = T1 + T4 + T7 + Ta + Td + Tg;
	       io[0] = TM + TR + TN + TQ + TO + TP;
	       Tx = FMA(KP755749574, Tk, KP540640817 * Tn) + FNMS(KP909631995, Tt, KP281732556 * Tq) - (KP989821441 * Tw);
	       Th = FMA(KP841253532, Ta, T1) + FNMS(KP959492973, Td, KP415415013 * Tg) + FNMA(KP142314838, T7, KP654860733 * T4);
	       ro[WS(os, 7)] = Th - Tx;
	       ro[WS(os, 4)] = Th + Tx;
	       TZ = FMA(KP755749574, TG, KP540640817 * TH) + FNMS(KP909631995, TI, KP281732556 * TJ) - (KP989821441 * TK);
	       T10 = FMA(KP841253532, TQ, TM) + FNMS(KP959492973, TO, KP415415013 * TP) + FNMA(KP142314838, TN, KP654860733 * TR);
	       io[WS(os, 4)] = TZ + T10;
	       io[WS(os, 7)] = T10 - TZ;
	       {
		    E TX, TY, Tz, Ty;
		    TX = FMA(KP909631995, TG, KP755749574 * TK) + FNMA(KP540640817, TI, KP989821441 * TJ) - (KP281732556 * TH);
		    TY = FMA(KP415415013, TR, TM) + FNMS(KP142314838, TO, KP841253532 * TP) + FNMA(KP959492973, TQ, KP654860733 * TN);
		    io[WS(os, 2)] = TX + TY;
		    io[WS(os, 9)] = TY - TX;
		    Tz = FMA(KP909631995, Tk, KP755749574 * Tw) + FNMA(KP540640817, Tt, KP989821441 * Tq) - (KP281732556 * Tn);
		    Ty = FMA(KP415415013, T4, T1) + FNMS(KP142314838, Td, KP841253532 * Tg) + FNMA(KP959492973, Ta, KP654860733 * T7);
		    ro[WS(os, 9)] = Ty - Tz;
		    ro[WS(os, 2)] = Ty + Tz;
	       }
	  }
	  {
	       E TB, TA, TT, TU;
	       TB = FMA(KP540640817, Tk, KP909631995 * Tw) + FMA(KP989821441, Tn, KP755749574 * Tq) + (KP281732556 * Tt);
	       TA = FMA(KP841253532, T4, T1) + FNMS(KP959492973, Tg, KP415415013 * T7) + FNMA(KP654860733, Td, KP142314838 * Ta);
	       ro[WS(os, 10)] = TA - TB;
	       ro[WS(os, 1)] = TA + TB;
	       {
		    E TV, TW, TD, TC;
		    TV = FMA(KP540640817, TG, KP909631995 * TK) + FMA(KP989821441, TH, KP755749574 * TJ) + (KP281732556 * TI);
		    TW = FMA(KP841253532, TR, TM) + FNMS(KP959492973, TP, KP415415013 * TN) + FNMA(KP654860733, TO, KP142314838 * TQ);
		    io[WS(os, 1)] = TV + TW;
		    io[WS(os, 10)] = TW - TV;
		    TD = FMA(KP989821441, Tk, KP540640817 * Tq) + FNMS(KP909631995, Tn, KP755749574 * Tt) - (KP281732556 * Tw);
		    TC = FMA(KP415415013, Ta, T1) + FNMS(KP654860733, Tg, KP841253532 * Td) + FNMA(KP959492973, T7, KP142314838 * T4);
		    ro[WS(os, 8)] = TC - TD;
		    ro[WS(os, 3)] = TC + TD;
	       }
	       TT = FMA(KP989821441, TG, KP540640817 * TJ) + FNMS(KP909631995, TH, KP755749574 * TI) - (KP281732556 * TK);
	       TU = FMA(KP415415013, TQ, TM) + FNMS(KP654860733, TP, KP841253532 * TO) + FNMA(KP959492973, TN, KP142314838 * TR);
	       io[WS(os, 3)] = TT + TU;
	       io[WS(os, 8)] = TU - TT;
	       {
		    E TL, TS, TF, TE;
		    TL = FMA(KP281732556, TG, KP755749574 * TH) + FNMS(KP909631995, TJ, KP989821441 * TI) - (KP540640817 * TK);
		    TS = FMA(KP841253532, TN, TM) + FNMS(KP142314838, TP, KP415415013 * TO) + FNMA(KP654860733, TQ, KP959492973 * TR);
		    io[WS(os, 5)] = TL + TS;
		    io[WS(os, 6)] = TS - TL;
		    TF = FMA(KP281732556, Tk, KP755749574 * Tn) + FNMS(KP909631995, Tq, KP989821441 * Tt) - (KP540640817 * Tw);
		    TE = FMA(KP841253532, T7, T1) + FNMS(KP142314838, Tg, KP415415013 * Td) + FNMA(KP654860733, Ta, KP959492973 * T4);
		    ro[WS(os, 6)] = TE - TF;
		    ro[WS(os, 5)] = TE + TF;
	       }
	  }
     }
}

static const kdft_desc desc = { 11, "n1_11", {60, 20, 80, 0}, &GENUS, 0, 0, 0, 0 };
void X(codelet_n1_11) (planner *p) {
     X(kdft_register) (p, n1_11, &desc);
}

#endif				/* HAVE_FMA */
