/*
 * libecb
 *
 * Copyright (©) 2009-2011 Marc Alexander Lehmann
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modifica-
 * tion, are permitted provided that the following conditions are met:
 *
 *   1.  Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *
 *   2.  Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MER-
 * CHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPE-
 * CIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTH-
 * ERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ECB_H
#define ECB_H

#define ECB_GCC_VERSION(major,minor) (__GNUC__ > (major) || (__GNUC__ == (major) && __GNUC_MINOR__ >= (minor)))

#if ECB_GCC_VERSION(3,1)
# define ecb_attribute(attrlist)        __attribute__(attrlist)
# define ecb_is_constant(c)             __builtin_constant_p (c)
# define ecb_expect(expr,value)         __builtin_expect ((expr),(value))
# define ecb_prefetch(addr,rw,locality) __builtin_prefetch (addr, rw, locality)
#else
# define ecb_attribute(attrlist)
# define ecb_is_constant(c)             0
# define ecb_expect(expr,value)         (expr)
# define ecb_prefetch(addr,rw,locality)
#endif

/* no emulation for ecb_decltype */
#if ECB_GCC_VERSION(4,5)
# define ecb_decltype(x) __decltype(x)
#elif ECB_GCC_VERSION(3,0)
# define ecb_decltype(x) typeof(x)
#endif

#define ecb_noinline ecb_attribute ((noinline))
#define ecb_noreturn ecb_attribute ((noreturn))
#define ecb_unused   ecb_attribute ((unused))
#define ecb_const    ecb_attribute ((const))
#define ecb_pure     ecb_attribute ((pure))
#define ecb_hot      ecb_attribute ((hot))	// 4.3
#define ecb_cold     ecb_attribute ((cold))	// 4.3

#if ECB_GCC_VERSION(4,5)
# define ecb_unreachable() __builtin_unreachable ()
#else
 // this seems to work fine, but gcc always emits a warning for it :/
 static inline void ecb_unreachable () ecb_attribute ((noreturn));
 static inline void ecb_unreachable () { }
#endif

// put into ifs if you are very sure that the expression
// is mostly true or mosty false. note that these return
// booleans, not the expression.
#define ecb_expect_false(expr) ecb_expect ((expr) ? 1 : 0, 0)
#define ecb_expect_true(expr)  ecb_expect ((expr) ? 1 : 0, 1)

// try to tell the compiler that some condition is definitely true
#define ecb_assume(cond) do { if (!(cond)) unreachable (); } while (0)

// count trailing zero bits and count # of one bits
#if ECB_GCC_VERSION(3,4)
static inline int ecb_ctz      (unsigned int x) { return __builtin_ctz      (x); }
static inline int ecb_popcount (unsigned int x) { return __builtin_popcount (x); }
#else
static int ecb_ctz (unsigned int x) ecb_const
{
  int r = 0;

  x &= -x; // this isolates the lowest bit

  if (x & 0xaaaaaaaa) r +=  1;
  if (x & 0xcccccccc) r +=  2;
  if (x & 0xf0f0f0f0) r +=  4;
  if (x & 0xff00ff00) r +=  8;
  if (x & 0xffff0000) r += 16;

  return r;
}

static int ecb_popcount (unsigned int x) ecb_const
{
  x -=  (x >> 1) & 0x55555555;
  x  = ((x >> 2) & 0x33333333) + (x & 0x33333333);
  x  = ((x >> 4) + x) & 0x0f0f0f0f;
  x *= 0x01010101;

  return x >> 24;
}
#endif

#endif

