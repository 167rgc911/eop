/*
 * =====================================================================================
 *
 *       Filename:  soe_fibo_iterative.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/23/24 19:44:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>
#include <utility> // std::pair

#include "benchmark/benchmark.h"

auto
fib0 (int n) -> int
{
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;
  return fib0 (n - 1) + fib0 (n - 2);
}

auto
fibo_iterative (int n) -> int
{
  if (n == 0)
    return 0;
  auto v = std::make_pair (0, 1);
  for (auto i = 1; i < n; ++i)
    v = std::make_pair (v.second, v.first + v.second);
  return v.second;
}

// int
// main ()
//{
//   std::cout << fibo_iterative (5) << '\n';
//   return 0;
// }

static void
BM_fib0 (benchmark::State &state)
{
  // Perform setup here
  for (auto _ : state)
    {
      // This code gets timed
      auto f = fib0 (25);
    }
}

static void
BM_fibi (benchmark::State &state)
{
  // Perform setup here
  for (auto _ : state)
    {
      // This code gets timed
      auto f = fibo_iterative (25);
    }
}

// Register the function as a benchmark
BENCHMARK (BM_fib0);
BENCHMARK (BM_fibi);

BENCHMARK_MAIN ();
