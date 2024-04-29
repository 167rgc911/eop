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

struct num_s
{
  std::vector<int> prime;
  std::vector<int> value;
  int sz;

  num_s (int n) : value (n), prime (n)
  {
    std::iota (value.begin (), value.end (), 3);
    std::iota (prime.begin (), prime.end (), 3);
    sz = n;
    std::cout << "[created] v: " << value.size () << " p: " << prime.size ()
              << '\n';
  }

  void
  display ()
  {
    auto pit = prime.begin ();
    auto vit = value.begin ();
    auto n = prime.size ();
    for (auto i = 0; i < n; ++i)
      {
        if (*pit)
          {
            std::cout << *vit << " : " << std::boolalpha
                      << static_cast<bool> (*pit) << ", ";
          }
        ++pit;
        ++vit;
      }
  }

  void
  sift ()
  {
    // remove evens
    prime.erase (std::remove_if (prime.begin (), prime.end (),
                                 [] (int n) { return Algo::even (n); }),
                 prime.end ());
    value.erase (std::remove_if (value.begin (), value.end (),
                                 [] (int n) { return Algo::even (n); }),
                 value.end ());
    std::cout << "[sift evens] v: " << value.size () << " p: " << prime.size ()
              << '\n';
    Algo::sift (prime.begin (), sz);
  }

  int
  size ()
  {
    return sz;
  }
};

int
main ()
{
  num_s n (200);
  n.sift ();
  n.display ();
  return 0;
}
