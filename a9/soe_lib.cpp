/*
 * =====================================================================================
 *
 *       Filename:  soe_lib.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/25/24 19:23:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <cassert>
#include <functional>
#include <iostream>

#include "soe_lib.h"

template <typename N, typename A, typename Op>
auto
power_accumulate_semigroup (A r, A a, N n, Op op) -> A
{
  assert (n >= 0);
  if (n == 0)
    return r;
  while (true)
    {
      if (odd (n))
        {
          r = op (r, a);
          if (n == 1)
            return r;
        }
      n = half (n);
      a = op (a, a);
    }
}

template <typename N, typename A, typename Op>
auto
power_semigroup (A a, N n, Op op) -> A
{
  assert (n > 0);
  while (!odd (n))
    {
      a = op (a, a);
      n = half (n);
    }
  if (n == 1)
    return a;
  return power_accumulate_semigroup (a, op (a, a), half (n), op);
}

template <typename N, typename A, typename Op>
auto
power_monoid (A a, N n, Op op) -> A
{
  assert (n >= 0);
  if (n == 0)
    return identity_element (op);
  return power_semigroup (a, n, op);
}

template <typename T>
auto
identity_element (std::plus<T>) -> T
{
  return T (0);
}

template <typename T>
auto
identity_element (std::multiplies<T>) -> T
{
  return T (1);
}

template <typename T>
auto
inverse_operation (std::plus<T>) -> std::negate<T>
{
  return std::negate<T> ();
}

template <typename T> struct reciprocal : public std::unary_function<T, T>
{
  T
  operator() (const T &x) const
  {
    return T (1) / x;
  }
};

template <typename T>
auto
inverse_operation (std::multiplies<T>) -> reciprocal<T>
{
  return reciprocal<T> ();
}

template <typename N, typename A, typename Op>
auto
power_group (A a, N n, Op op) -> A
{
  if (n < 0)
    {
      n = -n;
      a = inverse_operation (op) (a);
    }
  return power_monoid (a, n, op);
}

int
main ()
{
  std::cout << power_semigroup (2, 30, std::plus<int> ()) << '\n';
  std::cout << power_semigroup (2, 30, std::multiplies<int> ()) << '\n';
  return 0;
}
