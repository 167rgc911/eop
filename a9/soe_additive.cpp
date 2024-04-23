/*
 * =====================================================================================
 *
 *       Filename:  soe_additive.cpp
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
multiply_accumulate_semigroup (A r, N n, A a) -> A
{
  assert (n >= 0);
  while (true)
    {
      if (odd (n))
        {
          r = r + a;
          if (n == 1)
            return r;
        }
      n = half (n);
      a = a + a;
    }
}

template <typename N, typename A>
auto
multiply_semigroup (N n, A a) -> A
{
  assert (n > 0);
  while (!odd (n))
    {
      a = a + a;
      n = half (n);
    }
  if (n == 1)
    return a;
  return multiply_accumulate_semigroup (a, half (n - 1), a + a);
}

template <typename N, typename A>
auto
multiply_monoid (N n, A a) -> A
{
  assert (n >= 0);
  if (n == 0)
    return A(0);
  return multiply_semigroup (n, a);
}

template <typename N, typename A>
auto
multiply_group (N n, A a) -> A
{
  if (n < 0)
    {
      n = -n;
      a = -a;
    }
  return multiply_monoid (n, a);
}

int
main ()
{
  std::cout << multiply_semigroup (41, 59) << '\n';
  std::cout << multiply_group (41, 59) << '\n';
  return 0;
}
