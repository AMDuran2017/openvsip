/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * See the file COPYING for license information.
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Mon Nov 10 20:52:57 EST 2008 */

#include "codelet-rdft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_hc2cdft -fma -reorder-insns -schedule-for-pipeline -compact -variables 4 -pipeline-latency 4 -twiddle-log3 -precompute-twiddles -n 4 -dit -name hc2cfdft2_4 -include hc2cf.h */

/*
 * This function contains 32 FP additions, 24 FP multiplications,
 * (or, 24 additions, 16 multiplications, 8 fused multiply/add),
 * 33 stack variables, 1 constants, and 16 memory accesses
 */
#include "hc2cf.h"

static void hc2cfdft2_4(R *Rp, R *Ip, R *Rm, R *Im, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     INT m;
     for (m = mb, W = W + ((mb - 1) * 4); m < me; m = m + 1, Rp = Rp + ms, Ip = Ip + ms, Rm = Rm - ms, Im = Im - ms, W = W + 4, MAKE_VOLATILE_STRIDE(rs)) {
	  E T1, T5, T2, T4;
	  T1 = W[0];
	  T5 = W[3];
	  T2 = W[2];
	  T4 = W[1];
	  {
	       E Tc, T6, Tp, Tj, Tw, Tt, T9, TE, To, TC, Ta, Tr, Tf, Tl, Tm;
	       {
		    E Th, Tb, T3, Ti;
		    Th = Ip[0];
		    Tb = T1 * T5;
		    T3 = T1 * T2;
		    Ti = Im[0];
		    Tl = Rm[0];
		    Tc = FNMS(T4, T2, Tb);
		    T6 = FMA(T4, T5, T3);
		    Tp = Th + Ti;
		    Tj = Th - Ti;
		    Tm = Rp[0];
	       }
	       {
		    E T7, T8, Td, Tn, Te;
		    T7 = Ip[WS(rs, 1)];
		    T8 = Im[WS(rs, 1)];
		    Td = Rp[WS(rs, 1)];
		    Tw = Tm + Tl;
		    Tn = Tl - Tm;
		    Tt = T7 + T8;
		    T9 = T7 - T8;
		    Te = Rm[WS(rs, 1)];
		    TE = T4 * Tn;
		    To = T1 * Tn;
		    TC = T2 * Tt;
		    Ta = T6 * T9;
		    Tr = Td - Te;
		    Tf = Td + Te;
	       }
	       {
		    E Tq, Tk, TB, Ty, Tu, TI, TG, TF;
		    Tq = FNMS(T4, Tp, To);
		    TF = FMA(T1, Tp, TE);
		    {
			 E Tg, Tx, TD, Ts;
			 Tg = FNMS(Tc, Tf, Ta);
			 Tx = T6 * Tf;
			 TD = FNMS(T5, Tr, TC);
			 Ts = T2 * Tr;
			 Tk = Tg + Tj;
			 TB = Tj - Tg;
			 Ty = FMA(Tc, T9, Tx);
			 Tu = FMA(T5, Tt, Ts);
			 TI = TD + TF;
			 TG = TD - TF;
		    }
		    {
			 E Tz, TH, Tv, TA;
			 Tz = Tw - Ty;
			 TH = Tw + Ty;
			 Tv = Tq - Tu;
			 TA = Tu + Tq;
			 Rp[0] = KP500000000 * (TH + TI);
			 Rm[WS(rs, 1)] = KP500000000 * (TH - TI);
			 Rm[0] = KP500000000 * (Tz - TA);
			 Im[WS(rs, 1)] = KP500000000 * (Tv - Tk);
			 Ip[0] = KP500000000 * (Tk + Tv);
			 Im[0] = KP500000000 * (TG - TB);
			 Rp[WS(rs, 1)] = KP500000000 * (Tz + TA);
			 Ip[WS(rs, 1)] = KP500000000 * (TB + TG);
		    }
	       }
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_CEXP, 1, 1},
     {TW_CEXP, 1, 3},
     {TW_NEXT, 1, 0}
};

static const hc2c_desc desc = { 4, "hc2cfdft2_4", twinstr, &GENUS, {24, 16, 8, 0} };

void X(codelet_hc2cfdft2_4) (planner *p) {
     X(khc2c_register) (p, hc2cfdft2_4, &desc, HC2C_VIA_DFT);
}
#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_hc2cdft -compact -variables 4 -pipeline-latency 4 -twiddle-log3 -precompute-twiddles -n 4 -dit -name hc2cfdft2_4 -include hc2cf.h */

/*
 * This function contains 32 FP additions, 24 FP multiplications,
 * (or, 24 additions, 16 multiplications, 8 fused multiply/add),
 * 24 stack variables, 1 constants, and 16 memory accesses
 */
#include "hc2cf.h"

static void hc2cfdft2_4(R *Rp, R *Ip, R *Rm, R *Im, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     INT m;
     for (m = mb, W = W + ((mb - 1) * 4); m < me; m = m + 1, Rp = Rp + ms, Ip = Ip + ms, Rm = Rm - ms, Im = Im - ms, W = W + 4, MAKE_VOLATILE_STRIDE(rs)) {
	  E T1, T3, T2, T4, T5, T9;
	  T1 = W[0];
	  T3 = W[1];
	  T2 = W[2];
	  T4 = W[3];
	  T5 = FMA(T1, T2, T3 * T4);
	  T9 = FNMS(T3, T2, T1 * T4);
	  {
	       E Tg, Tr, Tm, Tx, Td, Tw, Tp, Ts;
	       {
		    E Te, Tf, Tl, Ti, Tj, Tk;
		    Te = Ip[0];
		    Tf = Im[0];
		    Tl = Te + Tf;
		    Ti = Rm[0];
		    Tj = Rp[0];
		    Tk = Ti - Tj;
		    Tg = Te - Tf;
		    Tr = Tj + Ti;
		    Tm = FNMS(T3, Tl, T1 * Tk);
		    Tx = FMA(T3, Tk, T1 * Tl);
	       }
	       {
		    E T8, To, Tc, Tn;
		    {
			 E T6, T7, Ta, Tb;
			 T6 = Ip[WS(rs, 1)];
			 T7 = Im[WS(rs, 1)];
			 T8 = T6 - T7;
			 To = T6 + T7;
			 Ta = Rp[WS(rs, 1)];
			 Tb = Rm[WS(rs, 1)];
			 Tc = Ta + Tb;
			 Tn = Ta - Tb;
		    }
		    Td = FNMS(T9, Tc, T5 * T8);
		    Tw = FNMS(T4, Tn, T2 * To);
		    Tp = FMA(T2, Tn, T4 * To);
		    Ts = FMA(T5, Tc, T9 * T8);
	       }
	       {
		    E Th, Tq, Tz, TA;
		    Th = Td + Tg;
		    Tq = Tm - Tp;
		    Ip[0] = KP500000000 * (Th + Tq);
		    Im[WS(rs, 1)] = KP500000000 * (Tq - Th);
		    Tz = Tr + Ts;
		    TA = Tw + Tx;
		    Rm[WS(rs, 1)] = KP500000000 * (Tz - TA);
		    Rp[0] = KP500000000 * (Tz + TA);
	       }
	       {
		    E Tt, Tu, Tv, Ty;
		    Tt = Tr - Ts;
		    Tu = Tp + Tm;
		    Rm[0] = KP500000000 * (Tt - Tu);
		    Rp[WS(rs, 1)] = KP500000000 * (Tt + Tu);
		    Tv = Tg - Td;
		    Ty = Tw - Tx;
		    Ip[WS(rs, 1)] = KP500000000 * (Tv + Ty);
		    Im[0] = KP500000000 * (Ty - Tv);
	       }
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_CEXP, 1, 1},
     {TW_CEXP, 1, 3},
     {TW_NEXT, 1, 0}
};

static const hc2c_desc desc = { 4, "hc2cfdft2_4", twinstr, &GENUS, {24, 16, 8, 0} };

void X(codelet_hc2cfdft2_4) (planner *p) {
     X(khc2c_register) (p, hc2cfdft2_4, &desc, HC2C_VIA_DFT);
}
#endif				/* HAVE_FMA */
