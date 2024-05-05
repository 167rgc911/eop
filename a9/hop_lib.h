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

}

template <BinaryInteger I>
auto
stein_gcd (I m, I n) -> I
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

#endif
