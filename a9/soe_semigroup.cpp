/*
 * =====================================================================================
 *
 *       Filename:  soe_semigroup.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/23/24 06:15:44
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

auto
half (int n) -> int
{
  return (n >> 1);
}

auto
odd (int n) -> bool
{
  return (n & 1);
}

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

int
main ()
{
  std::cout << multiply_semigroup (41, 59) << '\n';
  return 0;
}
