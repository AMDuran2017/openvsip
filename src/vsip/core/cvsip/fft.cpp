/* Copyright (c) 2006 by CodeSourcery.  All rights reserved. */

/** @file    vsip/core/cvsip/fft.cpp
    @author  Stefan Seefeld
    @date    2006-10-16
    @brief   VSIPL++ Library: FFT wrappers and traits to bridge with 
             C-VSIPL.
*/

#include <vsip/core/config.hpp>
#include <vsip/core/cvsip/fft.hpp>
#include <vsip/core/cvsip/block.hpp>
#include <vsip/core/cvsip/view.hpp>
extern "C" {
#include <vsip.h>
}

namespace vsip
{
namespace impl
{
namespace cvsip
{

template <dimension_type D, typename T, int E> struct FFT_traits;

#if VSIP_IMPL_CVSIP_HAVE_FLOAT
template <int E>
struct FFT_traits<1, std::complex<float>, E>
{
  typedef vsip_fft_f fft_type;
  typedef vsip_cvview_f view_type;
  static fft_type *create(vsip_length l, vsip_scalar_f s, unsigned int n)
  {
    return vsip_ccfftop_create_f(l, s, E == -1 ? VSIP_FFT_FWD : VSIP_FFT_INV,
                                 n, VSIP_ALG_SPACE);
  }
  static void destroy(fft_type *fft) { vsip_fft_destroy_f(fft);}
  static void call(fft_type *fft, view_type *input, view_type *output)
  { vsip_ccfftop_f(fft, input, output);}
};

template <>
struct FFT_traits<1, float, -1>
{
  typedef vsip_fft_f fft_type;
  typedef vsip_vview_f real_view;
  typedef vsip_cvview_f complex_view;
  static fft_type *create(vsip_length l, vsip_scalar_f s, unsigned int n)
  { return vsip_rcfftop_create_f(l, s, n, VSIP_ALG_SPACE);}
  static void destroy(fft_type *fft) { vsip_fft_destroy_f(fft);}
  static void call(fft_type *fft, real_view *input, complex_view *output)
  { vsip_rcfftop_f(fft, input, output);}
};

template <>
struct FFT_traits<1, float, 1>
{
  typedef vsip_fft_f fft_type;
  typedef vsip_vview_f real_view;
  typedef vsip_cvview_f complex_view;
  static fft_type *create(vsip_length l, vsip_scalar_f s, unsigned int n)
  { return vsip_crfftop_create_f(l, s, n, VSIP_ALG_SPACE);}
  static void destroy(fft_type *fft) { vsip_fft_destroy_f(fft);}
  static void call(fft_type *fft, complex_view *input, real_view *output)
  { vsip_crfftop_f(fft, input, output);}
};

#endif
#if VSIP_IMPL_CVSIP_HAVE_DOUBLE

template <int E>
struct FFT_traits<1, std::complex<double>, E>
{
  typedef vsip_fft_d fft_type;
  typedef vsip_cvview_d view_type;
  static fft_type *create(vsip_length l, vsip_scalar_d s, unsigned int n)
  {
    return vsip_ccfftop_create_d(l, s, E == -1 ? VSIP_FFT_FWD : VSIP_FFT_INV,
                                 n, VSIP_ALG_SPACE);
  }
  static void destroy(fft_type *fft) { vsip_fft_destroy_d(fft);}
  static void call(fft_type *fft, view_type *input, view_type *output)
  { vsip_ccfftop_d(fft, input, output);}
};

template <>
struct FFT_traits<1, double, -1>
{
  typedef vsip_fft_d fft_type;
  typedef vsip_vview_d real_view;
  typedef vsip_cvview_d complex_view;
  static fft_type *create(vsip_length l, vsip_scalar_d s, unsigned int n)
  { return vsip_rcfftop_create_d(l, s, n, VSIP_ALG_SPACE);}
  static void destroy(fft_type *fft) { vsip_fft_destroy_d(fft);}
  static void call(fft_type *fft, real_view *input, complex_view *output)
  { vsip_rcfftop_d(fft, input, output);}
};

template <>
struct FFT_traits<1, double, 1>
{
  typedef vsip_fft_d fft_type;
  typedef vsip_vview_d real_view;
  typedef vsip_cvview_d complex_view;
  static fft_type *create(vsip_length l, vsip_scalar_d s, unsigned int n)
  { return vsip_crfftop_create_d(l, s, n, VSIP_ALG_SPACE);}
  static void destroy(fft_type *fft) { vsip_fft_destroy_d(fft);}
  static void call(fft_type *fft, complex_view *input, real_view *output)
  { vsip_crfftop_d(fft, input, output);}
};

inline vsip_major 
to_major(int a) 
{ return a == 1 ? VSIP_ROW : VSIP_COL;}

inline vsip_alg_hint 
to_alg_hint(int h) 
{ return h == 0 ? VSIP_ALG_SPACE : h == 1 ? VSIP_ALG_TIME : VSIP_ALG_NOISE;}

#endif

template <dimension_type D, typename I, typename O, int S> class Fft_impl;

template <typename T, int S>
class Fft_impl<1, std::complex<T>, std::complex<T>, S>
  : public fft::Fft_backend<1, std::complex<T>, std::complex<T>, S>
{
  typedef T rtype;
  typedef std::complex<rtype> ctype;
  typedef std::pair<rtype*, rtype*> ztype;
  typedef FFT_traits<1, std::complex<T>, S == fft_fwd ? -1 : 1> traits;

public:
  Fft_impl(Domain<1> const &d, rtype scale, unsigned int n, int /*h*/)
    : impl_(traits::create(d.size(), scale, n))
  {}
  ~Fft_impl() { traits::destroy(impl_);}
  virtual bool supports_scale() { return true;}
  virtual void in_place(ctype *inout, stride_type stride, length_type length)
  {
    View<1, ctype> input(inout, 0, stride, length);
    View<1, ctype, false> output(length);
    traits::call(impl_, input.ptr(), output.ptr());
    input = output;
  }
  virtual void in_place(ztype inout, stride_type stride, length_type length)
  {
    View<1, ctype> input(inout, 0, stride, length);
    View<1, ctype, false> output(length);
    traits::call(impl_, input.ptr(), output.ptr());
    input = output;
  }
  virtual void out_of_place(ctype *in, stride_type in_stride,
			    ctype *out, stride_type out_stride,
			    length_type length)
  {
    View<1, ctype> input(in, 0, in_stride, length);
    View<1, ctype> output(out, 0, out_stride, length);
    traits::call(impl_, input.ptr(), output.ptr());
  }
  virtual void out_of_place(ztype in, stride_type in_stride,
			    ztype out, stride_type out_stride,
			    length_type length)
  {
    View<1, ctype> input(in, 0, in_stride, length);
    View<1, ctype> output(out, 0, out_stride, length);
    traits::call(impl_, input.ptr(), output.ptr());
  }

private:
  typename traits::fft_type *impl_;
};

template <typename T>
class Fft_impl<1, T, std::complex<T>, 0>
  : public fft::Fft_backend<1, T, std::complex<T>, 0>
{
  typedef T rtype;
  typedef std::complex<rtype> ctype;
  typedef std::pair<rtype*, rtype*> ztype;
  typedef FFT_traits<1, T, -1> traits;

public:
  Fft_impl(Domain<1> const &d, rtype scale, unsigned int n, int /*h*/)
    : impl_(traits::create(d.size(), scale, n))
  {}
  ~Fft_impl() { traits::destroy(impl_);}
  virtual bool supports_scale() { return true;}
  virtual void out_of_place(rtype *in, stride_type in_stride,
			    ctype *out, stride_type out_stride,
			    length_type length)
  {
    View<1, rtype> input(in, 0, in_stride, length);
    View<1, ctype> output(out, 0, out_stride, length);
    traits::call(impl_, input.ptr(), output.ptr());
  }
  virtual void out_of_place(rtype *in, stride_type in_stride,
			    ztype out, stride_type out_stride,
			    length_type length)
  {
    View<1, rtype> input(in, 0, in_stride, length);
    View<1, ctype> output(out, 0, out_stride, length);
    traits::call(impl_, input.ptr(), output.ptr());
  }

private:
  typename traits::fft_type *impl_;
};

template <typename T>
class Fft_impl<1, std::complex<T>, T, 0>
  : public fft::Fft_backend<1, std::complex<T>, T, 0>
{
  typedef T rtype;
  typedef std::complex<rtype> ctype;
  typedef std::pair<rtype*, rtype*> ztype;
  typedef FFT_traits<1, T, 1> traits;

public:
  Fft_impl(Domain<1> const &d, rtype scale, unsigned int n, int /*h*/)
    : impl_(traits::create(d.size(), scale, n))
  {}
  ~Fft_impl() { traits::destroy(impl_);}
  virtual bool supports_scale() { return true;}
  virtual void out_of_place(ctype *in, stride_type in_stride,
			    rtype *out, stride_type out_stride,
			    length_type length)
  {
    View<1, ctype> input(in, 0, in_stride, length);
    View<1, rtype> output(out, 0, out_stride, length);
    traits::call(impl_, input.ptr(), output.ptr());
  }
  virtual void out_of_place(ztype in, stride_type in_stride,
			    rtype *out, stride_type out_stride,
			    length_type length)
  {
    View<1, ctype> input(in, 0, in_stride, length);
    View<1, rtype> output(out, 0, out_stride, length);
    traits::call(impl_, input.ptr(), output.ptr());
  }

private:
  typename traits::fft_type *impl_;
};

template <typename I, typename O, int A, int D> class Fftm_impl;

template <typename T, int A, int D>
class Fftm_impl<std::complex<T>, std::complex<T>, A, D>
  : public fft::Fftm_backend<std::complex<T>, std::complex<T>, A, D>
{
  typedef T rtype;
  typedef std::complex<rtype> ctype;
  typedef std::pair<rtype*, rtype*> ztype;
  typedef FFT_traits<1, std::complex<T>, D == fft_fwd ? -1 : 1> traits;

  static int const axis = A == vsip::col ? 0 : 1;

public:
  Fftm_impl(Domain<2> const &dom, rtype scale, unsigned int n, int /*h*/)
    : impl_(traits::create(dom[axis].size(), scale, n)),
      mult_(dom[1-axis].size())
  {}
  ~Fftm_impl() { traits::destroy(impl_);}
  virtual bool supports_scale() { return true;}

  virtual void in_place(ctype *inout,
			stride_type stride_r, stride_type stride_c,
			length_type rows, length_type cols)
  {
    // If the inputs to the Fftm are distributed, the number of FFTs may
    // be less than mult_.
    length_type const n_fft = (axis == 1) ? rows : cols;
    stride_type vect_stride;
    stride_type elem_stride;
    length_type length = 0;
    if (axis == 0)
    {
      vect_stride = stride_c;
      elem_stride = stride_r;
      length = rows;
    }
    else
    {
      vect_stride = stride_r;
      elem_stride = stride_c;
      length = cols;
    }
    View<1, ctype, false> output(length);
    for (length_type i = 0; i != n_fft; ++i)
    {
      View<1, ctype> input(inout, i * vect_stride, elem_stride, length);
      traits::call(impl_, input.ptr(), output.ptr());
      input = output;
    }
  }

  virtual void in_place(ztype inout,
			stride_type stride_r, stride_type stride_c,
			length_type rows, length_type cols)
  {
    // If the inputs to the Fftm are distributed, the number of FFTs may
    // be less than mult_.
    length_type const n_fft = (axis == 1) ? rows : cols;
    stride_type vect_stride;
    stride_type elem_stride;
    length_type length = 0;
    if (axis == 0)
    {
      vect_stride = stride_c;
      elem_stride = stride_r;
      length = rows;
    }
    else
    {
      vect_stride = stride_r;
      elem_stride = stride_c;
      length = cols;
    }
    View<1, ctype, false> output(length);
    for (length_type i = 0; i != n_fft; ++i)
    {
      View<1, ctype> input(inout, i * vect_stride, elem_stride, length);
      traits::call(impl_, input.ptr(), output.ptr());
      input = output;
    }
  }

  virtual void out_of_place(ctype *in,
			    stride_type in_stride_r, stride_type in_stride_c,
			    ctype *out,
			    stride_type out_stride_r, stride_type out_stride_c,
			    length_type rows, length_type cols)
  {
    // If the inputs to the Fftm are distributed, the number of FFTs may
    // be less than mult_.
    length_type const n_fft = (axis == 1) ? rows : cols;
    stride_type in_vect_stride;
    stride_type in_elem_stride;
    stride_type out_vect_stride;
    stride_type out_elem_stride;
    length_type length = 0;
    if (axis == 0)
    {
      in_vect_stride = in_stride_c;
      in_elem_stride = in_stride_r;
      out_vect_stride = out_stride_c;
      out_elem_stride = out_stride_r;
      length = rows;
    }
    else
    {
      in_vect_stride = in_stride_r;
      in_elem_stride = in_stride_c;
      out_vect_stride = out_stride_r;
      out_elem_stride = out_stride_c;
      length = cols;
    }
    for (length_type i = 0; i != n_fft; ++i)
    {
      View<1, ctype> input(in, i * in_vect_stride, in_elem_stride, length);
      View<1, ctype> output(out, i * out_vect_stride, out_elem_stride, length);
      traits::call(impl_, input.ptr(), output.ptr());
    }
  }
  virtual void out_of_place(ztype in,
			    stride_type in_stride_r, stride_type in_stride_c,
			    ztype out,
			    stride_type out_stride_r, stride_type out_stride_c,
			    length_type rows, length_type cols)
  {
    // If the inputs to the Fftm are distributed, the number of FFTs may
    // be less than mult_.
    length_type const n_fft = (axis == 1) ? rows : cols;
    stride_type in_vect_stride;
    stride_type in_elem_stride;
    stride_type out_vect_stride;
    stride_type out_elem_stride;
    length_type length = 0;
    if (axis == 0)
    {
      in_vect_stride = in_stride_c;
      in_elem_stride = in_stride_r;
      out_vect_stride = out_stride_c;
      out_elem_stride = out_stride_r;
      length = rows;
    }
    else
    {
      in_vect_stride = in_stride_r;
      in_elem_stride = in_stride_c;
      out_vect_stride = out_stride_r;
      out_elem_stride = out_stride_c;
      length = cols;
    }
    for (length_type i = 0; i != n_fft; ++i)
    {
      View<1, ctype> input(in, i * in_vect_stride, out_elem_stride, length);
      View<1, ctype> output(out, i * out_vect_stride, out_elem_stride, length);
      traits::call(impl_, input.ptr(), output.ptr());
    }
  }

private:
  typename traits::fft_type *impl_;
  length_type                mult_;
};

template <typename T, int A>
class Fftm_impl<T, std::complex<T>, A, fft_fwd>
  : public fft::Fftm_backend<T, std::complex<T>, A, fft_fwd>
{
  typedef T rtype;
  typedef std::complex<rtype> ctype;
  typedef std::pair<rtype*, rtype*> ztype;
  typedef FFT_traits<1, T, -1> traits;

  static int const axis = A == vsip::col ? 0 : 1;

public:
  Fftm_impl(Domain<2> const &dom, rtype scale, unsigned int n, int /*h*/)
    : impl_(traits::create(dom[axis].size(), scale, n)),
      mult_(dom[1-axis].size())
  {}
  ~Fftm_impl() { traits::destroy(impl_);}
  virtual bool supports_scale() { return true;}

  virtual void out_of_place(rtype *in,
			    stride_type in_stride_r, stride_type in_stride_c,
			    ctype *out,
			    stride_type out_stride_r, stride_type out_stride_c,
			    length_type rows, length_type cols)
  {
    // If the inputs to the Fftm are distributed, the number of FFTs may
    // be less than mult_.
    length_type const n_fft = (axis == 1) ? rows : cols;
    stride_type in_vect_stride;
    stride_type in_elem_stride;
    stride_type out_vect_stride;
    stride_type out_elem_stride;
    length_type length = 0;
    if (axis == 0)
    {
      in_vect_stride = in_stride_c;
      in_elem_stride = in_stride_r;
      out_vect_stride = out_stride_c;
      out_elem_stride = out_stride_r;
      length = rows;
    }
    else
    {
      in_vect_stride = in_stride_r;
      in_elem_stride = in_stride_c;
      out_vect_stride = out_stride_r;
      out_elem_stride = out_stride_c;
      length = cols;
    }
    for (length_type i = 0; i != n_fft; ++i)
    {
      View<1, rtype> input(in, i * in_vect_stride, in_elem_stride, length);
      View<1, ctype> output(out, i * out_vect_stride, out_elem_stride, length/2+1);
      traits::call(impl_, input.ptr(), output.ptr());
    }
  }
  virtual void out_of_place(rtype *in,
			    stride_type in_stride_r, stride_type in_stride_c,
			    ztype out,
			    stride_type out_stride_r, stride_type out_stride_c,
			    length_type rows, length_type cols)
  {
    // If the inputs to the Fftm are distributed, the number of FFTs may
    // be less than mult_.
    length_type const n_fft = (axis == 1) ? rows : cols;
    stride_type in_vect_stride;
    stride_type in_elem_stride;
    stride_type out_vect_stride;
    stride_type out_elem_stride;
    length_type length = 0;
    if (axis == 0)
    {
      in_vect_stride = in_stride_c;
      in_elem_stride = in_stride_r;
      out_vect_stride = out_stride_c;
      out_elem_stride = out_stride_r;
      length = rows;
    }
    else
    {
      in_vect_stride = in_stride_r;
      in_elem_stride = in_stride_c;
      out_vect_stride = out_stride_r;
      out_elem_stride = out_stride_c;
      length = cols;
    }
    for (length_type i = 0; i != n_fft; ++i)
    {
      View<1, rtype> input(in, i * in_vect_stride, in_elem_stride, length);
      View<1, ctype> output(out, i * out_vect_stride, out_elem_stride, length/2+1);
      traits::call(impl_, input.ptr(), output.ptr());
    }
  }

private:
  typename traits::fft_type *impl_;
  length_type                mult_;
};

template <typename T, int A>
class Fftm_impl<std::complex<T>, T, A, fft_inv>
  : public fft::Fftm_backend<std::complex<T>, T, A, fft_inv>
{
  typedef T rtype;
  typedef std::complex<rtype> ctype;
  typedef std::pair<rtype*, rtype*> ztype;
  typedef FFT_traits<1, T, 1> traits;

  static int const axis = A == vsip::col ? 0 : 1;

public:
  Fftm_impl(Domain<2> const &dom, rtype scale, unsigned int n, int /*h*/)
    : impl_(traits::create(dom[axis].size(), scale, n)),
      mult_(dom[1-axis].size())
  {}
  ~Fftm_impl() { traits::destroy(impl_);}
  virtual bool supports_scale() { return true;}

  virtual void out_of_place(ctype* in,
			    stride_type in_stride_r, stride_type in_stride_c,
			    rtype *out,
			    stride_type out_stride_r, stride_type out_stride_c,
			    length_type rows, length_type cols)
  {
    // If the inputs to the Fftm are distributed, the number of FFTs may
    // be less than mult_.
    length_type const n_fft = (axis == 1) ? rows : cols;
    stride_type in_vect_stride;
    stride_type in_elem_stride;
    stride_type out_vect_stride;
    stride_type out_elem_stride;
    length_type length = 0;
    if (axis == 0)
    {
      in_vect_stride = in_stride_c;
      in_elem_stride = in_stride_r;
      out_vect_stride = out_stride_c;
      out_elem_stride = out_stride_r;
      length = rows;
    }
    else
    {
      in_vect_stride = in_stride_r;
      in_elem_stride = in_stride_c;
      out_vect_stride = out_stride_r;
      out_elem_stride = out_stride_c;
      length = cols;
    }
    for (length_type i = 0; i != n_fft; ++i)
    {
      View<1, ctype> input(in, i * in_vect_stride, in_elem_stride, length/2+1);
      View<1, rtype> output(out, i * out_vect_stride, out_elem_stride, length);
      traits::call(impl_, input.ptr(), output.ptr());
    }
  }
  virtual void out_of_place(ztype in,
			    stride_type in_stride_r, stride_type in_stride_c,
			    rtype *out,
			    stride_type out_stride_r, stride_type out_stride_c,
			    length_type rows, length_type cols)
  {
    // If the inputs to the Fftm are distributed, the number of FFTs may
    // be less than mult_.
    length_type const n_fft = (axis == 1) ? rows : cols;
    stride_type in_vect_stride;
    stride_type in_elem_stride;
    stride_type out_vect_stride;
    stride_type out_elem_stride;
    length_type length = 0;
    if (axis == 0)
    {
      in_vect_stride = in_stride_c;
      in_elem_stride = in_stride_r;
      out_vect_stride = out_stride_c;
      out_elem_stride = out_stride_r;
      length = rows;
    }
    else
    {
      in_vect_stride = in_stride_r;
      in_elem_stride = in_stride_c;
      out_vect_stride = out_stride_r;
      out_elem_stride = out_stride_c;
      length = cols;
    }
    for (length_type i = 0; i != n_fft; ++i)
    {
      View<1, ctype> input(in, i * in_vect_stride, in_elem_stride, length/2+1);
      View<1, rtype> output(out, i * out_vect_stride, out_elem_stride, length);
      traits::call(impl_, input.ptr(), output.ptr());
    }
  }

private:
  typename traits::fft_type *impl_;
  length_type                mult_;
};

#define FFT_DEF(D, I, O, S)				 \
template <>                                              \
std::auto_ptr<fft::Fft_backend<D, I, O, S> >	         \
create(Domain<D> const &dom, scalar_of<I>::type scale,   \
       unsigned int n)                                   \
{                                                        \
  return std::auto_ptr<fft::Fft_backend<D, I, O, S> >    \
    (new Fft_impl<D, I, O, S>(dom, scale, n, 0));        \
}

#if defined VSIP_IMPL_FFT_USE_FLOAT && VSIP_IMPL_CVSIP_HAVE_FLOAT
FFT_DEF(1, std::complex<float>, std::complex<float>, fft_fwd)
FFT_DEF(1, std::complex<float>, std::complex<float>, fft_inv)
FFT_DEF(1, float, std::complex<float>, 0)
FFT_DEF(1, std::complex<float>, float, 0)
#endif

#if defined VSIP_IMPL_FFT_USE_DOUBLE && VSIP_IMPL_CVSIP_HAVE_DOUBLE
FFT_DEF(1, std::complex<double>, std::complex<double>, fft_fwd)
FFT_DEF(1, std::complex<double>, std::complex<double>, fft_inv)
FFT_DEF(1, double, std::complex<double>, 0)
FFT_DEF(1, std::complex<double>, double, 0)
#endif

#undef FFT_DEF

#define FFTM_DEF(I, O, A, D)			       \
template <>                                            \
std::auto_ptr<fft::Fftm_backend<I, O, A, D> >	       \
create(Domain<2> const &dom, scalar_of<I>::type scale, \
       unsigned int n)                                 \
{                                                      \
  return std::auto_ptr<fft::Fftm_backend<I, O, A, D> > \
    (new Fftm_impl<I, O, A, D>(dom, scale, n, 0));     \
}

#if defined VSIP_IMPL_FFT_USE_FLOAT && VSIP_IMPL_CVSIP_HAVE_FLOAT
FFTM_DEF(float, std::complex<float>, 0, fft_fwd)
FFTM_DEF(float, std::complex<float>, 1, fft_fwd)
FFTM_DEF(std::complex<float>, float, 0, fft_inv)
FFTM_DEF(std::complex<float>, float, 1, fft_inv)
FFTM_DEF(std::complex<float>, std::complex<float>, 0, fft_fwd)
FFTM_DEF(std::complex<float>, std::complex<float>, 1, fft_fwd)
FFTM_DEF(std::complex<float>, std::complex<float>, 0, fft_inv)
FFTM_DEF(std::complex<float>, std::complex<float>, 1, fft_inv)
#endif

#if defined VSIP_IMPL_FFT_USE_DOUBLE && VSIP_IMPL_CVSIP_HAVE_DOUBLE
FFTM_DEF(double, std::complex<double>, 0, fft_fwd)
FFTM_DEF(double, std::complex<double>, 1, fft_fwd)
FFTM_DEF(std::complex<double>, double, 0, fft_inv)
FFTM_DEF(std::complex<double>, double, 1, fft_inv)
FFTM_DEF(std::complex<double>, std::complex<double>, 0, fft_fwd)
FFTM_DEF(std::complex<double>, std::complex<double>, 1, fft_fwd)
FFTM_DEF(std::complex<double>, std::complex<double>, 0, fft_inv)
FFTM_DEF(std::complex<double>, std::complex<double>, 1, fft_inv)
#endif

#undef FFTM_DEF

} // namespace vsip::impl::cvsip
} // namespace vsip::impl
} // namespace vsip
