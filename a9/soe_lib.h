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

#define Integer typename

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

#define NoncommutativeAdditiveSemigroup typename
#define NoncommutativeAdditiveMonoid    typename
#define AdditiveGroup                   typename
#define MultiplicativeMonoid            typename
#define MultiplicativeGroup             typename

#endif
