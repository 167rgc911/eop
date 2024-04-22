/*
 * =====================================================================================
 *
 *       Filename:  soe_m0.cpp
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
 *        Version:  1.0
 *        Created:  04/22/24 19:31:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>

constexpr auto
multiply0 (int n, int a) -> int
{
  if (n == 1)
    return a;
  return multiply0 (n - 1, a) + a;
}

int
main ()
{
  std::cout << multiply0 (41, 59) << '\n';
  return 0;
}
