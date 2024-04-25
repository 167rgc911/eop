/*
 * =====================================================================================
 *
 *       Filename:  soe_multiplicative.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/23/24 06:26:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <cassert>

#include "soe_lib.h"

template <typename N, typename A>
auto
power_accumulate_semigroup (A r, A a, N n) -> A
{
  assert (n >= 0);
  while (true)
    {
      if (odd (n))
        {
          r = r * a;
          if (n == 1)
            return r;
        }
      n = half (n);
      a = a * a;
    }
}

template <typename N, typename A>
auto
power_semigroup (A a, N n) -> A
{
  assert (n > 0);
  while (!odd (n))
    {
      a = a * a;
      n = half (n);
    }
  if (n == 1)
    return a;
  return power_accumulate_semigroup (a, a * a, half (n));
}

template <typename N, typename A>
auto
power_monoid (A a, N n) -> A
{
  assert (n >= 0);
  if (n == 0)
    return A(1);
  return power_semigroup (a, n);
}

template <typename A>
auto
multiplicative_inverse (A a) -> A
{
  return A(1) / a;
}

template <typename N, typename A>
auto
power_group (A a, N n) -> A
{
  if (n < 0)
    {
      n = -n;
      a = multiplicative_inverse(a);
    }
  return power_monoid (a, n);
}

int
main ()
{
  std::cout << power_semigroup (2, 30) << '\n';
  return 0;
}
