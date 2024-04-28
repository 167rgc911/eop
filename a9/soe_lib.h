/*
 * =====================================================================================
 *
 *       Filename:  soe_lib.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/23/24 19:00:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (),
 *   Organization:
 *
 * =====================================================================================
 */

#pragma once

#ifndef SOE_LIB_H
#define SOE_LIB_H

#include <cassert>
#include <functional>
#include <numeric>
#include <utility>

#include "concepts.h"

namespace Algo
{

template <Integer N>
auto
half (N n) -> N
{
  return (n >> 1);
}

template <Integer N>
auto
odd (N n) -> bool
{
  return (n & 1);
}

template <Integer N>
auto
even (N n) -> bool
{
  return !(n & 1);
}

template <Integer N, Regular A, SemigroupOperation Op>
// requires (Domain<Op, A>)
auto
power_accumulate_semigroup (A r, A a, N n, Op op) -> A
{
  assert (n >= 0);
  if (n == 0)
    return r;
  while (true)
    {
      if (odd (n))
        {
          r = op (r, a);
          if (n == 1)
            return r;
        }
      n = half (n);
      a = op (a, a);
    }
}

template <Integer N, Regular A, SemigroupOperation Op>
// requires (Domain<Op, A>)
auto
power_semigroup (A a, N n, Op op) -> A
{
  assert (n > 0);
  while (!odd (n))
    {
      a = op (a, a);
      n = half (n);
    }
  if (n == 1)
    return a;
  return power_accumulate_semigroup (a, op (a, a), half (n), op);
}

// AdditiveGroup

template <NoncommutativeAdditiveMonoid T>
auto
identity_element (std::plus<T>) -> T
{
  return T (0);
}

template <AdditiveGroup T>
auto
inverse_operation (std::plus<T>) -> std::negate<T>
{
  return std::negate<T> ();
}

// MultiplicativeGroup

template <MultiplicativeMonoid T>
auto
identity_element (std::multiplies<T>) -> T
{
  return T (1);
}

template <MultiplicativeGroup T>
struct reciprocal : public std::unary_function<T, T>
{
  T
  operator() (const T &x) const
  {
    return T (1) / x;
  }
};

template <MultiplicativeGroup T>
auto
inverse_operation (std::multiplies<T>) -> reciprocal<T>
{
  return reciprocal<T> ();
}

template <typename N> struct multiply_2x2
{
  std::array<N, 4>
  operator() (const std::array<N, 4> &x, const std::array<N, 4> &y)
  {
    return { x[0] * y[0] + x[1] * y[2], x[0] * y[1] + x[1] * y[3],
             x[2] * y[0] + x[3] * y[2], x[2] * y[1] + x[3] * y[3] };
  }
};

template <typename N>
std::array<N, 4>
identity_element (const multiply_2x2<N> &)
{
  return { N (1), N (0), N (0), N (1) };
}

template <Integer N, Regular A, MonoidOperation Op>
// requires (Domain<Op, A>)
auto
power_monoid (A a, N n, Op op) -> A
{
  assert (n >= 0);
  if (n == 0)
    return identity_element (op);
  return power_semigroup (a, n, op);
}

template <Integer N, Regular A, GroupOperation Op>
// requires (Domain<Op, A>)
auto
power_group (A a, N n, Op op) -> A
{
  if (n < 0)
    {
      n = -n;
      a = inverse_operation (op) (a);
    }
  return power_monoid (a, n, op);
}

// sieve

template <Integer N, RandomAccessIterator I>
void
mark_sieve (I fst, I lst, N step)
{
  *fst = false;
  while (lst - fst > step)
    {
      fst += step;
      *fst = false;
    }
}

template <Integer N, RandomAccessIterator I>
void
sift (I fst, N n)
{
  I lst = fst + n;
  std::fill (fst, lst, true);
  N i{ 0 };
  N square{ 3 };
  N step{ 3 };
  while (square < n)
    // invariant: square = 2i(i + 3) + 3, step = 2i + 3
    {
      if (fst[i])
        mark_sieve (fst + square, lst, step);
      ++i;

      square += step;
      step += N (2);
      square += step;
    }
}

// primes

template <Integer N>
auto
divides (const N &i, const N &n) -> bool
{
  return n % i == N (0);
}

template <Integer N>
auto
smallest_divisor (N n) -> N
{
  assert (n > 0);
  if (even (n))
    return N (2);
  for (N i (3); n >= i * i; i += N (2))
    {
      if (divides (i, n))
        return i;
    }
  return n;
}

template <Integer N>
auto
is_prime (const N &n) -> N
{
  return n > N (1) && smallest_divisor (n) == n;
}

template <Integer N> struct modulo_multiply
{
  N modulus;
  N
  operator() (const N &n, const N &m) const
  {
    return (n * m) % modulus;
  }
};

template <Integer N>
auto
identity_element (const modulo_multiply<N> &) -> N
{
  return N (1);
}

template <Integer N>
auto
multiplicative_inverse_fermat (N a, N p) -> N
{
  // precondition: p is prime & a > 0
  // assert(is_prime(p) && a > 0); // possible performance degradation
  return power_monoid (a, p - 2, modulo_multiply<N> ());
}

template <Integer N>
auto
fermat_test (N n, N witness) -> bool
{
  // precondition: 0 < witness < n
  N exp (power_semigroup (witness, n - N (1), modulo_multiply<N> (n)));
  return exp == N (1);
}

template <Integer N>
auto
is_carmichael (N n) -> bool
{
  return false;
}

template <Integer N>
bool
miller_rabin_test (N n, N q, N k, N w)
{
  modulo_multiply<N> op (n);
  N x = power_semigroup (w, q, op);
  if (x == N (1) || x == n - N (1))
    return true;
  for (N i (1); i < k; ++i)
    {
      x = op (x, x);
      if (x == n - N (1))
        return true;
      if (x == N (1))
        return false;
    }
  return false;
}

// RSA
// encode
// power_semigroup(plain_text_block, pub, modulo_multiply<N>(n))
// decode
// power_semigroup(cipher_text_block, prv, modulo_multiply<N>(n))

template <EuclideanDomain N>
std::pair<N, N>
extended_gcd (N a, N b)
{
  if (b == 0)
    return std::make_pair (N (1), a);
  N u (1);
  N v (0);
  while (true)
    {
      N q = a / b;
      a -= q * b; // a = a % b;
      if (a == N (0))
        return std::make_pair (v, b);
      u -= q * v;
      q = b / a;
      b -= q * a; // b = b % a;
      if (b == N (0))
        return std::make_pair (u, a);
      v -= q * u;
    }
}

template <Integer N>
auto
multiplicative_inverse (N a, N n) -> N
{
  std::pair<N, N> p = extended_gcd (a, n);
  if (p.second != N (1))
    return N (0);
  if (p.first < N (0))
    return p.first + n;
  return p.first;
}

}

#endif
