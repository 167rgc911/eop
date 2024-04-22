/*
 * =====================================================================================
 *
 *       Filename:  soe_ma1.cpp
 *
 *    Description:  from A9 Videos YT; Alex Stepanov and Egyptian
 * Multiplication
 *
 *                  r + na
 *
 *        Version:  1.0
 *        Created:  04/22/24 20:05:44
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
  return (n >> 1);
}

auto
odd (int n) -> bool
{
  return (n & 1);
}

constexpr auto
multiply_acc1 (int r, int n, int a) -> int
{
  if (n == 1)
    return r + a;
  if (odd (n))
    {
      r = r + a;
    }
  return multiply_acc1 (r, half (n), a + a);
}

int
main ()
{
  std::cout << multiply_acc1 (0, 41, 59) << '\n';
  return 0;
}
