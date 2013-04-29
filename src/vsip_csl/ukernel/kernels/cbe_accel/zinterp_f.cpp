/* Copyright (c) 2008 by CodeSourcery.  All rights reserved.

   This file is available for license from CodeSourcery, Inc. under the terms
   of a commercial license and under the GPL.  It is not part of the VSIPL++
   reference implementation and is not available under the BSD license.
*/
/** @file    vsip_csl/ukernel/kernels/cbe_accel/zinterp_f.hpp
    @author  Don McCoy
    @date    2008-08-26
    @brief   VSIPL++ Library: User-defined polar to rectangular
               interpolation kernel for SSAR images.
*/

/***********************************************************************
  Included Files
***********************************************************************/

#include <vsip_csl/ukernel/kernels/cbe_accel/zinterp_f.hpp>

typedef Zinterp_kernel kernel_type;

#include <vsip_csl/ukernel/cbe_accel/alf_base.hpp>
