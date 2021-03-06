//
// Copyright (c) 2007 by CodeSourcery
// Copyright (c) 2013 Stefan Seefeld
// All rights reserved.
//
// This file is part of OpenVSIP. It is made available under the
// license contained in the accompanying LICENSE.GPL file.

/// Description
///   Benchmark for 2D Convolution.

#include <iostream>

#include <vsip/initfin.hpp>
#include <vsip/support.hpp>
#include <vsip/math.hpp>
#include <vsip/signal.hpp>
#include "benchmark.hpp"

using namespace vsip;

template <support_region_type Supp,
	  typename            T>
struct t_conv2d : Benchmark_base
{
  static length_type const rdec = 1;
  static length_type const cdec = 1;

  char const* what() { return "t_conv2d"; }

  void output_size(
    length_type  rows,   length_type  cols,
    length_type& o_rows, length_type& o_cols)
  {
    if      (Supp == support_full)
    {
      o_rows = ((rows + m_ - 2)/rdec) + 1;
      o_cols = ((cols + n_ - 2)/cdec) + 1;
    }
    else if (Supp == support_same)
    {
      o_rows = ((rows - 1)/rdec) + 1;
      o_cols = ((cols - 1)/cdec) + 1;
    }
    else /* (Supp == support_min) */
    {
      o_rows = ((rows-1)/rdec) - ((m_-1)/rdec) + 1;
      o_cols = ((cols-1)/cdec) - ((n_-1)/rdec) + 1;
    }
  }
  
  float ops_per_point(length_type cols)
  {
    length_type o_rows, o_cols;

    output_size(rows_, cols, o_rows, o_cols);

    float ops = m_ * n_ * o_rows * o_cols *
      (ovxx::ops_count::traits<T>::mul + ovxx::ops_count::traits<T>::add);

    return ops / cols;
  }

  int riob_per_point(length_type) { return -1; }
  int wiob_per_point(length_type) { return -1; }
  int mem_per_point(length_type)  { return 2*sizeof(T); }

  void operator()(length_type cols, length_type loop, float& time)
  {
    length_type o_rows, o_cols;

    output_size(rows_, cols, o_rows, o_cols);

    Matrix<T>   in (rows_, cols, T());
    Matrix<T>   out(o_rows, o_cols);
    Matrix<T>   coeff(m_, n_, T());

    coeff = T(1);

    symmetry_type const       symmetry = nonsym;

    typedef Convolution<const_Matrix, symmetry, Supp, T> conv_type;

    conv_type conv(coeff, Domain<2>(rows_, cols), rdec);

    timer t1;
    for (index_type l=0; l<loop; ++l)
      conv(in, out);
    time = t1.elapsed();
  }

  t_conv2d(length_type rows, length_type m, length_type n)
    : rows_(rows), m_(m), n_(n)
  {}

  void diag()
  {
    // TODO
    // using namespace ovxx::dispatcher;
    // typedef typename Dispatcher<op::conv<2, nonsym, Supp, T> >::backend backend;
    // std::cout << "BE: " << Backend_name<backend>::name() << std::endl;
  }

  length_type rows_;
  length_type m_;
  length_type n_;
};



void
defaults(Loop1P& loop)
{
  loop.loop_start_ = 5000;
  loop.start_ = 4;

  loop.param_["rows"] = "16";
  loop.param_["mn"]   = "0";
  loop.param_["m"]    = "3";
  loop.param_["n"]    = "3";
}



int
benchmark(Loop1P& loop, int what)
{
  typedef complex<float> cf_type;

  length_type rows = atoi(loop.param_["rows"].c_str());
  length_type MN   = atoi(loop.param_["mn"].c_str());
  length_type M    = atoi(loop.param_["m"].c_str());
  length_type N    = atoi(loop.param_["n"].c_str());

  if (MN != 0)
    M = N = MN;

  switch (what)
  {
  case  1: loop(t_conv2d<support_full, float>(rows, M, N)); break;
  case  2: loop(t_conv2d<support_same, float>(rows, M, N)); break;
  case  3: loop(t_conv2d<support_min, float> (rows, M, N)); break;

  // case  4: loop(t_conv1<support_full, cf_type>(loop.user_param_)); break;
  // case  5: loop(t_conv1<support_same, cf_type>(loop.user_param_)); break;
  // case  6: loop(t_conv1<support_min,  cf_type>(loop.user_param_)); break;

  case 0:
    std::cout
      << "conv2d -- 2D convolution\n"
      << "   -1 -- float, support=full\n"
      << "   -2 -- float, support=same\n"
      << "   -3 -- float, support=min\n"
      << "\n"
      << " Parameters:\n"
      << "  -p:rows     ROWS -- rows in input matrix (default 16)\n"
      << "  -p:m        M    -- rows in coefficient matrix (default 3)\n"
      << "  -p:n        N    -- columns in coefficient matrix (default 3)\n"
      << "  -p:mn       MN   -- if not zero, set both M and N to MN (default 0)\n"
      << "  -start      N    -- starting problem size 2^N (default 4, that is 16 points)\n"
      << "  -loop_start N    -- initial number of calibration loops (default 5000)\n"
      ;   

  default:
    return 0;
  }
  return 1;
}
