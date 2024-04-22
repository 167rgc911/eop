/*
 * =====================================================================================
 *
 *       Filename:  soe_ma2.cpp
 *
 *    Description:  from A9 Videos YT; Alex Stepanov and Egyptian Multiplication
 *
 *                  r + na
 *
 *        Version:  1.0
 *        Created:  04/22/24 20:09:19
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
multiply_acc2 (int r, int n, int a) -> int
{
  if (odd (n))
    {
      r = r + a;
      if (n == 1)
        return r;
    }
  return multiply_acc2 (r, half (n), a + a);
}

int
main ()
{
  std::cout << multiply_acc2 (0, 41, 59) << '\n';
  return 0;
}
