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

/*
 * Journey 2; page 272
 */
template <ForwardIterator I0, ForwardIterator I1>
auto
swap_ranges (I0 f0, I0 l0, I1 f1) -> I1
{
  while (f0 != l0)
    std::swap (*f0++, *f1++);
  return f1;
}

/*
 * Journey 2; page 275
 */
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

/*
 * Journey 2; page 277
 */
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

/*
 * Journey 2; page 278
 */
template <ForwardIterator I0, ForwardIterator I1, Integer N>
auto
swap_ranges_n (I0 f0, I1 f1, N n0, N n1) -> std::pair<I0, I1>
{
  return std::pair<I0, I1> (f0, f1);
}

/*
 * Journey 2; page 286
 */
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

/*
 * Journey 2; page 293
 */
template <ForwardIterator I>
auto
rotate_unguarded (I f, I m, I l, I m1) -> I
{
  // assert (f != m && m != l)
  std::pair<I, I> p = swap_ranges (f, m, m, l);
  while (p.first != m || p.second != l)
    {
      f = p.first;
      if (m == f)
        m = p.second;
      p = swap_ranges (f, m, m, l);
    }
  return m1;
}

/*
 * Journey 2; page 294
 */
template <ForwardIterator I>
auto
rotate (I f, I m, I l) -> I
{
  if (f == m)
    return l;
  if (m == l)
    return f;
  std::pair<I, I> p = swap_ranges (f, m, m, l);
  while (p.first != m || p.second != l)
    {
      if (p.second == l)
        return rotate_unguarded (p.first, m, l, p.first);
      f = m;
      m = p.second;
      p = swap_ranges (f, m, m, l);
    }
  return m;
}

/*
 * Journey 2; page 296
 */
template <ForwardIterator I, Transformation F>
void
cycle_from (I i, F from)
{
  typedef typename std::iterator_traits<I>::value_type V;
  V tmp = *i;
  I start = i;
  for (I j = from (i); j != start; j = from (j))
    {
      *i = *j;
      i = j;
    }
  *i = tmp;
}

/*
 * Journey 2; page 297
 */
template <RandomAccessIterator I>

struct rotate_transform
{
  typedef typename std::iterator_traits<I>::difference_type N;
  N plus;
  N minus;
  I m1;
  rotate_transform (I f, I m, I l)
      : plus (m - f), minus (m - l), m1 (f + (l - m))
  {
  }
  I
  operator() (I i) const
  {
    return i + ((i < m1) ? plus : minus);
  }
};

/*
 * Journey 2; page 298
 */
template <RandomAccessIterator I>
auto
rotate2 (I f, I m, I l) -> I
{
  if (f == m)
    return l;
  if (m == l)
    return f;
  typedef typename std::iterator_traits<I>::difference_type N;
  N d = gcd (m - f, l - m);
  rotate_transform<I> rotator (f, m, l);
  while (d-- > 0)
    cycle_from (f + d, rotator);
  return rotator.m1;
}

/*
 * Journey 2; page 299
 */
template <BidirectionalIterator I>
void
three_reverse_rotate (I f, I m, I l)
{
  reverse (f, m);
  reverse (m, l);
  reverse (f, l);
}

/*
 * Journey 2; page 301
 */
template <BidirectionalIterator I>
auto
reverse_until (I f, I m, I l) -> std::pair<I, I>
{
  while (f != m && m != l)
    std::swap (*f++, *--l);
  return std::pair<I, I> (f, l);
}

/*
 * Journey 2; page 302
 */
template <BidirectionalIterator I>
auto
rotate3 (I f, I m, I l, std::bidirectional_iterator_tag) -> I
{
  reverse (f, m);
  reverse (m, l);
  std::pair<I, I> p = reverse_until (f, m, l);
  reverse (p.first, p.second);
  if (m == p.first)
    return p.second;
  return p.first;
}

/*
 * Journey 2; page 303
 */
template <ForwardIterator I>
auto
rotate4 (I f, I m, I l) -> I
{
  typename std::iterator_traits<I>::iterator_category c;
  return rotate3 (f, m, l, c);
}

/*
 * Journey 2; page 304
 */
template <BidirectionalIterator I>
void
reverse5 (I f, I l, std::bidirectional_iterator_tag)
{
  while (f != l && f != --l)
    std::swap (*f++, *l);
}

/*
 * Journey 2; page 306
 */
template <BidirectionalIterator I, Integer N>
void
reverse_n (I f, I l, N n)
{
  n >>= 1;
  while (n-- > N (0))
    {
      std::swap (*f++, *--l);
    }
}

/*
 * Journey 2; page 308
 */
template <RandomAccessIterator I>
void
reverse6 (I f, I l, std::random_access_iterator_tag)
{
  reverse_n (f, l, l - f);
}

/*
 * Journey 2; page 309
 */
template <ForwardIterator I, BinaryInteger N>
auto
reverse_recursive (I f, N n) -> I
{
  if (n == 0)
    return f;
  if (n == 1)
    return ++f;
  N h = n >> 1;
  I m = reverse_recursive (f, h);
  std::advance (m, n & 1);
  I l = reverse_recursive (m, h);
  swap_ranges_n (f, m, h);
  return l;
}

/*
 * Journey 2; page 310
 */
template <ForwardIterator I>
void
reverse7 (I f, I l, std::forward_iterator_tag)
{
  reverse_recursive (f, distance (f, l));
}

/*
 * Journey 2; page 311
 */
template <ForwardIterator I>
void
reverse8 (I f, I l)
{
  typename std::iterator_traits<I>::iterator_category c;
  reverse (f, l, c);
}

/*
 * Journey 2; page 314
 */
template <ForwardIterator I, Integer N, BidirectionalIterator B>
auto
reverse_n_with_buffer (I f, N n, B buffer) -> I
{
  return reverse_copy (buffer, copy_n (f, n, buffer), f);
}

/*
 * Journey 2; page 315
 */
template <BidirectionalIterator I, OutputIterator O>
auto
reverse_copy (I f, I l, O r) -> O
{
  while (f != l)
    *r++ = *--l;
  return r;
}

/*
 * Journey 2; page 317
 */
template <ForwardIterator I, Integer N, BidirectionalIterator B>
auto
reverse_n_adaptive (I f, N n, B b, N b_n) -> I
{
  if (n == N (0))
    return f;
  if (n == N (1))
    return ++f;
  if (n <= b_n)
    return reverse_n_with_buffer (f, n, b);
  N h = n >> 1;
  I m = reverse_n_adaptive (f, h, b, b_n);
  advance (m, n & 1);
  I l = reverse_n_adaptive (m, h, b, b_n);
  swap_ranges_n (f, m, h);
  return l;
}

}

#endif
