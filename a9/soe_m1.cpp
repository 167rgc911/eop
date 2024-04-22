/*
 * =====================================================================================
 *
 *       Filename:  soe_m1.cpp
 *
 *    Description:  from A9 Videos YT; Alex Stepanov and Egyptian
 * Multiplication
 *
 *                  distributivity
 *
 *                    (n + m)a = na + ma
 *
 *                    (n + 1)a = na + a
 *
 *                  halving n
 *
 *                                  n   n
 *                    even(n)   n = - + -
 *                                  2   2
 *
 *                                  n - 1   n - 1
 *                     odd(n)   n = ----- + ----- + 1
 *                                    2       2
 *
 *        Version:  1.0
 *        Created:  04/22/24 19:35:12
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
odd (int n) -> bool
{
  return (n & 1);
}

auto
multiply1 (int n, int a) -> int
{
  if (n == 1)
    return a;
  int result = multiply1 (half (n), a + a);
  if (odd (n))
    result = result + a;
  return result;
}

int
main ()
{
  std::cout << multiply1 (41, 59) << '\n';
  return 0;
}
