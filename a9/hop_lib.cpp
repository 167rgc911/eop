/*
 * =====================================================================================
 *
 *       Filename:  hop_lib.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  05/05/24 09:40:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (), sessyargc.jp@gmail.com
 *   Organization:
 *
 * SPDX-License-Identifier: MIT
 * =====================================================================================
 */

#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

#include "hop_lib.h"
#include "soe_lib.h"

int
main ()
{
  std::vector<int> n (10);
  std::iota (n.begin (), n.end (), 69);
  [n] () {
    for (auto v : n)
      std::cout << v << ", ";
  }();

  auto m = std::distance (n.begin (), n.end ()) / 2;

  std::cout << '\n';

  Algo::gries_mills_rotate (n.begin (), n.begin () + m, n.end ());
  [n] () {
    for (auto v : n)
      std::cout << v << ", ";
  }();

  std::cout << '\n';

  std::rotate (n.begin (), n.begin () + m, n.end ());
  [n] () {
    for (auto v : n)
      std::cout << v << ", ";
  }();

  std::cout << '\n';

  return 0;
}
