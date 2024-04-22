/*
 * =====================================================================================
 *
 *       Filename:  soe_ma0.cpp
 *
 *    Description:  from A9 Videos YT; Alex Stepanov and Egyptian
 * Multiplication
 *
 *                  r + na
 *
 *        Version:  1.0
 *        Created:  04/22/24 19:57:14
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
multiply_acc0 (int r, int n, int a) -> int
{
  if (n == 1)
    return r + a;
  if (odd (n))
    {
      return multiply_acc0 (r + a, half (n), a + a);
    }
  else
    {
      return multiply_acc0 (r, half (n), a + a);
    }
}

int
main ()
{
  std::cout << multiply_acc0 (0, 41, 59) << '\n';
  return 0;
}
