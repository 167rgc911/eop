/*
 * =====================================================================================
 *
 *       Filename:  soe_lib.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/25/24 19:23:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (),
 *   Organization:
 *
 * SPDX-License-Identifier: MIT
 * =====================================================================================
 */

#include <cassert>
#include <functional>
#include <iostream>

#include "soe_lib.h"

int
main ()
{
  std::cout << power_semigroup (2, 30, std::plus<int> ()) << '\n';
  std::cout << power_semigroup (2, 30, std::multiplies<int> ()) << '\n';
  return 0;
}
