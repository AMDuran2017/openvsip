/* Copyright (c) 2008 by CodeSourcery.  All rights reserved. */

#ifndef KERNELS_HOST_ID1_HPP
#define KERNELS_HOST_ID1_HPP

#include <vsip_csl/ukernel/host/ukernel.hpp>

namespace example
{
class Id1 : public vsip_csl::ukernel::Host_kernel
{
  // Parameters.
  //  - 'tag_type' is used to select the appropriate kernel (via
  //    Task_manager's Task_map)
  //  - in_argc and out_argc describe the number of input and output
  //    streams.
  //  - param_type (inherited) defaults to 'Empty_params'.
public:
  static unsigned int const in_argc  = 1;
  static unsigned int const out_argc = 1;

  // Host-side ukernel object initialization.
  //
  // Streaming pattern divides linear vector into blocks, with minimum
  // size 256, maximum size 1024.  (Blocksize_sdist has an implicit
  // quantum of 16 elements).
  Id1()
    : sp_(vsip_csl::ukernel::Blocksize_sdist(1024, 256))
  {}

  // Host-side compute kernel.  Used if accelerator is not available.
  template <typename View1, typename View2>
  void compute(View1 in, View2 out)
  {
    out = in;
  }


  // Query API:  in_spatt()/out_spatt() allow VSIPL++ to determine
  // streaming pattern for user-kernel.  Since both input and output
  // have same streaming pattern, simply return 'sp'
  vsip_csl::ukernel::Stream_pattern const& in_spatt(vsip::index_type) const
  { return sp_; }

  vsip_csl::ukernel::Stream_pattern const& out_spatt(vsip::index_type) const
  { return sp_; }

private:
  vsip_csl::ukernel::Stream_pattern sp_;	
};

}

#endif
