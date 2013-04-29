/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * See the file COPYING for license information.
 *
 */


#ifndef __DFT_H__
#define __DFT_H__

#include "ifftw.h"
#include "codelet-dft.h"

/* problem.c: */
typedef struct {
     problem super;
     tensor *sz, *vecsz;
     R *ri, *ii, *ro, *io;
} problem_dft;

void X(dft_zerotens)(tensor *sz, R *ri, R *ii);
problem *X(mkproblem_dft)(const tensor *sz, const tensor *vecsz,
				R *ri, R *ii, R *ro, R *io);
problem *X(mkproblem_dft_d)(tensor *sz, tensor *vecsz,
			    R *ri, R *ii, R *ro, R *io);

/* solve.c: */
void X(dft_solve)(const plan *ego_, const problem *p_);

/* plan.c: */
typedef void (*dftapply) (const plan *ego, R *ri, R *ii, R *ro, R *io);

typedef struct {
     plan super;
     dftapply apply;
} plan_dft;

plan *X(mkplan_dft)(size_t size, const plan_adt *adt, dftapply apply);

#define MKPLAN_DFT(type, adt, apply) \
  (type *)X(mkplan_dft)(sizeof(type), adt, apply)

/* various solvers */
solver *X(mksolver_dft_direct)(kdft k, const kdft_desc *desc);
solver *X(mksolver_dft_directbuf)(kdft k, const kdft_desc *desc);

void X(dft_rank0_register)(planner *p);
void X(dft_rank_geq2_register)(planner *p);
void X(dft_indirect_register)(planner *p);
void X(dft_indirect_transpose_register)(planner *p);
void X(dft_vrank_geq1_register)(planner *p);
void X(dft_vrank2_transpose_register)(planner *p);
void X(dft_vrank3_transpose_register)(planner *p);
void X(dft_buffered_register)(planner *p);
void X(dft_generic_register)(planner *p);
void X(dft_rader_register)(planner *p);
void X(dft_bluestein_register)(planner *p);
void X(dft_nop_register)(planner *p);
void X(ct_generic_register)(planner *p);
void X(ct_genericbuf_register)(planner *p);

/* configurations */
void X(dft_conf_standard)(planner *p);

#if HAVE_CELL
  void X(dft_conf_cell)(planner *p);
#endif

#endif /* __DFT_H__ */
