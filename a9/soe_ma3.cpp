/*
 * =====================================================================================
 *
 *       Filename:  soe_ma3.cpp
 *
 *    Description:  from A9 Videos YT; Alex Stepanov and Egyptian
 * Multiplication
 *
 *                  r + na
 *
 *                  strict tail recursive
 *
 *        Version:  1.0
 *        Created:  04/22/24 20:15:49
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
multiply_acc3 (int r, int n, int a) -> int
{
  if (odd (n))
    {
      r = r + a;
      if (n == 1)
        return r;
    }
  n = half (n);
  a = a + a;
  return multiply_acc3 (r, n, a);
}

int
main ()
{
  std::cout << multiply_acc3 (0, 41, 59) << '\n';
  return 0;
}
