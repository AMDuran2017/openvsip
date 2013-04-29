/* Copyright (c) 2005, 2006 by CodeSourcery.  All rights reserved.

   This file is available for license from CodeSourcery, Inc. under the terms
   of a commercial license and under the GPL.  It is not part of the VSIPL++
   reference implementation and is not available under the BSD license.
*/
/** @file    vsip/opt/pas/assign_eb.hpp
    @author  Jules Bergmann
    @date    2005-06-22
    @brief   VSIPL++ Library: Parallel assignment algorithm for PAS.
                              (with early binding).
*/

#ifndef VSIP_IMPL_PAR_ASSIGN_PAS_EB_HPP
#define VSIP_IMPL_PAR_ASSIGN_PAS_EB_HPP

#if VSIP_IMPL_REF_IMPL
# error "vsip/opt files cannot be used as part of the reference impl."
#endif

/***********************************************************************
  Included Files
***********************************************************************/

#include <vsip/support.hpp>
#include <vsip/core/parallel/services.hpp>
#include <vsip/core/profile.hpp>
#include <vsip/domain.hpp>
#include <vsip/core/view_traits.hpp>
#include <vsip/core/parallel/assign.hpp>
#include <vsip/opt/pas/param.hpp>

#define VERBOSE 0



/***********************************************************************
  Declarations
***********************************************************************/

namespace vsip
{

namespace impl
{

template <dimension_type Dim,
	  typename       T1,
	  typename       T2,
	  typename       Block1,
	  typename       Block2>
class Par_assign<Dim, T1, T2, Block1, Block2, Pas_assign_eb>
  : Compile_time_assert<is_split_block<Block1>::value ==
                        is_split_block<Block2>::value>
{
  static dimension_type const dim = Dim;

  typedef typename Distributed_local_block<Block1>::type dst_local_block;
  typedef typename Distributed_local_block<Block2>::type src_local_block;

  typedef typename view_of<dst_local_block>::type dst_lview_type;
  typedef typename view_of<src_local_block>::const_type src_lview_type;


  // Constructor.
public:
  Par_assign(typename view_of<Block1>::type dst,
	     typename view_of<Block2>::const_type src)
    : dst_      (dst),
      src_      (src.block()),
      ready_sem_index_(0),
      done_sem_index_ (0)
  {
    long rc;
    long const reserved_flags = 0;
    profile::Scope<profile::par>
      scope("Par_assign<Pas_assign_eb>-cons");

    PAS_id src_pset = src_.block().map().impl_ll_pset();
    PAS_id dst_pset = dst_.block().map().impl_ll_pset();
    PAS_id all_pset;

    long* src_pnums;
    long* dst_pnums;
    long* all_pnums;
    long  src_npnums;
    long  dst_npnums;
    unsigned long  all_npnums;

    long  max_components = Block1::components > Block2::components ?
                           Block1::components : Block2::components;

    rc = pas_pset_get_pnums_list(src_pset, &src_pnums, &src_npnums);
    VSIP_IMPL_CHECK_RC(rc, "pas_pset_get_pnums_list");
    rc = pas_pset_get_pnums_list(dst_pset, &dst_pnums, &dst_npnums);
    VSIP_IMPL_CHECK_RC(rc, "pas_pset_get_pnums_list");
    all_pnums = pas_pset_combine(src_pnums, dst_pnums, PAS_PSET_UNION,
				 &all_npnums);
    rc = pas_pset_create(all_pnums, 0, &all_pset);
    VSIP_IMPL_CHECK_RC(rc, "pas_pset_create");

    free(src_pnums);
    free(dst_pnums);
    free(all_pnums);


    // Set default values if temporary buffer is not necessary
    // Either not in pset, or local_nbytes == 0
    move_desc_ = NULL;
    pull_flags_ = 0;


    // Setup tmp buffer
    if (pas_pset_is_member(all_pset))
    {
      long                 local_nbytes;

      rc = pas_distribution_calc_tmp_local_nbytes(
	src_.block().impl_ll_dist(),
	dst_.block().impl_ll_dist(),
	pas::Pas_datatype<T1>::value(),
	0,
	&local_nbytes);
      VSIP_IMPL_CHECK_RC(rc, "pas_distribution_calc_tmp_local_nbytes");
#if VERBOSE
      std::cout << "[" << local_processor() << "] "
		<< "local_nbytes = " << local_nbytes << std::endl;
#endif

      if (local_nbytes > 0)
      {
	rc = pas_pbuf_create(
	  0, 
	  all_pset,
	  local_nbytes,
	  0,			// Default alignment
	  max_components,
	  PAS_ZERO,
	  &tmp_pbuf_);
	VSIP_IMPL_CHECK_RC(rc, "pas_pbuf_create");
	
	rc = pas_move_desc_create(reserved_flags, &move_desc_);
	VSIP_IMPL_CHECK_RC(rc, "pas_move_desc_create");

	rc = pas_move_desc_set_tmp_pbuf(move_desc_, tmp_pbuf_, 0);
	VSIP_IMPL_CHECK_RC(rc, "pas_move_desc_set_tmp_pbuf");

	pull_flags_ = PAS_WAIT;
      }
    }

    // Setup transfer
    if (pas_pset_is_member(src_pset))
    {
      rc = pas_push_setup(
		    move_desc_,
		    src_.block().impl_ll_pbuf(),
		    src_.block().impl_ll_dist(),
		    dst_.block().impl_ll_pbuf(),
		    dst_.block().impl_ll_dist(),
		    pas::Pas_datatype<T1>::value(),
		    done_sem_index_,
		    pull_flags_ | VSIP_IMPL_PAS_XFER_ENGINE |
		    VSIP_IMPL_PAS_SEM_GIVE_AFTER,
		    &xfer_handle_); 
      VSIP_IMPL_CHECK_RC(rc, "pas_push_setup");
    }

    rc = pas_pset_close(all_pset, 0);
    VSIP_IMPL_CHECK_RC(rc, "pas_pset_close");
  }

  ~Par_assign()
  {
    long const reserved_flags = 0;
    long rc;

    PAS_id src_pset = src_.block().map().impl_ll_pset();

    if (pas_pset_is_member(src_pset))
    {
      rc = pas_xfer_free(xfer_handle_);
      VSIP_IMPL_CHECK_RC(rc, "pas_xfer_free");
    }

    if (move_desc_ != NULL)
    {
      rc = pas_move_desc_destroy(move_desc_, reserved_flags);
      VSIP_IMPL_CHECK_RC(rc, "pas_move_desc_destroy");
      
      rc = pas_pbuf_destroy(tmp_pbuf_, reserved_flags);
      VSIP_IMPL_CHECK_RC(rc, "pas_pbuf_destroy");
    }
  }


  // Invoke the parallel assignment
public:
  void operator()()
  {
    long rc;

    PAS_id src_pset = src_.block().map().impl_ll_pset();
    PAS_id dst_pset = dst_.block().map().impl_ll_pset();

    // -------------------------------------------------------------------
    // Tell source that dst is ready
    if (pas_pset_is_member(dst_pset))
    {
      // assert that subblock is not emtpy
#if VERBOSE
      std::cout << "[" << local_processor() << "] "
		<< "give start" << std::endl << std::flush;
#endif

      pas::semaphore_give(src_pset, ready_sem_index_);

#if VERBOSE
      std::cout << "[" << local_processor() << "] "
		<< "give done" << std::endl << std::flush;
#endif
    }


    // -------------------------------------------------------------------
    // Push when dst is ready
    if (pas_pset_is_member(src_pset))
    {
      pas::semaphore_take(dst_pset, ready_sem_index_);

#if VERBOSE
      std::cout << "[" << local_processor() << "] "
		<< "push start" << std::endl << std::flush;
#endif
      rc = pas_xfer_start(
		    xfer_handle_,
		    PAS_WAIT,
		    NULL);
      VSIP_IMPL_CHECK_RC(rc, "pas_xfer_start");
#if VERBOSE
      std::cout << "[" << local_processor() << "] "
		<< "push done" << std::endl << std::flush;
#endif
    }

    // -------------------------------------------------------------------
    // Wait for push to complete.
    if (pas_pset_is_member(dst_pset))
      pas::semaphore_take(src_pset, done_sem_index_);
  }


  // Private member data.
private:
  typename view_of<Block1>::type dst_;
  typename view_of<Block2>::const_type src_;

  PAS_move_desc_handle  move_desc_;
  PAS_pbuf_handle       tmp_pbuf_;
  PAS_xfer_setup_handle xfer_handle_;
  long                  pull_flags_;
  long                  ready_sem_index_;
  long                  done_sem_index_;
};

/***********************************************************************
  Definitions
***********************************************************************/


#undef VERBOSE

} // namespace vsip::impl

} // namespace vsip

#endif // VSIP_IMPL_PAR_ASSIGN_PAS_EB_HPP
