/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * See the file COPYING for license information.
 *
 */


#include "ifftw.h"

#ifdef HAVE_UNISTD_H
#  include <unistd.h>
#endif

#ifndef WITH_SLOW_TIMER
#  include "cycle.h"
#endif

#ifndef FFTW_TIME_LIMIT
#define FFTW_TIME_LIMIT 2.0  /* don't run for more than two seconds */
#endif

#if defined(HAVE_GETTIMEOFDAY)
crude_time X(get_crude_time)(void)
{
     crude_time tv;
     gettimeofday(&tv, 0);
     return tv;
}

#define elapsed_sec(t1,t0) ((double)(t1.tv_sec - t0.tv_sec) +		\
			    (double)(t1.tv_usec - t0.tv_usec) * 1.0E-6)

static double elapsed_since(crude_time t0)
{
     crude_time t1;
     gettimeofday(&t1, 0);
     return elapsed_sec(t1, t0);
}

#  define TIME_MIN_SEC 1.0e-2 /* from fftw2 */

#else /* !HAVE_GETTIMEOFDAY */

/* Note that the only system where we are likely to need to fall back
   on the clock() function is Windows, for which CLOCKS_PER_SEC is 1000
   and thus the clock wraps once every 50 days.  This should hopefully
   be longer than the time required to create any single plan! */
crude_time X(get_crude_time)(void) { return clock(); }

#define elapsed_sec(t1,t0) ((double) ((t1) - (t0)) / CLOCKS_PER_SEC)

static double elapsed_since(crude_time t0)
{
     return elapsed_sec(clock(), t0);
}

#  define TIME_MIN_SEC 2.0e-1 /* from fftw2 */

#endif /* !HAVE_GETTIMEOFDAY */

double X(elapsed_since)(const planner *plnr, const problem *p, crude_time t0)
{
     double t = elapsed_since(t0);
     if (plnr->cost_hook)
	  t = plnr->cost_hook(p, t, COST_MAX);
     return t;
}

#ifdef WITH_SLOW_TIMER
/* excruciatingly slow; only use this if there is no choice! */
typedef crude_time ticks;
#  define getticks X(get_crude_time)
#  define elapsed(t1,t0) elapsed_sec(t1,t0)
#  define TIME_MIN TIME_MIN_SEC
#  define TIME_REPEAT 4 /* from fftw2 */
#  define HAVE_TICK_COUNTER
#endif

#ifdef HAVE_TICK_COUNTER

#  ifndef TIME_MIN
#    define TIME_MIN 100.0
#  endif

#  ifndef TIME_REPEAT
#    define TIME_REPEAT 8
#  endif

  static double measure(plan *pln, const problem *p, int iter)
  {
       ticks t0, t1;
       int i;

       t0 = getticks();
       for (i = 0; i < iter; ++i) 
	    pln->adt->solve(pln, p);
       t1 = getticks();
       return elapsed(t1, t0);
  }


  double X(measure_execution_time)(const planner *plnr, 
				   plan *pln, const problem *p)
  {
       int iter;
       int repeat;

       X(plan_awake)(pln, AWAKE_ZERO);
       p->adt->zero(p);

  start_over:
       for (iter = 1; iter; iter *= 2) {
	    double tmin = 0;
	    int first = 1;
	    crude_time begin = X(get_crude_time)();

	    /* repeat the measurement TIME_REPEAT times */
	    for (repeat = 0; repeat < TIME_REPEAT; ++repeat) {
		 double t = measure(pln, p, iter);
		 
		 if (plnr->cost_hook)
		      t = plnr->cost_hook(p, t, COST_MAX);
		 if (t < 0)
		      goto start_over;

		 if (first || t < tmin)
		      tmin = t;
		 first = 0;

		 /* do not run for too long */
		 if (X(elapsed_since)(plnr, p, begin) > FFTW_TIME_LIMIT)
		      break;
	    }

	    if (tmin >= TIME_MIN) {
		 X(plan_awake)(pln, SLEEPY);
		 return tmin / (double) iter;
	    }
       }
       goto start_over; /* may happen if timer is screwed up */
  }

#else /* no cycle counter */

  double X(measure_execution_time)(const planner *plnr, 
				   plan *pln, const problem *p)
  {
       UNUSED(plnr);
       UNUSED(p);
       UNUSED(pln);
       return -1.0;
  }

#endif
