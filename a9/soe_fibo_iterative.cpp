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

#include <boost/multiprecision/cpp_int.hpp>
namespace mpre = boost::multiprecision;

#include "benchmark/benchmark.h"

#include "soe_lib.h"

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

template <typename N, typename R>
auto
fibo_fast (N n) -> R
{
  if (n == 0)
    return R (0);
  return power_monoid (std::array<R, 4>{ 1, 1, 1, 0 }, N (n - 1),
                       multiply_2x2<R> ())[0];
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
      auto f = fibo_iterative (111);
    }
}

static void
BM_fibf (benchmark::State &state)
{
  // Perform setup here
  for (auto _ : state)
    {
      // This code gets timed
      auto f = fibo_fast<int, int> (111);
    }
}

static void
BM_fibfastlong (benchmark::State &state)
{
  // Perform setup here
  for (auto _ : state)
    {
      // This code gets timed
      auto f = fibo_fast<int, mpre::cpp_int> (1000000);
    }
}

// Register the function as a benchmark
BENCHMARK (BM_fib0);
BENCHMARK (BM_fibi);
BENCHMARK (BM_fibf);
BENCHMARK (BM_fibfastlong);

BENCHMARK_MAIN ();
