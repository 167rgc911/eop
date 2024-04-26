/*
 * =====================================================================================
 *
 *       Filename:  soe_prime.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/26/24 14:10:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc ()
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>

#include "soe_lib.h"

int
main ()
{
  std::cout << is_prime (1) << '\n';
  std::cout << is_prime (3) << '\n';
  std::cout << is_prime (4) << '\n';
  std::cout << is_prime (5) << '\n';
  std::cout << is_prime (127) << '\n';
  std::cout << is_prime (257) << '\n';
  std::cout << is_prime (65537) << '\n';
  std::cout << is_prime (4294967297) << '\n';
  return 0;
}
