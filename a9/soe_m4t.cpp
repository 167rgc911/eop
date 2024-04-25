/*
 * =====================================================================================
 *
 *       Filename:  soe_m4t.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/22/24 20:57:50
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
multiply_acc4 (A r, N n, A a) -> A
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
multiply4 (N n, A a) -> A
{
  assert (n > 0);
  while (!odd (n))
    {
      a = a + a;
      n = half (n);
    }
  if (n == 1)
    return a;
  // even(n - 1) => n - 1 != 1
  return multiply_acc4 (a, half (n), a + a);
}

int
main ()
{
  std::cout << multiply4 (41, 59) << '\n';
  std::cout << multiply4 (13, 30) << '\n';
  std::cout << multiply4 (10, 20) << '\n';
  std::cout << multiply4 (1, 1) << '\n';
  std::cout << multiply4 (1, 0) << '\n';
  return 0;
}
