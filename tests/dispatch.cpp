//
// Copyright (c) 2005, 2006 by CodeSourcery
// Copyright (c) 2013 Stefan Seefeld
// All rights reserved.
//
// This file is part of OpenVSIP. It is made available under the
// license contained in the accompanying LICENSE.GPL file.

#include <ovxx/dispatch.hpp>
#include <ovxx/dispatcher/diagnostics.hpp>
#include "test.hpp"

template <typename T> void test_dispatch();


// backends
struct A;
struct B;
struct C;
struct D;

///////////////////////// O1 tests /////////////////////////////////////
struct O1;

namespace ovxx
{
namespace dispatcher
{

template <>
struct List<O1>
{
  typedef make_type_list<A, B, C, D>::type type;
};

template <>
struct Signature<O1>
{
  typedef void(type)(int &, int);
};

template <>
struct Evaluator<O1, A>
{
  static bool const ct_valid = true;
  static char const *name() { return "A Evaluator";}
  static bool rt_valid(int &, int) { return false;}
  static void exec(int &o, int i) { o = i + 'A';}
};

template <>
struct Evaluator<O1, B>
{
  static bool const ct_valid = true;
  static char const *name() { return "B Evaluator";}
  static bool rt_valid(int &, int) { return true;}
  static void exec(int &o, int i) { o = i + 'B';}
};
} // namespace ovxx::dispatcher
} // namespace ovxx

template <>
void
test_dispatch<O1>()
{
  // Test: Evaluator<O1, A> disqualifies at runtime, so 'B' should win.
  int value = 0;
  ovxx::dispatch<O1, void, int &, int>(value, 5);
  test_assert(value == 5 + 'B');
}

///////////////////////// O2 tests /////////////////////////////////////
struct O2;

namespace ovxx
{
namespace dispatcher
{
template <>
struct List<O2>
{
  typedef make_type_list<A, B, C, D>::type type;
};

template <>
struct Signature<O2>
{
  typedef int(type)(int);
};

// The A backend gives correct results for even numbers.
template <>
struct Evaluator<O2, A>
{
  static bool const ct_valid = true;
  static bool rt_valid(int i) { return !(i % 2);}
  static int exec(int i) { return 2 * (i / 2);}
};

// The B backend gives correct results for odd numbers.
template <>
struct Evaluator<O2, B>
{
  static bool const ct_valid = true;
  static bool rt_valid(int i) { return i % 2;}
  static int exec(int i) { return 2 * (i / 2) + 1;}
};
} // namespace ovxx::dispatcher
} // namespace ovxx

template <>
void
test_dispatch<O2>()
{
  // Test: Evaluator<O2, A> is valid for even input, Evaluator<O2, B> for odd.
  test_assert((ovxx::dispatch<O2, int>(4) == 4));
  test_assert((ovxx::dispatch<O2, int>(5) == 5));
}

///////////////////////// O3 tests /////////////////////////////////////
// Test compile-time dispatch
struct O3;

namespace ovxx
{
namespace dispatcher
{

template <>
struct List<O3>
{
  typedef make_type_list<A, B, C, D>::type type;
};

template <>
struct Evaluator<O3, B>
{
  static bool const ct_valid = true;
  // Make the tag its own type, for this test.
  typedef B backend_type;
};
template <>
struct Evaluator<O3, C, float>
{
  static bool const ct_valid = true;
  // Make the tag its own type, for this test.
  typedef C backend_type;
};
template <>
struct Evaluator<O3, D, double>
{
  static bool const ct_valid = true;
  // Make the tag its own type, for this test.
  typedef D backend_type;
};

} // namespace ovxx::dispatcher
} // namespace ovxx

using namespace vsip;

// Provide an alternative way to map type T to backend B,
// for testing.
template <typename B, typename T> 
struct backend_available
{
  static bool const value = false;
};

template <>
struct backend_available<C, float>
{
  static bool const value = true;
};

template <>
struct backend_available<D, double>
{
  static bool const value = true;
};

template <>
void
test_dispatch<O3>()
{
  namespace dispatcher = ovxx::dispatcher;
  // Test: Evaluator<O3, float> is ct-valid, while Evaluator<O3, double> is not.
  test_assert((backend_available<dispatcher::Dispatcher<O3, float>::backend,
                                 float>::value));
  test_assert((!backend_available<dispatcher::Dispatcher<O3, float>::backend,
                                  double>::value));
  test_assert((!backend_available<dispatcher::Dispatcher<O3, double>::backend,
                                  float>::value));
  test_assert((backend_available<dispatcher::Dispatcher<O3, double>::backend,
                                 double>::value));
  test_assert((dispatcher::is_operation_supported<O3, float>::value == true));
  test_assert((dispatcher::is_operation_supported<O3, int>::value == false));
}

///////////////////////// O4 tests /////////////////////////////////////
// Same as O3, but with additional template parameters.
template <typename A, typename B> struct O4;

namespace ovxx
{
namespace dispatcher
{

template <typename S, typename T>
struct List<O4<S, T> >
{
  typedef make_type_list<A, B, C, D>::type type;
};

template <typename S, typename T>
struct Evaluator<O4<S, T>, B>
{
  static bool const ct_valid = false;
  // Make the tag its own type, for this test.
  typedef B backend_type;
};
template <typename T>
struct Evaluator<O4<T, float>, C>
{
  static bool const ct_valid = true;
  // Make the tag its own type, for this test.
  typedef C backend_type;
};
template <typename T>
struct Evaluator<O4<T, double>, D>
{
  static bool const ct_valid = true;
  // Make the tag its own type, for this test.
  typedef D backend_type;
};

} // namespace ovxx::dispatcher
} // namespace ovxx

template <template <typename, typename> class O>
void
test_dispatch()
{
  namespace dispatcher = ovxx::dispatcher;
  // Test: Evaluator<O4<T, float> > is ct-valid, while Evaluator<O4<T, double> > is not.
  test_assert((backend_available<typename dispatcher::Dispatcher<O<short, float> >::backend,
                                 float>::value));
  test_assert((!backend_available<typename dispatcher::Dispatcher<O<char, float> >::backend,
                                  double>::value));
  test_assert((!backend_available<typename dispatcher::Dispatcher<O<int, double> >::backend,
                                  float>::value));
  test_assert((backend_available<typename dispatcher::Dispatcher<O<float, double> >::backend,
                                 double>::value));
}

int main(int, char **)
{
  test_dispatch<O1>();
  test_dispatch<O2>();
  test_dispatch<O3>();
  test_dispatch<O4>();
}
