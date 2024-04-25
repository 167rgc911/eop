/*
 * =====================================================================================
 *
 *       Filename:  soe_ma4.cpp
 *
 *    Description:  from A9 Videos YT; Alex Stepanov and Egyptian
 * Multiplication
 *
 *                  r + na
 *
 *                  iterative
 *
 *        Version:  1.0
 *        Created:  04/22/24 20:20:48
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

int
main ()
{
  std::cout << multiply_acc4 (0, 41, 59) << '\n';
  return 0;
}
