/*
 * =====================================================================================
 *
 *       Filename:  hop_lib.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/28/24 22:09:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (), sessyargc.jp@gmail.com
 *   Organization:
 *
 * SPDX-License-Identifier: MIT
 * =====================================================================================
 */

#pragma once

#ifndef HOP_LIB_H
#define HOP_LIB_H

#include "concepts.h"

namespace Algo
{

template <Integer N>
auto
gcm (N a, N b) -> N
{
  if (a == b)
    return a;
  if (b < a)
    return gcm (a - b, b);
  if (a < b)
    return gcm (a, b - a);
}

template <Integer N>
auto
segment_remainder (N a, N b) -> N
{
  while (b < a)
    a = a - b;
  return a;
}

template <Integer N>
auto
segment_gcm (N a, N b) -> N
{
  while (a != b)
    {
      a = segment_remainder (a, b);
      std::swap (a, b);
    }
  return a;
}

template <Integer N>
auto
fast_segment_remainder (N a, N b) -> N
{
  if (a <= b)
    return a;
  if (a - b <= b)
    return a - b;
  a = fast_segment_remainder (a, b + b);
  if (a <= b)
    return a;
  return a - b;
}

template <Integer N>
auto
fast_segment_remainder1 (N a, N b) -> N
{
  // precondition: b != 0
  if (a < b)
    return a;
  if (a - b < b)
    return a - b;
  a = fast_segment_remainder1 (a, b + b);
  if (a < b)
    return a;
  return a - b;
}

template <Integer N>
auto
fast_segment_gcm (N a, N b) -> N
{
  while (a != b)
    {
      a = fast_segment_remainder (a, b);
      std::swap (a, b);
    }
  return a;
}

template <Integer N>
auto
largest_doubling (N a, N b) -> N
{
  // precondition: b != 0
  while (b <= a - b)
    b = b + b;
  return b;
}

template <Integer N>
auto
remainder (N a, N b) -> N
{
  // precondition: b != 0
  if (a < b)
    return a;
  N c = largest_doubling (a, b);
  a = a - c;
  while (c != b)
    {
      c = half (c);
      if (c <= a)
        a = a - c;
    }
  return a;
}

template <Integer N, Integer I>
auto
quotient (N a, N b) -> I
{
  // precondition: b > 0
  if (a < b)
    return I (0);
  N c = largest_doubling (a, b);
  I n (1);
  a = a - c;
  while (c != b)
    {
      c = half (c);
      n = n + n;
      if (c <= a)
        {
          a = a - c;
          n = n + 1;
        }
    }
  return n;
}

template <Integer N, Integer I>
std::pair<N, I>
quotient_remainder (N a, N b)
{
  // precondition: b > 0
  if (a < b)
    return std::make_pair (I (0), a);
  N c = largest_doubling (a, b);
  I n (1);
  a = a - c;
  while (c != b)
    {
      c = half (c);
      n = n + n;
      if (c <= a)
        {
          a = a - c;
          n = n + 1;
        }
    }
  return std::make_pair (n, a);
}

template <Integer N>
auto
remainder_fibonacci (N a, N b) -> N
{
  // precondition: b > 0
  if (a < b)
    return a;
  N c = b;
  do
    {
      N tmp = c;
      c = b + c;
      b = tmp;
    }
  while (a >= c);
  do
    {
      if (a >= b)
        a = a - b;
      N tmp = c - b;
      c = b;
      b = tmp;
    }
  while (b < c);
  return a;
}

template <Integer N, Integer I>
auto
quotient_fibonacci (N a, N b) -> I
{
  return a;
}

template <Integer N, Integer I>
std::pair<N, I>
quotient_remainder_fibonacci (N a, N b)
{
  return std::make_pair (a, b);
}

template <Integer N>
auto
gcm_remainder (N a, N b) -> N
{
  while (b != N (0))
    {
      a = remainder (a, b);
      std::swap (a, b);
    }
  return a;
}

template <Integer N>
auto
gcd (N a, N b) -> N
{
  while (b != N (0))
    {
      a = a % b;
      std::swap (a, b);
    }
  return a;
}

template <InputIterator I, Semiring R>
auto
polynomial_value (I f, I l, R x) -> R
{
  if (f == l)
    return R (0);
  R sum (*f);
  while (++f != l)
    {
      sum = sum * x;
      sum = sum + *f;
    }
  return sum;
}

/*
 * Journey 2; page 102
polynomial<real> gcd_stevin (polynomial<real> m, polynomial<real> n)
{
  while (n != polynomial<real> (0))
    {
      polynomial<real> t = remainder (m,  n);
      m = n;
      n = t;
    }
  return m;
}
 */

/*
 * Journey 2; page 102
complex<integer> gcd_gauss (complex<integer> m, complex<integer> n)
{
  while (real(n) != 0 || imag(n) != 0) {
    complex<integer> t = m % n;
    m = n;
    n = t;
  }
  return m;
}
 */

template <EuclideanDomain R>
auto
gcd_noether (R m, R n) -> R
{
  while (n != R (0))
    {
      R t = m % n;
      m = n;
      n = t;
    }
  return m;
}

/*
 * Journey 2; page 195-198
 */
template <BinaryInteger I>
auto
stein_gcd0 (I m, I n) -> I
{
  if (m < I (0))
    m = -m;
  if (n < I (0))
    n = -n;
  if (m == I (0))
    return n;
  if (n == I (0))
    return m;

  // m > 0 ^ n > 0
  I d_m = 0;
  while (even (m))
    {
      m >>= 1;
      ++d_m;
    }

  I d_n = 0;
  while (even (n))
    {
      n >>= 1;
      ++d_n;
    }

  // odd (m) ^ odd (n)
  while (m != n)
    {
      if (n > m)
        swap (n, m);
      m -= n;

      do
        m >>= 1;
      while (even (m));
    }

  // m = n
  return m << min (d_m, d_n);
}

/*
 * Journey 2; page 215-218
 * need to implement page 212
 */
/*
template <SteinDomain I>
auto
stein_gcd (I m, I n) -> I
{
  if (m == I (0))
    return n;
  if (n == I (0))
    return m;

  // m > 0 ^ n > 0
  I d_m = 0;
  while (divisible_by_smallest_prime (m))
    {
      m = divide_by_smallest_prime (m);
      ++d_m;
    }

  I d_n = 0;
  while (divisible_by_smallest_prime (n))
    {
      n = divide_by_smallest_prime (n);
      ++d_n;
    }

  // odd (m) ^ odd (n)
  while (! is_associate (m, n))
    {
      if (norm (n) > norm (m))
        swap (n, m);
      m = reduce_associate_remainders (n, m);

      do
        m = divide_by_smallest_prime (m);
      while (divisible_by_smallest_prime (m));
    }

  // m = n
  I p = smallest_prime<I>();
  return m * power (p, min (d_m, d_n));
}
 */

/*
 * Journey 2; page 253
 */
template <EuclideanDomain N>
auto
extended_gcd1 (N a, N b) -> std::pair<N, N>
{
  N x0 (1);
  N x1 (0);
  while (b != N (0))
    {
      // compute new r and x
      std::pair<N, N> p = quotient_remainder (a, b);
      N x2 = x1 - p.first * x0;
      // shift r and x
      x0 = x1;
      x1 = x2;
      a = b;
      b = p.second;
    }
  return std::make_pair (x0, a);
}

template <ForwardIterator I0, ForwardIterator I1>
auto
swap_ranges (I0 f0, I0 l0, I1 f1) -> I1
{
  while (f0 != l0)
    std::swap (*f0++, *f1++);
  return f1;
}

template <ForwardIterator I0, ForwardIterator I1>
auto
swap_ranges (I0 f0, I0 l0, I1 f1, I1 l1) -> std::pair<I0, I1>
{
  while (f0 != l0 && f1 != l1)
    {
      std::swap (*f0++, *f1++);
    }
  return std::pair<I0, I1> (f0, f1);
}

template <ForwardIterator I0, ForwardIterator I1, Integer N>
auto
swap_ranges (I0 f0, I1 f1, N n) -> std::pair<I0, I1>
{
  while (n != N (0))
    {
      std::swap (*f0++, *f1++);
      --n;
    }
  return std::pair<I0, I1> (f0, f1);
}

template <ForwardIterator I>
void
gries_mills_rotate (I f, I m, I l)
{
  // u = distance (f, m) &&v = distance (m, l)
  if (f == m || m == l)
    return; // u == 0 || v == 0
  std::pair<I, I> p = swap_ranges (f, m, m, l);
  while (p.first != m || p.second != l)
    {
      if (p.first == m)
        { // u < v
          f = m;
          m = p.second; // v = v - u
        }
      else
        {              // v < u
          f = p.first; // u = u - v
        }
      p = swap_ranges (f, m, m, l);
    }
  return; // u == v
}
}

#endif
