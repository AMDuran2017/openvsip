/* Copyright (c) 2008 by CodeSourcery.  All rights reserved.

   This file is available for license from CodeSourcery, Inc. under the terms
   of a commercial license and under the GPL.  It is not part of the VSIPL++
   reference implementation and is not available under the BSD license.
*/
/** @file    tests/solvers/cholesky/double.cpp
    @author  Jules Bergmann
    @date    2005-10-07
    @brief   VSIPL++ Library: Unit tests for Cholesky solver.
*/

/***********************************************************************
  Included Files
***********************************************************************/

#include <vsip/initfin.hpp>
#include <vsip/support.hpp>
#include <vsip/tensor.hpp>
#include <vsip/solvers.hpp>

#include "cholesky.hpp"



/***********************************************************************
  Main
***********************************************************************/

template <> double Precision_traits<double>::eps = 0.0;



int
main(int argc, char** argv)
{
  vsipl init(argc, argv);

  Precision_traits<double>::compute_eps();

  chold_cases<double>          (upper);
  chold_cases<complex<double> >(upper);
  chold_cases<double>          (lower);
  chold_cases<complex<double> >(lower);
}
