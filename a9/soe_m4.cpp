/*
 * =====================================================================================
 *
 *       Filename:  soe_m4.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/22/24 20:37:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>

#include "soe_lib.h"

auto
multiply_acc4 (int r, int n, int a) -> int
{
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

auto
multiply4 (int n, int a) -> int
{
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
