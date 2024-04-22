/*
 * =====================================================================================
 *
 *       Filename:  soe_m2.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/22/24 20:29:14
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
      n = half(n);
      a = a + a;
    }
}

constexpr auto
multiply2 (int n, int a) -> int
{
  if (n ==1) return a;
  return multiply_acc4 (a, n - 1, a);
}

int
main ()
{
  std::cout << multiply2 (41, 59) << '\n';
  return 0;
}
