/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * See the file COPYING for license information.
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Mon Nov 10 20:45:17 EST 2008 */

#include "codelet-rdft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_r2cf -fma -reorder-insns -schedule-for-pipeline -compact -variables 4 -pipeline-latency 4 -n 3 -name r2cf_3 -include r2cf.h */

/*
 * This function contains 4 FP additions, 2 FP multiplications,
 * (or, 3 additions, 1 multiplications, 1 fused multiply/add),
 * 7 stack variables, 2 constants, and 6 memory accesses
 */
#include "r2cf.h"

static void r2cf_3(R *R0, R *R1, R *Cr, R *Ci, stride rs, stride csr, stride csi, INT v, INT ivs, INT ovs)
{
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     DK(KP866025403, +0.866025403784438646763723170752936183471402627);
     INT i;
     for (i = v; i > 0; i = i - 1, R0 = R0 + ivs, R1 = R1 + ivs, Cr = Cr + ovs, Ci = Ci + ovs, MAKE_VOLATILE_STRIDE(rs), MAKE_VOLATILE_STRIDE(csr), MAKE_VOLATILE_STRIDE(csi)) {
	  E T1, T2, T3, T4;
	  T1 = R0[0];
	  T2 = R1[0];
	  T3 = R0[WS(rs, 1)];
	  Ci[WS(csi, 1)] = KP866025403 * (T3 - T2);
	  T4 = T2 + T3;
	  Cr[0] = T1 + T4;
	  Cr[WS(csr, 1)] = FNMS(KP500000000, T4, T1);
     }
}

static const kr2c_desc desc = { 3, "r2cf_3", {3, 1, 1, 0}, &GENUS };

void X(codelet_r2cf_3) (planner *p) {
     X(kr2c_register) (p, r2cf_3, &desc);
}

#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_r2cf -compact -variables 4 -pipeline-latency 4 -n 3 -name r2cf_3 -include r2cf.h */

/*
 * This function contains 4 FP additions, 2 FP multiplications,
 * (or, 3 additions, 1 multiplications, 1 fused multiply/add),
 * 7 stack variables, 2 constants, and 6 memory accesses
 */
#include "r2cf.h"

static void r2cf_3(R *R0, R *R1, R *Cr, R *Ci, stride rs, stride csr, stride csi, INT v, INT ivs, INT ovs)
{
     DK(KP866025403, +0.866025403784438646763723170752936183471402627);
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     INT i;
     for (i = v; i > 0; i = i - 1, R0 = R0 + ivs, R1 = R1 + ivs, Cr = Cr + ovs, Ci = Ci + ovs, MAKE_VOLATILE_STRIDE(rs), MAKE_VOLATILE_STRIDE(csr), MAKE_VOLATILE_STRIDE(csi)) {
	  E T1, T2, T3, T4;
	  T1 = R0[0];
	  T2 = R1[0];
	  T3 = R0[WS(rs, 1)];
	  T4 = T2 + T3;
	  Cr[WS(csr, 1)] = FNMS(KP500000000, T4, T1);
	  Ci[WS(csi, 1)] = KP866025403 * (T3 - T2);
	  Cr[0] = T1 + T4;
     }
}

static const kr2c_desc desc = { 3, "r2cf_3", {3, 1, 1, 0}, &GENUS };

void X(codelet_r2cf_3) (planner *p) {
     X(kr2c_register) (p, r2cf_3, &desc);
}

#endif				/* HAVE_FMA */
