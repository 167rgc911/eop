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

auto
half (int n) -> int
{
  return (n / 2);
}

auto
odd (int n) -> int
{
  return (n % 2);
}

constexpr auto
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

constexpr auto
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
  return multiply_acc4 (a, half (n - 1), a + a);
}

int
main ()
{
  std::cout << multiply4 (41, 59) << '\n';
  return 0;
}
