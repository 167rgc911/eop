/*
 * =====================================================================================
 *
 *       Filename:  soe_sift.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/26/24 09:49:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc ()
 *   Organization:
 *
 * =====================================================================================
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

#include "soe_lib.h"

int
main()
{
  std::vector<int> v(55);
  std::iota(v.begin(), v.end(), 0);
  sift<int, std::vector<int>::iterator> (v.begin(), 55);

  auto x = 0;
  for (auto i : v)
    {
      std::cout << x  << " : " << i << '\n';
      x++;
    }
  return 0;
}
