/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * See the file COPYING for license information.
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Mon Nov 10 20:30:23 EST 2008 */

#include "codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_twidsq -fma -reorder-insns -schedule-for-pipeline -compact -variables 4 -pipeline-latency 4 -reload-twiddle -dif -n 4 -name q1_4 -include q.h */

/*
 * This function contains 88 FP additions, 48 FP multiplications,
 * (or, 64 additions, 24 multiplications, 24 fused multiply/add),
 * 76 stack variables, 0 constants, and 64 memory accesses
 */
#include "q.h"

static void q1_4(R *rio, R *iio, const R *W, stride rs, stride vs, INT mb, INT me, INT ms)
{
     INT m;
     for (m = mb, W = W + (mb * 6); m < me; m = m + 1, rio = rio + ms, iio = iio + ms, W = W + 6, MAKE_VOLATILE_STRIDE(rs), MAKE_VOLATILE_STRIDE(vs)) {
	  E T1X, T1S, T1L, T1Y, T1R;
	  {
	       E T3, Tf, Tv, Ti, Tw, Tx, T6, Tm, Tc, Ts, T1T, T1H, T29, T1W, T2a;
	       E T2b, T1K, T20, T1Q, T26, TN, TB, T13, TQ, T14, T15, TE, TU, TK, T10;
	       E T1l, T19, T1a, T1h, T1B, T1o, T1C, T1b, T1D, T1e, T1c;
	       {
		    E T1I, T1P, T1J, T1M;
		    {
			 E Tb, T4, T5, T8;
			 {
			      E T1, T2, T9, Ta, Tg, Th;
			      T1 = rio[0];
			      T2 = rio[WS(rs, 2)];
			      T9 = iio[0];
			      Ta = iio[WS(rs, 2)];
			      Tg = iio[WS(rs, 1)];
			      T3 = T1 + T2;
			      Tf = T1 - T2;
			      Th = iio[WS(rs, 3)];
			      Tv = T9 + Ta;
			      Tb = T9 - Ta;
			      T4 = rio[WS(rs, 1)];
			      Ti = Tg - Th;
			      Tw = Tg + Th;
			      T5 = rio[WS(rs, 3)];
			 }
			 Tx = Tv - Tw;
			 T8 = T4 - T5;
			 T6 = T4 + T5;
			 {
			      E T1N, T1O, T1F, T1G, T1U, T1V;
			      T1F = rio[WS(vs, 3)];
			      T1G = rio[WS(vs, 3) + WS(rs, 2)];
			      Tm = Tb - T8;
			      Tc = T8 + Tb;
			      Ts = T3 - T6;
			      T1T = T1F - T1G;
			      T1H = T1F + T1G;
			      T1N = iio[WS(vs, 3)];
			      T1O = iio[WS(vs, 3) + WS(rs, 2)];
			      T1U = iio[WS(vs, 3) + WS(rs, 1)];
			      T1V = iio[WS(vs, 3) + WS(rs, 3)];
			      T1I = rio[WS(vs, 3) + WS(rs, 1)];
			      T1P = T1N - T1O;
			      T29 = T1N + T1O;
			      T1W = T1U - T1V;
			      T2a = T1U + T1V;
			      T1J = rio[WS(vs, 3) + WS(rs, 3)];
			 }
		    }
		    T2b = T29 - T2a;
		    T1M = T1I - T1J;
		    T1K = T1I + T1J;
		    {
			 E TC, TJ, TD, TG;
			 {
			      E TH, TI, Tz, TA, TO, TP;
			      Tz = rio[WS(vs, 1)];
			      TA = rio[WS(vs, 1) + WS(rs, 2)];
			      T20 = T1P - T1M;
			      T1Q = T1M + T1P;
			      T26 = T1H - T1K;
			      TN = Tz - TA;
			      TB = Tz + TA;
			      TH = iio[WS(vs, 1)];
			      TI = iio[WS(vs, 1) + WS(rs, 2)];
			      TO = iio[WS(vs, 1) + WS(rs, 1)];
			      TP = iio[WS(vs, 1) + WS(rs, 3)];
			      TC = rio[WS(vs, 1) + WS(rs, 1)];
			      TJ = TH - TI;
			      T13 = TH + TI;
			      TQ = TO - TP;
			      T14 = TO + TP;
			      TD = rio[WS(vs, 1) + WS(rs, 3)];
			 }
			 T15 = T13 - T14;
			 TG = TC - TD;
			 TE = TC + TD;
			 {
			      E T1f, T1g, T17, T18, T1m, T1n;
			      T17 = rio[WS(vs, 2)];
			      T18 = rio[WS(vs, 2) + WS(rs, 2)];
			      TU = TJ - TG;
			      TK = TG + TJ;
			      T10 = TB - TE;
			      T1l = T17 - T18;
			      T19 = T17 + T18;
			      T1f = iio[WS(vs, 2)];
			      T1g = iio[WS(vs, 2) + WS(rs, 2)];
			      T1m = iio[WS(vs, 2) + WS(rs, 1)];
			      T1n = iio[WS(vs, 2) + WS(rs, 3)];
			      T1a = rio[WS(vs, 2) + WS(rs, 1)];
			      T1h = T1f - T1g;
			      T1B = T1f + T1g;
			      T1o = T1m - T1n;
			      T1C = T1m + T1n;
			      T1b = rio[WS(vs, 2) + WS(rs, 3)];
			 }
		    }
	       }
	       T1D = T1B - T1C;
	       T1e = T1a - T1b;
	       T1c = T1a + T1b;
	       {
		    E T1s, T1i, T1y, T28, T27, Tr, Tu;
		    rio[0] = T3 + T6;
		    iio[0] = Tv + Tw;
		    T1s = T1h - T1e;
		    T1i = T1e + T1h;
		    T1y = T19 - T1c;
		    rio[WS(rs, 1)] = TB + TE;
		    iio[WS(rs, 1)] = T13 + T14;
		    rio[WS(rs, 2)] = T19 + T1c;
		    iio[WS(rs, 2)] = T1B + T1C;
		    iio[WS(rs, 3)] = T29 + T2a;
		    rio[WS(rs, 3)] = T1H + T1K;
		    Tr = W[2];
		    Tu = W[3];
		    {
			 E T25, Ty, Tt, T2c;
			 T25 = W[2];
			 T28 = W[3];
			 Ty = Tr * Tx;
			 Tt = Tr * Ts;
			 T2c = T25 * T2b;
			 T27 = T25 * T26;
			 iio[WS(vs, 2)] = FNMS(Tu, Ts, Ty);
			 rio[WS(vs, 2)] = FMA(Tu, Tx, Tt);
			 iio[WS(vs, 2) + WS(rs, 3)] = FNMS(T28, T26, T2c);
		    }
		    rio[WS(vs, 2) + WS(rs, 3)] = FMA(T28, T2b, T27);
		    {
			 E Tp, T1v, T23, T22, T1Z, TR, TM, TF;
			 {
			      E T1A, T1z, TZ, T12;
			      TZ = W[2];
			      T12 = W[3];
			      {
				   E T1x, T16, T11, T1E;
				   T1x = W[2];
				   T1A = W[3];
				   T16 = TZ * T15;
				   T11 = TZ * T10;
				   T1E = T1x * T1D;
				   T1z = T1x * T1y;
				   iio[WS(vs, 2) + WS(rs, 1)] = FNMS(T12, T10, T16);
				   rio[WS(vs, 2) + WS(rs, 1)] = FMA(T12, T15, T11);
				   iio[WS(vs, 2) + WS(rs, 2)] = FNMS(T1A, T1y, T1E);
			      }
			      rio[WS(vs, 2) + WS(rs, 2)] = FMA(T1A, T1D, T1z);
			      {
				   E Tj, Te, T7, T1p, T1k, T1j;
				   Tp = Tf + Ti;
				   Tj = Tf - Ti;
				   Te = W[5];
				   T7 = W[4];
				   {
					E T1d, T1q, Tk, Td;
					T1p = T1l - T1o;
					T1v = T1l + T1o;
					T1k = W[5];
					Tk = Te * Tc;
					Td = T7 * Tc;
					T1d = W[4];
					T1q = T1k * T1i;
					rio[WS(vs, 3)] = FMA(T7, Tj, Tk);
					iio[WS(vs, 3)] = FNMS(Te, Tj, Td);
					T1j = T1d * T1i;
					rio[WS(vs, 3) + WS(rs, 2)] = FMA(T1d, T1p, T1q);
				   }
				   T23 = T1T + T1W;
				   T1X = T1T - T1W;
				   T22 = W[1];
				   iio[WS(vs, 3) + WS(rs, 2)] = FNMS(T1k, T1p, T1j);
				   T1Z = W[0];
			      }
			 }
			 {
			      E TX, TW, TT, TY, TV, T24, T21;
			      TX = TN + TQ;
			      TR = TN - TQ;
			      T24 = T22 * T20;
			      TW = W[1];
			      T21 = T1Z * T20;
			      TT = W[0];
			      rio[WS(vs, 1) + WS(rs, 3)] = FMA(T1Z, T23, T24);
			      TY = TW * TU;
			      iio[WS(vs, 1) + WS(rs, 3)] = FNMS(T22, T23, T21);
			      TV = TT * TU;
			      rio[WS(vs, 1) + WS(rs, 1)] = FMA(TT, TX, TY);
			      TM = W[5];
			      iio[WS(vs, 1) + WS(rs, 1)] = FNMS(TW, TX, TV);
			      TF = W[4];
			 }
			 {
			      E To, Tl, Tq, Tn, TS, TL;
			      TS = TM * TK;
			      To = W[1];
			      TL = TF * TK;
			      Tl = W[0];
			      rio[WS(vs, 3) + WS(rs, 1)] = FMA(TF, TR, TS);
			      Tq = To * Tm;
			      iio[WS(vs, 3) + WS(rs, 1)] = FNMS(TM, TR, TL);
			      Tn = Tl * Tm;
			      {
				   E T1u, T1r, T1w, T1t;
				   rio[WS(vs, 1)] = FMA(Tl, Tp, Tq);
				   T1u = W[1];
				   iio[WS(vs, 1)] = FNMS(To, Tp, Tn);
				   T1r = W[0];
				   T1w = T1u * T1s;
				   T1S = W[5];
				   T1t = T1r * T1s;
				   T1L = W[4];
				   rio[WS(vs, 1) + WS(rs, 2)] = FMA(T1r, T1v, T1w);
				   T1Y = T1S * T1Q;
				   iio[WS(vs, 1) + WS(rs, 2)] = FNMS(T1u, T1v, T1t);
				   T1R = T1L * T1Q;
			      }
			 }
		    }
	       }
	  }
	  rio[WS(vs, 3) + WS(rs, 3)] = FMA(T1L, T1X, T1Y);
	  iio[WS(vs, 3) + WS(rs, 3)] = FNMS(T1S, T1X, T1R);
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 0, 4},
     {TW_NEXT, 1, 0}
};

static const ct_desc desc = { 4, "q1_4", twinstr, &GENUS, {64, 24, 24, 0}, 0, 0, 0 };

void X(codelet_q1_4) (planner *p) {
     X(kdft_difsq_register) (p, q1_4, &desc);
}
#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_twidsq -compact -variables 4 -pipeline-latency 4 -reload-twiddle -dif -n 4 -name q1_4 -include q.h */

/*
 * This function contains 88 FP additions, 48 FP multiplications,
 * (or, 64 additions, 24 multiplications, 24 fused multiply/add),
 * 37 stack variables, 0 constants, and 64 memory accesses
 */
#include "q.h"

static void q1_4(R *rio, R *iio, const R *W, stride rs, stride vs, INT mb, INT me, INT ms)
{
     INT m;
     for (m = mb, W = W + (mb * 6); m < me; m = m + 1, rio = rio + ms, iio = iio + ms, W = W + 6, MAKE_VOLATILE_STRIDE(rs), MAKE_VOLATILE_STRIDE(vs)) {
	  E T3, Te, Tb, Tq, T6, T8, Th, Tr, Tv, TG, TD, TS, Ty, TA, TJ;
	  E TT, TX, T18, T15, T1k, T10, T12, T1b, T1l, T1p, T1A, T1x, T1M, T1s, T1u;
	  E T1D, T1N;
	  {
	       E T1, T2, T9, Ta;
	       T1 = rio[0];
	       T2 = rio[WS(rs, 2)];
	       T3 = T1 + T2;
	       Te = T1 - T2;
	       T9 = iio[0];
	       Ta = iio[WS(rs, 2)];
	       Tb = T9 - Ta;
	       Tq = T9 + Ta;
	  }
	  {
	       E T4, T5, Tf, Tg;
	       T4 = rio[WS(rs, 1)];
	       T5 = rio[WS(rs, 3)];
	       T6 = T4 + T5;
	       T8 = T4 - T5;
	       Tf = iio[WS(rs, 1)];
	       Tg = iio[WS(rs, 3)];
	       Th = Tf - Tg;
	       Tr = Tf + Tg;
	  }
	  {
	       E Tt, Tu, TB, TC;
	       Tt = rio[WS(vs, 1)];
	       Tu = rio[WS(vs, 1) + WS(rs, 2)];
	       Tv = Tt + Tu;
	       TG = Tt - Tu;
	       TB = iio[WS(vs, 1)];
	       TC = iio[WS(vs, 1) + WS(rs, 2)];
	       TD = TB - TC;
	       TS = TB + TC;
	  }
	  {
	       E Tw, Tx, TH, TI;
	       Tw = rio[WS(vs, 1) + WS(rs, 1)];
	       Tx = rio[WS(vs, 1) + WS(rs, 3)];
	       Ty = Tw + Tx;
	       TA = Tw - Tx;
	       TH = iio[WS(vs, 1) + WS(rs, 1)];
	       TI = iio[WS(vs, 1) + WS(rs, 3)];
	       TJ = TH - TI;
	       TT = TH + TI;
	  }
	  {
	       E TV, TW, T13, T14;
	       TV = rio[WS(vs, 2)];
	       TW = rio[WS(vs, 2) + WS(rs, 2)];
	       TX = TV + TW;
	       T18 = TV - TW;
	       T13 = iio[WS(vs, 2)];
	       T14 = iio[WS(vs, 2) + WS(rs, 2)];
	       T15 = T13 - T14;
	       T1k = T13 + T14;
	  }
	  {
	       E TY, TZ, T19, T1a;
	       TY = rio[WS(vs, 2) + WS(rs, 1)];
	       TZ = rio[WS(vs, 2) + WS(rs, 3)];
	       T10 = TY + TZ;
	       T12 = TY - TZ;
	       T19 = iio[WS(vs, 2) + WS(rs, 1)];
	       T1a = iio[WS(vs, 2) + WS(rs, 3)];
	       T1b = T19 - T1a;
	       T1l = T19 + T1a;
	  }
	  {
	       E T1n, T1o, T1v, T1w;
	       T1n = rio[WS(vs, 3)];
	       T1o = rio[WS(vs, 3) + WS(rs, 2)];
	       T1p = T1n + T1o;
	       T1A = T1n - T1o;
	       T1v = iio[WS(vs, 3)];
	       T1w = iio[WS(vs, 3) + WS(rs, 2)];
	       T1x = T1v - T1w;
	       T1M = T1v + T1w;
	  }
	  {
	       E T1q, T1r, T1B, T1C;
	       T1q = rio[WS(vs, 3) + WS(rs, 1)];
	       T1r = rio[WS(vs, 3) + WS(rs, 3)];
	       T1s = T1q + T1r;
	       T1u = T1q - T1r;
	       T1B = iio[WS(vs, 3) + WS(rs, 1)];
	       T1C = iio[WS(vs, 3) + WS(rs, 3)];
	       T1D = T1B - T1C;
	       T1N = T1B + T1C;
	  }
	  rio[0] = T3 + T6;
	  iio[0] = Tq + Tr;
	  rio[WS(rs, 1)] = Tv + Ty;
	  iio[WS(rs, 1)] = TS + TT;
	  rio[WS(rs, 2)] = TX + T10;
	  iio[WS(rs, 2)] = T1k + T1l;
	  iio[WS(rs, 3)] = T1M + T1N;
	  rio[WS(rs, 3)] = T1p + T1s;
	  {
	       E Tc, Ti, T7, Td;
	       Tc = T8 + Tb;
	       Ti = Te - Th;
	       T7 = W[4];
	       Td = W[5];
	       iio[WS(vs, 3)] = FNMS(Td, Ti, T7 * Tc);
	       rio[WS(vs, 3)] = FMA(Td, Tc, T7 * Ti);
	  }
	  {
	       E T1K, T1O, T1J, T1L;
	       T1K = T1p - T1s;
	       T1O = T1M - T1N;
	       T1J = W[2];
	       T1L = W[3];
	       rio[WS(vs, 2) + WS(rs, 3)] = FMA(T1J, T1K, T1L * T1O);
	       iio[WS(vs, 2) + WS(rs, 3)] = FNMS(T1L, T1K, T1J * T1O);
	  }
	  {
	       E Tk, Tm, Tj, Tl;
	       Tk = Tb - T8;
	       Tm = Te + Th;
	       Tj = W[0];
	       Tl = W[1];
	       iio[WS(vs, 1)] = FNMS(Tl, Tm, Tj * Tk);
	       rio[WS(vs, 1)] = FMA(Tl, Tk, Tj * Tm);
	  }
	  {
	       E To, Ts, Tn, Tp;
	       To = T3 - T6;
	       Ts = Tq - Tr;
	       Tn = W[2];
	       Tp = W[3];
	       rio[WS(vs, 2)] = FMA(Tn, To, Tp * Ts);
	       iio[WS(vs, 2)] = FNMS(Tp, To, Tn * Ts);
	  }
	  {
	       E T16, T1c, T11, T17;
	       T16 = T12 + T15;
	       T1c = T18 - T1b;
	       T11 = W[4];
	       T17 = W[5];
	       iio[WS(vs, 3) + WS(rs, 2)] = FNMS(T17, T1c, T11 * T16);
	       rio[WS(vs, 3) + WS(rs, 2)] = FMA(T17, T16, T11 * T1c);
	  }
	  {
	       E T1G, T1I, T1F, T1H;
	       T1G = T1x - T1u;
	       T1I = T1A + T1D;
	       T1F = W[0];
	       T1H = W[1];
	       iio[WS(vs, 1) + WS(rs, 3)] = FNMS(T1H, T1I, T1F * T1G);
	       rio[WS(vs, 1) + WS(rs, 3)] = FMA(T1H, T1G, T1F * T1I);
	  }
	  {
	       E TQ, TU, TP, TR;
	       TQ = Tv - Ty;
	       TU = TS - TT;
	       TP = W[2];
	       TR = W[3];
	       rio[WS(vs, 2) + WS(rs, 1)] = FMA(TP, TQ, TR * TU);
	       iio[WS(vs, 2) + WS(rs, 1)] = FNMS(TR, TQ, TP * TU);
	  }
	  {
	       E T1e, T1g, T1d, T1f;
	       T1e = T15 - T12;
	       T1g = T18 + T1b;
	       T1d = W[0];
	       T1f = W[1];
	       iio[WS(vs, 1) + WS(rs, 2)] = FNMS(T1f, T1g, T1d * T1e);
	       rio[WS(vs, 1) + WS(rs, 2)] = FMA(T1f, T1e, T1d * T1g);
	  }
	  {
	       E T1i, T1m, T1h, T1j;
	       T1i = TX - T10;
	       T1m = T1k - T1l;
	       T1h = W[2];
	       T1j = W[3];
	       rio[WS(vs, 2) + WS(rs, 2)] = FMA(T1h, T1i, T1j * T1m);
	       iio[WS(vs, 2) + WS(rs, 2)] = FNMS(T1j, T1i, T1h * T1m);
	  }
	  {
	       E T1y, T1E, T1t, T1z;
	       T1y = T1u + T1x;
	       T1E = T1A - T1D;
	       T1t = W[4];
	       T1z = W[5];
	       iio[WS(vs, 3) + WS(rs, 3)] = FNMS(T1z, T1E, T1t * T1y);
	       rio[WS(vs, 3) + WS(rs, 3)] = FMA(T1z, T1y, T1t * T1E);
	  }
	  {
	       E TM, TO, TL, TN;
	       TM = TD - TA;
	       TO = TG + TJ;
	       TL = W[0];
	       TN = W[1];
	       iio[WS(vs, 1) + WS(rs, 1)] = FNMS(TN, TO, TL * TM);
	       rio[WS(vs, 1) + WS(rs, 1)] = FMA(TN, TM, TL * TO);
	  }
	  {
	       E TE, TK, Tz, TF;
	       TE = TA + TD;
	       TK = TG - TJ;
	       Tz = W[4];
	       TF = W[5];
	       iio[WS(vs, 3) + WS(rs, 1)] = FNMS(TF, TK, Tz * TE);
	       rio[WS(vs, 3) + WS(rs, 1)] = FMA(TF, TE, Tz * TK);
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 0, 4},
     {TW_NEXT, 1, 0}
};

static const ct_desc desc = { 4, "q1_4", twinstr, &GENUS, {64, 24, 24, 0}, 0, 0, 0 };

void X(codelet_q1_4) (planner *p) {
     X(kdft_difsq_register) (p, q1_4, &desc);
}
#endif				/* HAVE_FMA */
