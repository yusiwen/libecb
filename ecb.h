/*
 * libecb - http://software.schmorp.de/pkg/libecb
 *
 * Copyright (©) 2009-2015,2018-2021 Marc Alexander Lehmann <libecb@schmorp.de>
 * Copyright (©) 2011 Emanuele Giaquinta
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
 *
 * Alternatively, the contents of this file may be used under the terms of
 * the GNU General Public License ("GPL") version 2 or any later version,
 * in which case the provisions of the GPL are applicable instead of
 * the above. If you wish to allow the use of your version of this file
 * only under the terms of the GPL and not to allow others to use your
 * version of this file under the BSD license, indicate your decision
 * by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL. If you do not delete the
 * provisions above, a recipient may use your version of this file under
 * either the BSD or the GPL.
 */

#ifndef ECB_H
#define ECB_H

/* 16 bits major, 16 bits minor */
#define ECB_VERSION 0x0001000c

#include <string.h> /* for memcpy */

#if defined (_WIN32) && !defined (__MINGW32__)
  typedef   signed char   int8_t;
  typedef unsigned char  uint8_t;
  typedef   signed char   int_fast8_t;
  typedef unsigned char  uint_fast8_t;
  typedef   signed short  int16_t;
  typedef unsigned short uint16_t;
  typedef   signed int    int_fast16_t;
  typedef unsigned int   uint_fast16_t;
  typedef   signed int    int32_t;
  typedef unsigned int   uint32_t;
  typedef   signed int    int_fast32_t;
  typedef unsigned int   uint_fast32_t;
  #if __GNUC__
    typedef   signed long long int64_t;
    typedef unsigned long long uint64_t;
  #else /* _MSC_VER || __BORLANDC__ */
    typedef   signed __int64   int64_t;
    typedef unsigned __int64   uint64_t;
  #endif
  typedef  int64_t  int_fast64_t;
  typedef uint64_t uint_fast64_t;
  #ifdef _WIN64
    #define ECB_PTRSIZE 8
    typedef uint64_t uintptr_t;
    typedef  int64_t  intptr_t;
  #else
    #define ECB_PTRSIZE 4
    typedef uint32_t uintptr_t;
    typedef  int32_t  intptr_t;
  #endif
#else
  #include <inttypes.h>
  #if (defined INTPTR_MAX ? INTPTR_MAX : ULONG_MAX) > 0xffffffffU
    #define ECB_PTRSIZE 8
  #else
    #define ECB_PTRSIZE 4
  #endif
#endif

#define ECB_GCC_AMD64 (__amd64 || __amd64__ || __x86_64 || __x86_64__)
#define ECB_MSVC_AMD64 (_M_AMD64 || _M_X64)

#ifndef ECB_OPTIMIZE_SIZE
  #if __OPTIMIZE_SIZE__
    #define ECB_OPTIMIZE_SIZE 1
  #else
    #define ECB_OPTIMIZE_SIZE 0
  #endif
#endif

/* work around x32 idiocy by defining proper macros */
#if ECB_GCC_AMD64 || ECB_MSVC_AMD64
  #if _ILP32
    #define ECB_AMD64_X32 1
  #else
    #define ECB_AMD64 1
  #endif
#endif

#if ECB_PTRSIZE >= 8 || ECB_AMD64_X32
  #define ECB_64BIT_NATIVE 1
#else
  #define ECB_64BIT_NATIVE 0
#endif

/* many compilers define _GNUC_ to some versions but then only implement
 * what their idiot authors think are the "more important" extensions,
 * causing enormous grief in return for some better fake benchmark numbers.
 * or so.
 * we try to detect these and simply assume they are not gcc - if they have
 * an issue with that they should have done it right in the first place.
 */
#if !defined __GNUC_MINOR__ || defined __INTEL_COMPILER || defined __SUNPRO_C || defined __SUNPRO_CC || defined __llvm__ || defined __clang__
  #define ECB_GCC_VERSION(major,minor) 0
#else
  #define ECB_GCC_VERSION(major,minor) (__GNUC__ > (major) || (__GNUC__ == (major) && __GNUC_MINOR__ >= (minor)))
#endif

#define ECB_CLANG_VERSION(major,minor) (__clang_major__ > (major) || (__clang_major__ == (major) && __clang_minor__ >= (minor)))

#if __clang__ && defined __has_builtin
  #define ECB_CLANG_BUILTIN(x) __has_builtin (x)
#else
  #define ECB_CLANG_BUILTIN(x) 0
#endif

#if __clang__ && defined __has_extension
  #define ECB_CLANG_EXTENSION(x) __has_extension (x)
#else
  #define ECB_CLANG_EXTENSION(x) 0
#endif

#define ECB_CPP   (__cplusplus+0)
#define ECB_CPP11 (__cplusplus >= 201103L)
#define ECB_CPP14 (__cplusplus >= 201402L)
#define ECB_CPP17 (__cplusplus >= 201703L)

#if ECB_CPP
  #define ECB_C            0
  #define ECB_STDC_VERSION 0
#else
  #define ECB_C            1
  #define ECB_STDC_VERSION __STDC_VERSION__
#endif

#define ECB_C99   (ECB_STDC_VERSION >= 199901L)
#define ECB_C11   (ECB_STDC_VERSION >= 201112L)
#define ECB_C17   (ECB_STDC_VERSION >= 201710L)

#if ECB_CPP
  #define ECB_EXTERN_C extern "C"
  #define ECB_EXTERN_C_BEG ECB_EXTERN_C {
  #define ECB_EXTERN_C_END }
#else
  #define ECB_EXTERN_C extern
  #define ECB_EXTERN_C_BEG
  #define ECB_EXTERN_C_END
#endif

/*****************************************************************************/

/* ECB_NO_THREADS - ecb is not used by multiple threads, ever */
/* ECB_NO_SMP     - ecb might be used in multiple threads, but only on a single cpu */

#if ECB_NO_THREADS
  #define ECB_NO_SMP 1
#endif

#if ECB_NO_SMP
  #define ECB_MEMORY_FENCE do { } while (0)
#endif

/* http://www-01.ibm.com/support/knowledgecenter/SSGH3R_13.1.0/com.ibm.xlcpp131.aix.doc/compiler_ref/compiler_builtins.html */
#if __xlC__ && ECB_CPP
  #include <builtins.h>
#endif

#if 1400 <= _MSC_VER
  #include <intrin.h> /* fence functions _ReadBarrier, also bit search functions _BitScanReverse */
#endif

#ifndef ECB_MEMORY_FENCE
  #if ECB_GCC_VERSION(2,5) || defined __INTEL_COMPILER || (__llvm__ && __GNUC__) || __SUNPRO_C >= 0x5110 || __SUNPRO_CC >= 0x5110
    #define ECB_MEMORY_FENCE_RELAXED __asm__ __volatile__ ("" : : : "memory")
    #if __i386 || __i386__
      #define ECB_MEMORY_FENCE         __asm__ __volatile__ ("lock; orb $0, -1(%%esp)" : : : "memory")
      #define ECB_MEMORY_FENCE_ACQUIRE __asm__ __volatile__ (""                        : : : "memory")
      #define ECB_MEMORY_FENCE_RELEASE __asm__ __volatile__ (""                        : : : "memory")
    #elif ECB_GCC_AMD64
      #define ECB_MEMORY_FENCE         __asm__ __volatile__ ("mfence"   : : : "memory")
      #define ECB_MEMORY_FENCE_ACQUIRE __asm__ __volatile__ (""         : : : "memory")
      #define ECB_MEMORY_FENCE_RELEASE __asm__ __volatile__ (""         : : : "memory")
    #elif __powerpc__ || __ppc__ || __powerpc64__ || __ppc64__
      #define ECB_MEMORY_FENCE         __asm__ __volatile__ ("sync"     : : : "memory")
    #elif defined __ARM_ARCH_2__ \
      || defined __ARM_ARCH_3__  || defined __ARM_ARCH_3M__  \
      || defined __ARM_ARCH_4__  || defined __ARM_ARCH_4T__  \
      || defined __ARM_ARCH_5__  || defined __ARM_ARCH_5E__  \
      || defined __ARM_ARCH_5T__ || defined __ARM_ARCH_5TE__ \
      || defined __ARM_ARCH_5TEJ__
      /* should not need any, unless running old code on newer cpu - arm doesn't support that */
    #elif defined __ARM_ARCH_6__  || defined __ARM_ARCH_6J__  \
       || defined __ARM_ARCH_6K__ || defined __ARM_ARCH_6ZK__ \
       || defined __ARM_ARCH_6T2__
      #define ECB_MEMORY_FENCE         __asm__ __volatile__ ("mcr p15,0,%0,c7,c10,5" : : "r" (0) : "memory")
    #elif defined __ARM_ARCH_7__  || defined __ARM_ARCH_7A__  \
       || defined __ARM_ARCH_7R__ || defined __ARM_ARCH_7M__
      #define ECB_MEMORY_FENCE         __asm__ __volatile__ ("dmb"      : : : "memory")
    #elif __aarch64__
      #define ECB_MEMORY_FENCE         __asm__ __volatile__ ("dmb ish"  : : : "memory")
    #elif (__sparc || __sparc__) && !(__sparc_v8__ || defined __sparcv8)
      #define ECB_MEMORY_FENCE         __asm__ __volatile__ ("membar #LoadStore | #LoadLoad | #StoreStore | #StoreLoad" : : : "memory")
      #define ECB_MEMORY_FENCE_ACQUIRE __asm__ __volatile__ ("membar #LoadStore | #LoadLoad"                            : : : "memory")
      #define ECB_MEMORY_FENCE_RELEASE __asm__ __volatile__ ("membar #LoadStore             | #StoreStore")
    #elif defined __s390__ || defined __s390x__
      #define ECB_MEMORY_FENCE         __asm__ __volatile__ ("bcr 15,0" : : : "memory")
    #elif defined __mips__
      /* GNU/Linux emulates sync on mips1 architectures, so we force its use */
      /* anybody else who still uses mips1 is supposed to send in their version, with detection code. */
      #define ECB_MEMORY_FENCE         __asm__ __volatile__ (".set mips2; sync; .set mips0" : : : "memory")
    #elif defined __alpha__
      #define ECB_MEMORY_FENCE         __asm__ __volatile__ ("mb"       : : : "memory")
    #elif defined __hppa__
      #define ECB_MEMORY_FENCE         __asm__ __volatile__ (""         : : : "memory")
      #define ECB_MEMORY_FENCE_RELEASE __asm__ __volatile__ ("")
    #elif defined __ia64__
      #define ECB_MEMORY_FENCE         __asm__ __volatile__ ("mf"       : : : "memory")
    #elif defined __m68k__
      #define ECB_MEMORY_FENCE         __asm__ __volatile__ (""         : : : "memory")
    #elif defined __m88k__
      #define ECB_MEMORY_FENCE         __asm__ __volatile__ ("tb1 0,%%r0,128" : : : "memory")
    #elif defined __sh__
      #define ECB_MEMORY_FENCE         __asm__ __volatile__ (""         : : : "memory")
    #endif
  #endif
#endif

#ifndef ECB_MEMORY_FENCE
  #if ECB_GCC_VERSION(4,7)
    /* see comment below (stdatomic.h) about the C11 memory model. */
    #define ECB_MEMORY_FENCE         __atomic_thread_fence (__ATOMIC_SEQ_CST)
    #define ECB_MEMORY_FENCE_ACQUIRE __atomic_thread_fence (__ATOMIC_ACQUIRE)
    #define ECB_MEMORY_FENCE_RELEASE __atomic_thread_fence (__ATOMIC_RELEASE)
    #undef ECB_MEMORY_FENCE_RELAXED
    #define ECB_MEMORY_FENCE_RELAXED __atomic_thread_fence (__ATOMIC_RELAXED)

  #elif ECB_CLANG_EXTENSION(c_atomic)
    /* see comment below (stdatomic.h) about the C11 memory model. */
    #define ECB_MEMORY_FENCE         __c11_atomic_thread_fence (__ATOMIC_SEQ_CST)
    #define ECB_MEMORY_FENCE_ACQUIRE __c11_atomic_thread_fence (__ATOMIC_ACQUIRE)
    #define ECB_MEMORY_FENCE_RELEASE __c11_atomic_thread_fence (__ATOMIC_RELEASE)
    #undef ECB_MEMORY_FENCE_RELAXED
    #define ECB_MEMORY_FENCE_RELAXED __c11_atomic_thread_fence (__ATOMIC_RELAXED)

  #elif ECB_GCC_VERSION(4,4) || defined __INTEL_COMPILER || defined __clang__
    #define ECB_MEMORY_FENCE         __sync_synchronize ()
  #elif _MSC_VER >= 1500 /* VC++ 2008 */
    /* apparently, microsoft broke all the memory barrier stuff in Visual Studio 2008... */
    #pragma intrinsic(_ReadBarrier,_WriteBarrier,_ReadWriteBarrier)
    #define ECB_MEMORY_FENCE         _ReadWriteBarrier (); MemoryBarrier()
    #define ECB_MEMORY_FENCE_ACQUIRE _ReadWriteBarrier (); MemoryBarrier() /* according to msdn, _ReadBarrier is not a load fence */
    #define ECB_MEMORY_FENCE_RELEASE _WriteBarrier (); MemoryBarrier()
  #elif _MSC_VER >= 1400 /* VC++ 2005 */
    #pragma intrinsic(_ReadBarrier,_WriteBarrier,_ReadWriteBarrier)
    #define ECB_MEMORY_FENCE         _ReadWriteBarrier ()
    #define ECB_MEMORY_FENCE_ACQUIRE _ReadWriteBarrier () /* according to msdn, _ReadBarrier is not a load fence */
    #define ECB_MEMORY_FENCE_RELEASE _WriteBarrier ()
  #elif defined _WIN32
    #include <WinNT.h>
    #define ECB_MEMORY_FENCE         MemoryBarrier () /* actually just xchg on x86... scary */
  #elif __SUNPRO_C >= 0x5110 || __SUNPRO_CC >= 0x5110
    #include <mbarrier.h>
    #define ECB_MEMORY_FENCE         __machine_rw_barrier  ()
    #define ECB_MEMORY_FENCE_ACQUIRE __machine_acq_barrier ()
    #define ECB_MEMORY_FENCE_RELEASE __machine_rel_barrier ()
    #define ECB_MEMORY_FENCE_RELAXED __compiler_barrier ()
  #elif __xlC__
    #define ECB_MEMORY_FENCE         __sync ()
  #endif
#endif

#ifndef ECB_MEMORY_FENCE
  #if ECB_C11 && !defined __STDC_NO_ATOMICS__
    /* we assume that these memory fences work on all variables/all memory accesses, */
    /* not just C11 atomics and atomic accesses */
    #include <stdatomic.h>
    #define ECB_MEMORY_FENCE         atomic_thread_fence (memory_order_seq_cst)
    #define ECB_MEMORY_FENCE_ACQUIRE atomic_thread_fence (memory_order_acquire)
    #define ECB_MEMORY_FENCE_RELEASE atomic_thread_fence (memory_order_release)
  #endif
#endif

#ifndef ECB_MEMORY_FENCE
  #if !ECB_AVOID_PTHREADS
    /*
     * if you get undefined symbol references to pthread_mutex_lock,
     * or failure to find pthread.h, then you should implement
     * the ECB_MEMORY_FENCE operations for your cpu/compiler
     * OR provide pthread.h and link against the posix thread library
     * of your system.
     */
    #include <pthread.h>
    #define ECB_NEEDS_PTHREADS 1
    #define ECB_MEMORY_FENCE_NEEDS_PTHREADS 1

    static pthread_mutex_t ecb_mf_lock = PTHREAD_MUTEX_INITIALIZER;
    #define ECB_MEMORY_FENCE do { pthread_mutex_lock (&ecb_mf_lock); pthread_mutex_unlock (&ecb_mf_lock); } while (0)
  #endif
#endif

#if !defined ECB_MEMORY_FENCE_ACQUIRE && defined ECB_MEMORY_FENCE
  #define ECB_MEMORY_FENCE_ACQUIRE ECB_MEMORY_FENCE
#endif

#if !defined ECB_MEMORY_FENCE_RELEASE && defined ECB_MEMORY_FENCE
  #define ECB_MEMORY_FENCE_RELEASE ECB_MEMORY_FENCE
#endif

#if !defined ECB_MEMORY_FENCE_RELAXED && defined ECB_MEMORY_FENCE
  #define ECB_MEMORY_FENCE_RELAXED ECB_MEMORY_FENCE /* very heavy-handed */
#endif

/*****************************************************************************/

#if ECB_CPP
  #define ecb_inline static inline
#elif ECB_GCC_VERSION(2,5)
  #define ecb_inline static __inline__
#elif ECB_C99
  #define ecb_inline static inline
#else
  #define ecb_inline static
#endif

#if ECB_GCC_VERSION(3,3)
  #define ecb_restrict __restrict__
#elif ECB_C99
  #define ecb_restrict restrict
#else
  #define ecb_restrict
#endif

typedef int ecb_bool;

#define ECB_CONCAT_(a, b) a ## b
#define ECB_CONCAT(a, b) ECB_CONCAT_(a, b)
#define ECB_STRINGIFY_(a) # a
#define ECB_STRINGIFY(a) ECB_STRINGIFY_(a)
#define ECB_STRINGIFY_EXPR(expr) ((expr), ECB_STRINGIFY_ (expr))

/* This marks larger functions that do not neccessarily need to be inlined */
/* The idea is to possibly compile the header twice, */
/* once exposing only the declarations, another time to define external functions */
/* TODO: possibly static would be best for these at the moment? */
#define ecb_function_ ecb_inline

#if ECB_GCC_VERSION(3,1) || ECB_CLANG_VERSION(2,8)
  #define ecb_attribute(attrlist)        __attribute__ (attrlist)
#else
  #define ecb_attribute(attrlist)
#endif

#if ECB_GCC_VERSION(3,1) || ECB_CLANG_BUILTIN(__builtin_constant_p)
  #define ecb_is_constant(expr)          __builtin_constant_p (expr)
#else
  /* possible C11 impl for integral types
  typedef struct ecb_is_constant_struct ecb_is_constant_struct;
  #define ecb_is_constant(expr)          _Generic ((1 ? (struct ecb_is_constant_struct *)0 : (void *)((expr) - (expr)), ecb_is_constant_struct *: 0, default: 1)) */

  #define ecb_is_constant(expr)          0
#endif

#if ECB_GCC_VERSION(3,1) || ECB_CLANG_BUILTIN(__builtin_expect)
  #define ecb_expect(expr,value)         __builtin_expect ((expr),(value))
#else
  #define ecb_expect(expr,value)         (expr)
#endif

#if ECB_GCC_VERSION(3,1) || ECB_CLANG_BUILTIN(__builtin_prefetch)
  #define ecb_prefetch(addr,rw,locality) __builtin_prefetch (addr, rw, locality)
#else
  #define ecb_prefetch(addr,rw,locality)
#endif

/* no emulation for ecb_decltype */
#if ECB_CPP11
  // older implementations might have problems with decltype(x)::type, work around it
  template<class T> struct ecb_decltype_t { typedef T type; };
  #define ecb_decltype(x) ecb_decltype_t<decltype (x)>::type
#elif ECB_GCC_VERSION(3,0) || ECB_CLANG_VERSION(2,8)
  #define ecb_decltype(x) __typeof__ (x)
#endif

#if _MSC_VER >= 1300
  #define ecb_deprecated __declspec (deprecated)
#else
  #define ecb_deprecated ecb_attribute ((__deprecated__))
#endif

#if _MSC_VER >= 1500
  #define ecb_deprecated_message(msg) __declspec (deprecated (msg))
#elif ECB_GCC_VERSION(4,5)
  #define ecb_deprecated_message(msg) ecb_attribute ((__deprecated__ (msg))
#else
  #define ecb_deprecated_message(msg) ecb_deprecated
#endif

#if _MSC_VER >= 1400
  #define ecb_noinline __declspec (noinline)
#else
  #define ecb_noinline ecb_attribute ((__noinline__))
#endif

#define ecb_unused     ecb_attribute ((__unused__))
#define ecb_const      ecb_attribute ((__const__))
#define ecb_pure       ecb_attribute ((__pure__))

#if ECB_C11 || __IBMC_NORETURN
  /* http://www-01.ibm.com/support/knowledgecenter/SSGH3R_13.1.0/com.ibm.xlcpp131.aix.doc/language_ref/noreturn.html */
  #define ecb_noreturn   _Noreturn
#elif ECB_CPP11
  #define ecb_noreturn   [[noreturn]]
#elif _MSC_VER >= 1200
  /* http://msdn.microsoft.com/en-us/library/k6ktzx3s.aspx */
  #define ecb_noreturn   __declspec (noreturn)
#else
  #define ecb_noreturn   ecb_attribute ((__noreturn__))
#endif

#if ECB_GCC_VERSION(4,3)
  #define ecb_artificial ecb_attribute ((__artificial__))
  #define ecb_hot        ecb_attribute ((__hot__))
  #define ecb_cold       ecb_attribute ((__cold__))
#else
  #define ecb_artificial
  #define ecb_hot
  #define ecb_cold
#endif

/* put around conditional expressions if you are very sure that the  */
/* expression is mostly true or mostly false. note that these return */
/* booleans, not the expression.                                     */
#define ecb_expect_false(expr) ecb_expect (!!(expr), 0)
#define ecb_expect_true(expr)  ecb_expect (!!(expr), 1)
/* for compatibility to the rest of the world */
#define ecb_likely(expr)   ecb_expect_true  (expr)
#define ecb_unlikely(expr) ecb_expect_false (expr)

/* count trailing zero bits and count # of one bits */
#if ECB_GCC_VERSION(3,4) \
    || (ECB_CLANG_BUILTIN(__builtin_clz) && ECB_CLANG_BUILTIN(__builtin_clzll) \
        && ECB_CLANG_BUILTIN(__builtin_ctz) && ECB_CLANG_BUILTIN(__builtin_ctzll) \
        && ECB_CLANG_BUILTIN(__builtin_popcount))
  #define ecb_ctz32(x)      __builtin_ctz (x)
  #define ecb_ctz64(x)      (__SIZEOF_LONG__ == 64 ? __builtin_ctzl (x) : __builtin_ctzll (x))
  #define ecb_clz32(x)      __builtin_clz (x)
  #define ecb_clz64(x)      (__SIZEOF_LONG__ == 64 ? __builtin_clzl (x) : __builtin_clzll (x))
  #define ecb_ld32(x)       (ecb_clz32 (x) ^ 31)
  #define ecb_ld64(x)       (ecb_clz64 (x) ^ 63)
  #define ecb_popcount32(x) __builtin_popcount (x)
  /* ecb_popcount64 is more difficult, see below */
#else
  ecb_function_ ecb_const int ecb_ctz32 (uint32_t x);
  ecb_function_ ecb_const int ecb_ctz32 (uint32_t x)
  {
#if 1400 <= _MSC_VER && (_M_IX86 || _M_X64 || _M_IA64 || _M_ARM)
    unsigned long r;
    _BitScanForward (&r, x);
    return (int)r;
#else
    int r;

    x &= ~x + 1; /* this isolates the lowest bit */

  #if 1
    /* David Seal's algorithm, Message-ID: <32975@armltd.uucp> from 1994 */
    /* This happens to return 32 for x == 0, but the API does not support this */

    /* -0 marks unused entries */
    static unsigned char table[64] =
      {
        32,  0,  1, 12,  2,  6, -0, 13,    3, -0,  7, -0, -0, -0, -0, 14,
        10,  4, -0, -0,  8, -0, -0, 25,   -0, -0, -0, -0, -0, 21, 27, 15,
        31, 11,  5, -0, -0, -0, -0, -0,    9, -0, -0, 24, -0, -0, 20, 26,
        30, -0, -0, -0, -0, 23, -0, 19,   29, -0, 22, 18, 28, 17, 16, -0
      };

    /* magic constant results in 33 unique values in the upper 6 bits */
    x *= 0x0450fbafU; /* == 17 * 65 * 65535 */

    r = table [x >> 26];
  #elif 0 /* branchless on i386, typically */
    r = 0;
    r += !!(x & 0xaaaaaaaa) << 0;
    r += !!(x & 0xcccccccc) << 1;
    r += !!(x & 0xf0f0f0f0) << 2;
    r += !!(x & 0xff00ff00) << 3;
    r += !!(x & 0xffff0000) << 4;
  #else /* branchless on modern compilers, typically */
    r = 0;
    if (x & 0xaaaaaaaa) r +=  1;
    if (x & 0xcccccccc) r +=  2;
    if (x & 0xf0f0f0f0) r +=  4;
    if (x & 0xff00ff00) r +=  8;
    if (x & 0xffff0000) r += 16;
#endif

    return r;
#endif
  }

  ecb_function_ ecb_const int ecb_ctz64 (uint64_t x);
  ecb_function_ ecb_const int ecb_ctz64 (uint64_t x)
  {
#if 1400 <= _MSC_VER && (_M_X64 || _M_IA64 || _M_ARM)
    unsigned long r;
    _BitScanForward64 (&r, x);
    return (int)r;
#else
    int shift = x & 0xffffffff ? 0 : 32;
    return ecb_ctz32 (x >> shift) + shift;
#endif
  }

  ecb_function_ ecb_const int ecb_clz32 (uint32_t x);
  ecb_function_ ecb_const int ecb_clz32 (uint32_t x)
  {
#if 1400 <= _MSC_VER && (_M_IX86 || _M_X64 || _M_IA64 || _M_ARM)
    unsigned long r;
    _BitScanReverse (&r, x);
    return 31 - (int)r;
#else

    /* Robert Harley's algorithm from comp.arch 1996-12-07 */
    /* This happens to return 32 for x == 0, but the API does not support this */

    /* -0 marks unused table elements */
    static unsigned char table[64] =
      {
        32, 31, -0, 16, -0, 30,  3, -0,   15, -0, -0, -0, 29, 10,  2, -0,
        -0, -0, 12, 14, 21, -0, 19, -0,   -0, 28, -0, 25, -0,  9,  1, -0,
        17, -0,  4, -0, -0, -0, 11, -0,   13, 22, 20, -0, 26, -0, -0, 18,
         5, -0, -0, 23, -0, 27, -0,  6,   -0, 24,  7, -0,  8, -0,  0, -0
      };

    /* propagate leftmost 1 bit to the right */
    x |= x >>  1;
    x |= x >>  2;
    x |= x >>  4;
    x |= x >>  8;
    x |= x >> 16;

    /* magic constant results in 33 unique values in the upper 6 bits */
    x *= 0x06EB14F9U; /* == 7 * 255 * 255 * 255 */

    return table [x >> 26];
#endif
  }

  ecb_function_ ecb_const int ecb_clz64 (uint64_t x);
  ecb_function_ ecb_const int ecb_clz64 (uint64_t x)
  {
#if 1400 <= _MSC_VER && (_M_X64 || _M_IA64 || _M_ARM)
    unsigned long r;
    _BitScanReverse64 (&r, x);
    return 63 - (int)r;
#else
    uint32_t l = x >> 32;
    int shift = l ? 0 : 32;
    return ecb_clz32 (l ? l : x) + shift;
#endif
  }

  ecb_function_ ecb_const int ecb_popcount32 (uint32_t x);
  ecb_function_ ecb_const int ecb_popcount32 (uint32_t x)
  {
    x -=  (x >> 1) & 0x55555555;
    x  = ((x >> 2) & 0x33333333) + (x & 0x33333333);
    x  = ((x >> 4) + x) & 0x0f0f0f0f;
    x *= 0x01010101;

    return x >> 24;
  }

  ecb_function_ ecb_const int ecb_ld32 (uint32_t x);
  ecb_function_ ecb_const int ecb_ld32 (uint32_t x)
  {
#if 1400 <= _MSC_VER && (_M_IX86 || _M_X64 || _M_IA64 || _M_ARM)
    unsigned long r;
    _BitScanReverse (&r, x);
    return (int)r;
#else
    int r = 0;

    if (x >> 16) { x >>= 16; r += 16; }
    if (x >>  8) { x >>=  8; r +=  8; }
    if (x >>  4) { x >>=  4; r +=  4; }
    if (x >>  2) { x >>=  2; r +=  2; }
    if (x >>  1) {           r +=  1; }

    return r;
#endif
  }

  ecb_function_ ecb_const int ecb_ld64 (uint64_t x);
  ecb_function_ ecb_const int ecb_ld64 (uint64_t x)
  {
#if 1400 <= _MSC_VER && (_M_X64 || _M_IA64 || _M_ARM)
    unsigned long r;
    _BitScanReverse64 (&r, x);
    return (int)r;
#else
    int r = 0;

    if (x >> 32) { x >>= 32; r += 32; }

    return r + ecb_ld32 (x);
#endif
  }
#endif

ecb_function_ ecb_const ecb_bool ecb_is_pot32 (uint32_t x);
ecb_function_ ecb_const ecb_bool ecb_is_pot32 (uint32_t x) { return !(x & (x - 1)); }
ecb_function_ ecb_const ecb_bool ecb_is_pot64 (uint64_t x);
ecb_function_ ecb_const ecb_bool ecb_is_pot64 (uint64_t x) { return !(x & (x - 1)); }

ecb_function_ ecb_const uint8_t  ecb_bitrev8  (uint8_t  x);
ecb_function_ ecb_const uint8_t  ecb_bitrev8  (uint8_t  x)
{
  return (  (x * 0x0802U & 0x22110U)
          | (x * 0x8020U & 0x88440U)) * 0x10101U >> 16;
}

ecb_function_ ecb_const uint16_t ecb_bitrev16 (uint16_t x);
ecb_function_ ecb_const uint16_t ecb_bitrev16 (uint16_t x)
{
  x = ((x >>  1) &     0x5555) | ((x &     0x5555) <<  1);
  x = ((x >>  2) &     0x3333) | ((x &     0x3333) <<  2);
  x = ((x >>  4) &     0x0f0f) | ((x &     0x0f0f) <<  4);
  x = ( x >>  8              ) | ( x               <<  8);

  return x;
}

ecb_function_ ecb_const uint32_t ecb_bitrev32 (uint32_t x);
ecb_function_ ecb_const uint32_t ecb_bitrev32 (uint32_t x)
{
  x = ((x >>  1) & 0x55555555) | ((x & 0x55555555) <<  1);
  x = ((x >>  2) & 0x33333333) | ((x & 0x33333333) <<  2);
  x = ((x >>  4) & 0x0f0f0f0f) | ((x & 0x0f0f0f0f) <<  4);
  x = ((x >>  8) & 0x00ff00ff) | ((x & 0x00ff00ff) <<  8);
  x = ( x >> 16              ) | ( x               << 16);

  return x;
}

ecb_function_ ecb_const int ecb_popcount64 (uint64_t x);
ecb_function_ ecb_const int ecb_popcount64 (uint64_t x)
{
  /* popcount64 is only available on 64 bit cpus as gcc builtin. */
  /* also, gcc/clang make this surprisingly difficult to use */
#if (__SIZEOF_LONG__ == 8) && (ECB_GCC_VERSION(3,4) || ECB_CLANG_BUILTIN (__builtin_popcountl))
  return __builtin_popcountl (x);
#else
  return ecb_popcount32 (x) + ecb_popcount32 (x >> 32);
#endif
}

ecb_inline uint8_t  ecb_rotl8  (uint8_t  x, unsigned int count) { return (x >> (-count &  7)) | (x << (count &  7)); }
ecb_inline uint8_t  ecb_rotr8  (uint8_t  x, unsigned int count) { return (x << (-count &  7)) | (x >> (count &  7)); }
ecb_inline uint16_t ecb_rotl16 (uint16_t x, unsigned int count) { return (x >> (-count & 15)) | (x << (count & 15)); }
ecb_inline uint16_t ecb_rotr16 (uint16_t x, unsigned int count) { return (x << (-count & 15)) | (x >> (count & 15)); }
ecb_inline uint32_t ecb_rotl32 (uint32_t x, unsigned int count) { return (x >> (-count & 31)) | (x << (count & 31)); }
ecb_inline uint32_t ecb_rotr32 (uint32_t x, unsigned int count) { return (x << (-count & 31)) | (x >> (count & 31)); }
ecb_inline uint64_t ecb_rotl64 (uint64_t x, unsigned int count) { return (x >> (-count & 63)) | (x << (count & 63)); }
ecb_inline uint64_t ecb_rotr64 (uint64_t x, unsigned int count) { return (x << (-count & 63)) | (x >> (count & 63)); }

#if ECB_CPP

inline uint8_t  ecb_ctz (uint8_t  v) { return ecb_ctz32 (v); }
inline uint16_t ecb_ctz (uint16_t v) { return ecb_ctz32 (v); }
inline uint32_t ecb_ctz (uint32_t v) { return ecb_ctz32 (v); }
inline uint64_t ecb_ctz (uint64_t v) { return ecb_ctz64 (v); }

inline bool ecb_is_pot (uint8_t  v) { return ecb_is_pot32 (v); }
inline bool ecb_is_pot (uint16_t v) { return ecb_is_pot32 (v); }
inline bool ecb_is_pot (uint32_t v) { return ecb_is_pot32 (v); }
inline bool ecb_is_pot (uint64_t v) { return ecb_is_pot64 (v); }

inline int ecb_ld (uint8_t  v) { return ecb_ld32 (v); }
inline int ecb_ld (uint16_t v) { return ecb_ld32 (v); }
inline int ecb_ld (uint32_t v) { return ecb_ld32 (v); }
inline int ecb_ld (uint64_t v) { return ecb_ld64 (v); }

inline int ecb_popcount (uint8_t  v) { return ecb_popcount32 (v); }
inline int ecb_popcount (uint16_t v) { return ecb_popcount32 (v); }
inline int ecb_popcount (uint32_t v) { return ecb_popcount32 (v); }
inline int ecb_popcount (uint64_t v) { return ecb_popcount64 (v); }

inline uint8_t  ecb_bitrev (uint8_t  v) { return ecb_bitrev8  (v); }
inline uint16_t ecb_bitrev (uint16_t v) { return ecb_bitrev16 (v); }
inline uint32_t ecb_bitrev (uint32_t v) { return ecb_bitrev32 (v); }

inline uint8_t  ecb_rotl (uint8_t  v, unsigned int count) { return ecb_rotl8  (v, count); }
inline uint16_t ecb_rotl (uint16_t v, unsigned int count) { return ecb_rotl16 (v, count); }
inline uint32_t ecb_rotl (uint32_t v, unsigned int count) { return ecb_rotl32 (v, count); }
inline uint64_t ecb_rotl (uint64_t v, unsigned int count) { return ecb_rotl64 (v, count); }

inline uint8_t  ecb_rotr (uint8_t  v, unsigned int count) { return ecb_rotr8  (v, count); }
inline uint16_t ecb_rotr (uint16_t v, unsigned int count) { return ecb_rotr16 (v, count); }
inline uint32_t ecb_rotr (uint32_t v, unsigned int count) { return ecb_rotr32 (v, count); }
inline uint64_t ecb_rotr (uint64_t v, unsigned int count) { return ecb_rotr64 (v, count); }

#endif

#if ECB_GCC_VERSION(4,3) || (ECB_CLANG_BUILTIN(__builtin_bswap32) && ECB_CLANG_BUILTIN(__builtin_bswap64))
  #if ECB_GCC_VERSION(4,8) || ECB_CLANG_BUILTIN(__builtin_bswap16)
  #define ecb_bswap16(x)  __builtin_bswap16 (x)
  #else
  #define ecb_bswap16(x) (__builtin_bswap32 (x) >> 16)
  #endif
  #define ecb_bswap32(x)  __builtin_bswap32 (x)
  #define ecb_bswap64(x)  __builtin_bswap64 (x)
#elif _MSC_VER
  #include <stdlib.h>
  #define ecb_bswap16(x) ((uint16_t)_byteswap_ushort ((uint16_t)(x)))
  #define ecb_bswap32(x) ((uint32_t)_byteswap_ulong  ((uint32_t)(x)))
  #define ecb_bswap64(x) ((uint64_t)_byteswap_uint64 ((uint64_t)(x)))
#else
  ecb_function_ ecb_const uint16_t ecb_bswap16 (uint16_t x);
  ecb_function_ ecb_const uint16_t ecb_bswap16 (uint16_t x)
  {
    return ecb_rotl16 (x, 8);
  }

  ecb_function_ ecb_const uint32_t ecb_bswap32 (uint32_t x);
  ecb_function_ ecb_const uint32_t ecb_bswap32 (uint32_t x)
  {
    return (((uint32_t)ecb_bswap16 (x)) << 16) | ecb_bswap16 (x >> 16);
  }

  ecb_function_ ecb_const uint64_t ecb_bswap64 (uint64_t x);
  ecb_function_ ecb_const uint64_t ecb_bswap64 (uint64_t x)
  {
    return (((uint64_t)ecb_bswap32 (x)) << 32) | ecb_bswap32 (x >> 32);
  }
#endif

#if ECB_GCC_VERSION(4,5) || ECB_CLANG_BUILTIN(__builtin_unreachable)
  #define ecb_unreachable() __builtin_unreachable ()
#else
  /* this seems to work fine, but gcc always emits a warning for it :/ */
  ecb_inline ecb_noreturn void ecb_unreachable (void);
  ecb_inline ecb_noreturn void ecb_unreachable (void) { }
#endif

/* try to tell the compiler that some condition is definitely true */
#define ecb_assume(cond) if (!(cond)) ecb_unreachable (); else 0

ecb_inline uint32_t ecb_byteorder_helper (void);
ecb_inline uint32_t ecb_byteorder_helper (void)
{
  /* the union code still generates code under pressure in gcc, */
  /* but less than using pointers, and always seems to */
  /* successfully return a constant. */
  /* the reason why we have this horrible preprocessor mess */
  /* is to avoid it in all cases, at least on common architectures */
  /* or when using a recent enough gcc version (>= 4.6) */
#if (defined __BYTE_ORDER__ && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) \
    || ((__i386 || __i386__ || _M_IX86 || ECB_GCC_AMD64 || ECB_MSVC_AMD64) && !__VOS__)
  #define ECB_LITTLE_ENDIAN 1
  return 0x44332211;
#elif (defined __BYTE_ORDER__ && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) \
      || ((__AARCH64EB__ || __MIPSEB__ || __ARMEB__) && !__VOS__)
  #define ECB_BIG_ENDIAN 1
  return 0x11223344;
#else
  union
  {
    uint8_t c[4];
    uint32_t u;
  } u = { 0x11, 0x22, 0x33, 0x44 };
  return u.u;
#endif
}

ecb_inline ecb_const ecb_bool ecb_big_endian    (void) { return ecb_byteorder_helper () == 0x11223344; }
ecb_inline ecb_const ecb_bool ecb_little_endian (void) { return ecb_byteorder_helper () == 0x44332211; }

/*****************************************************************************/
/* unaligned load/store */

ecb_inline uint_fast16_t ecb_be_u16_to_host (uint_fast16_t v) { return ecb_little_endian () ? ecb_bswap16 (v) : v; }
ecb_inline uint_fast32_t ecb_be_u32_to_host (uint_fast32_t v) { return ecb_little_endian () ? ecb_bswap32 (v) : v; }
ecb_inline uint_fast64_t ecb_be_u64_to_host (uint_fast64_t v) { return ecb_little_endian () ? ecb_bswap64 (v) : v; }

ecb_inline uint_fast16_t ecb_le_u16_to_host (uint_fast16_t v) { return ecb_big_endian    () ? ecb_bswap16 (v) : v; }
ecb_inline uint_fast32_t ecb_le_u32_to_host (uint_fast32_t v) { return ecb_big_endian    () ? ecb_bswap32 (v) : v; }
ecb_inline uint_fast64_t ecb_le_u64_to_host (uint_fast64_t v) { return ecb_big_endian    () ? ecb_bswap64 (v) : v; }

ecb_inline uint_fast16_t ecb_peek_u16_u (const void *ptr) { uint16_t v; memcpy (&v, ptr, sizeof (v)); return v; }
ecb_inline uint_fast32_t ecb_peek_u32_u (const void *ptr) { uint32_t v; memcpy (&v, ptr, sizeof (v)); return v; }
ecb_inline uint_fast64_t ecb_peek_u64_u (const void *ptr) { uint64_t v; memcpy (&v, ptr, sizeof (v)); return v; }

ecb_inline uint_fast16_t ecb_peek_be_u16_u (const void *ptr) { return ecb_be_u16_to_host (ecb_peek_u16_u (ptr)); }
ecb_inline uint_fast32_t ecb_peek_be_u32_u (const void *ptr) { return ecb_be_u32_to_host (ecb_peek_u32_u (ptr)); }
ecb_inline uint_fast64_t ecb_peek_be_u64_u (const void *ptr) { return ecb_be_u64_to_host (ecb_peek_u64_u (ptr)); }

ecb_inline uint_fast16_t ecb_peek_le_u16_u (const void *ptr) { return ecb_le_u16_to_host (ecb_peek_u16_u (ptr)); }
ecb_inline uint_fast32_t ecb_peek_le_u32_u (const void *ptr) { return ecb_le_u32_to_host (ecb_peek_u32_u (ptr)); }
ecb_inline uint_fast64_t ecb_peek_le_u64_u (const void *ptr) { return ecb_le_u64_to_host (ecb_peek_u64_u (ptr)); }

ecb_inline uint_fast16_t ecb_host_to_be_u16 (uint_fast16_t v) { return ecb_little_endian () ? ecb_bswap16 (v) : v; }
ecb_inline uint_fast32_t ecb_host_to_be_u32 (uint_fast32_t v) { return ecb_little_endian () ? ecb_bswap32 (v) : v; }
ecb_inline uint_fast64_t ecb_host_to_be_u64 (uint_fast64_t v) { return ecb_little_endian () ? ecb_bswap64 (v) : v; }

ecb_inline uint_fast16_t ecb_host_to_le_u16 (uint_fast16_t v) { return ecb_big_endian    () ? ecb_bswap16 (v) : v; }
ecb_inline uint_fast32_t ecb_host_to_le_u32 (uint_fast32_t v) { return ecb_big_endian    () ? ecb_bswap32 (v) : v; }
ecb_inline uint_fast64_t ecb_host_to_le_u64 (uint_fast64_t v) { return ecb_big_endian    () ? ecb_bswap64 (v) : v; }

ecb_inline void ecb_poke_u16_u (void *ptr, uint16_t v) { memcpy (ptr, &v, sizeof (v)); }
ecb_inline void ecb_poke_u32_u (void *ptr, uint32_t v) { memcpy (ptr, &v, sizeof (v)); }
ecb_inline void ecb_poke_u64_u (void *ptr, uint64_t v) { memcpy (ptr, &v, sizeof (v)); }

ecb_inline void ecb_poke_be_u16_u (void *ptr, uint_fast16_t v) { ecb_poke_u16_u (ptr, ecb_host_to_be_u16 (v)); }
ecb_inline void ecb_poke_be_u32_u (void *ptr, uint_fast32_t v) { ecb_poke_u32_u (ptr, ecb_host_to_be_u32 (v)); }
ecb_inline void ecb_poke_be_u64_u (void *ptr, uint_fast64_t v) { ecb_poke_u64_u (ptr, ecb_host_to_be_u64 (v)); }

ecb_inline void ecb_poke_le_u16_u (void *ptr, uint_fast16_t v) { ecb_poke_u16_u (ptr, ecb_host_to_le_u16 (v)); }
ecb_inline void ecb_poke_le_u32_u (void *ptr, uint_fast32_t v) { ecb_poke_u32_u (ptr, ecb_host_to_le_u32 (v)); }
ecb_inline void ecb_poke_le_u64_u (void *ptr, uint_fast64_t v) { ecb_poke_u64_u (ptr, ecb_host_to_le_u64 (v)); }

#if ECB_CPP

inline uint8_t  ecb_bswap (uint8_t  v) { return v; }
inline uint16_t ecb_bswap (uint16_t v) { return ecb_bswap16 (v); }
inline uint32_t ecb_bswap (uint32_t v) { return ecb_bswap32 (v); }
inline uint64_t ecb_bswap (uint64_t v) { return ecb_bswap64 (v); }

template<typename T> inline T ecb_be_to_host (T v) { return ecb_little_endian () ? ecb_bswap (v) : v; }
template<typename T> inline T ecb_le_to_host (T v) { return ecb_big_endian    () ? ecb_bswap (v) : v; }
template<typename T> inline T ecb_peek       (const void *ptr) { return *(const T *)ptr; }
template<typename T> inline T ecb_peek_be    (const void *ptr) { return ecb_be_to_host (ecb_peek  <T> (ptr)); }
template<typename T> inline T ecb_peek_le    (const void *ptr) { return ecb_le_to_host (ecb_peek  <T> (ptr)); }
template<typename T> inline T ecb_peek_u     (const void *ptr) { T v; memcpy (&v, ptr, sizeof (v)); return v; }
template<typename T> inline T ecb_peek_be_u  (const void *ptr) { return ecb_be_to_host (ecb_peek_u<T> (ptr)); }
template<typename T> inline T ecb_peek_le_u  (const void *ptr) { return ecb_le_to_host (ecb_peek_u<T> (ptr)); }

template<typename T> inline T ecb_host_to_be (T v) { return ecb_little_endian () ? ecb_bswap (v) : v; }
template<typename T> inline T ecb_host_to_le (T v) { return ecb_big_endian    () ? ecb_bswap (v) : v; }
template<typename T> inline void ecb_poke      (void *ptr, T v) { *(T *)ptr = v; }
template<typename T> inline void ecb_poke_be   (void *ptr, T v) { return ecb_poke  <T> (ptr, ecb_host_to_be (v)); }
template<typename T> inline void ecb_poke_le   (void *ptr, T v) { return ecb_poke  <T> (ptr, ecb_host_to_le (v)); }
template<typename T> inline void ecb_poke_u    (void *ptr, T v) { memcpy (ptr, &v, sizeof (v)); }
template<typename T> inline void ecb_poke_be_u (void *ptr, T v) { return ecb_poke_u<T> (ptr, ecb_host_to_be (v)); }
template<typename T> inline void ecb_poke_le_u (void *ptr, T v) { return ecb_poke_u<T> (ptr, ecb_host_to_le (v)); }

#endif

/*****************************************************************************/
/* pointer/integer hashing */

/* based on hash by Chris Wellons, https://nullprogram.com/blog/2018/07/31/ */
ecb_function_ ecb_const uint32_t ecb_mix32 (uint32_t v);
ecb_function_ ecb_const uint32_t ecb_mix32 (uint32_t v)
{
  v ^= v >> 16; v *= 0x7feb352dU;
  v ^= v >> 15; v *= 0x846ca68bU;
  v ^= v >> 16;
  return v;
}

ecb_function_ ecb_const uint32_t ecb_unmix32 (uint32_t v);
ecb_function_ ecb_const uint32_t ecb_unmix32 (uint32_t v)
{
  v ^= v >> 16          ; v *= 0x43021123U;
  v ^= v >> 15 ^ v >> 30; v *= 0x1d69e2a5U;
  v ^= v >> 16          ;
  return v;
}

/* based on splitmix64, by Sebastiona Vigna, https://prng.di.unimi.it/splitmix64.c */
ecb_function_ ecb_const uint64_t ecb_mix64 (uint64_t v);
ecb_function_ ecb_const uint64_t ecb_mix64 (uint64_t v)
{
  v ^= v >> 30; v *= 0xbf58476d1ce4e5b9U;
  v ^= v >> 27; v *= 0x94d049bb133111ebU;
  v ^= v >> 31;
  return v;
}

ecb_function_ ecb_const uint64_t ecb_unmix64 (uint64_t v);
ecb_function_ ecb_const uint64_t ecb_unmix64 (uint64_t v)
{
  v ^= v >> 31 ^ v >> 62; v *= 0x319642b2d24d8ec3U;
  v ^= v >> 27 ^ v >> 54; v *= 0x96de1b173f119089U;
  v ^= v >> 30 ^ v >> 60;
  return v;
}

ecb_function_ ecb_const uintptr_t ecb_ptrmix (void *p);
ecb_function_ ecb_const uintptr_t ecb_ptrmix (void *p)
{
  #if ECB_PTRSIZE <= 4
  return ecb_mix32 ((uint32_t)p);
  #else
  return ecb_mix64 ((uint64_t)p);
  #endif
}

ecb_function_ ecb_const void *ecb_ptrunmix (uintptr_t v);
ecb_function_ ecb_const void *ecb_ptrunmix (uintptr_t v)
{
  #if ECB_PTRSIZE <= 4
  return (void *)ecb_unmix32 (v);
  #else
  return (void *)ecb_unmix64 (v);
  #endif
}

#if ECB_CPP

template<typename T>
inline uintptr_t ecb_ptrmix (T *p)
{
  return ecb_ptrmix (static_cast<void *>(p));
}

template<typename T>
inline T *ecb_ptrunmix (uintptr_t v)
{
  return static_cast<T *>(ecb_ptrunmix (v));
}

#endif

/*****************************************************************************/
/* gray code */

ecb_inline uint_fast8_t  ecb_gray_encode8  (uint_fast8_t  b) { return b ^ (b >> 1); }
ecb_inline uint_fast16_t ecb_gray_encode16 (uint_fast16_t b) { return b ^ (b >> 1); }
ecb_inline uint_fast32_t ecb_gray_encode32 (uint_fast32_t b) { return b ^ (b >> 1); }
ecb_inline uint_fast64_t ecb_gray_encode64 (uint_fast64_t b) { return b ^ (b >> 1); }

ecb_function_ ecb_const uint8_t ecb_gray_decode8 (uint8_t g);
ecb_function_ ecb_const uint8_t ecb_gray_decode8 (uint8_t g)
{
  g ^= g >>  1;
  g ^= g >>  2;
  g ^= g >>  4;

  return g;
}

ecb_function_ ecb_const uint16_t ecb_gray_decode16 (uint16_t g);
ecb_function_ ecb_const uint16_t ecb_gray_decode16 (uint16_t g)
{
  g ^= g >>  1;
  g ^= g >>  2;
  g ^= g >>  4;
  g ^= g >>  8;

  return g;
}

ecb_function_ ecb_const uint32_t ecb_gray_decode32 (uint32_t g);
ecb_function_ ecb_const uint32_t ecb_gray_decode32 (uint32_t g)
{
  g ^= g >>  1;
  g ^= g >>  2;
  g ^= g >>  4;
  g ^= g >>  8;
  g ^= g >> 16;

  return g;
}

ecb_function_ ecb_const uint64_t ecb_gray_decode64 (uint64_t g);
ecb_function_ ecb_const uint64_t ecb_gray_decode64 (uint64_t g)
{
  g ^= g >>  1;
  g ^= g >>  2;
  g ^= g >>  4;
  g ^= g >>  8;
  g ^= g >> 16;
  g ^= g >> 32;

  return g;
}

#if ECB_CPP

ecb_inline uint8_t  ecb_gray_encode (uint8_t  b) { return ecb_gray_encode8  (b); }
ecb_inline uint16_t ecb_gray_encode (uint16_t b) { return ecb_gray_encode16 (b); }
ecb_inline uint32_t ecb_gray_encode (uint32_t b) { return ecb_gray_encode32 (b); }
ecb_inline uint64_t ecb_gray_encode (uint64_t b) { return ecb_gray_encode64 (b); }

ecb_inline uint8_t  ecb_gray_decode (uint8_t  g) { return ecb_gray_decode8  (g); }
ecb_inline uint16_t ecb_gray_decode (uint16_t g) { return ecb_gray_decode16 (g); }
ecb_inline uint32_t ecb_gray_decode (uint32_t g) { return ecb_gray_decode32 (g); }
ecb_inline uint64_t ecb_gray_decode (uint64_t g) { return ecb_gray_decode64 (g); }

#endif

/*****************************************************************************/
/* 2d hilbert curves */

/* algorithm from the book Hacker's Delight, modified to not */
/* run into undefined behaviour for n==16 */
ecb_function_ ecb_const uint32_t ecb_hilbert2d_index_to_coord32 (int n, uint32_t s);
ecb_function_ ecb_const uint32_t ecb_hilbert2d_index_to_coord32 (int n, uint32_t s)
{
  uint32_t comp, swap, cs, t, sr;

  /* pad s on the left (unused) bits with 01 (no change groups) */
  s |= 0x55555555U << n << n;
  /* "s shift right" */
  sr = (s >> 1) & 0x55555555U;
  /* compute complement and swap info in two-bit groups */
  cs = ((s & 0x55555555U) + sr) ^ 0x55555555U;

  /* parallel prefix xor op to propagate both complement
   * and swap info together from left to right (there is
   * no step "cs ^= cs >> 1", so in effect it computes
   * two independent parallel prefix operations on two
   * interleaved sets of sixteen bits).
   */
  cs ^= cs >>  2;
  cs ^= cs >>  4;
  cs ^= cs >>  8;
  cs ^= cs >> 16;

  /* separate swap and complement bits */
  swap =  cs       & 0x55555555U;
  comp = (cs >> 1) & 0x55555555U;
 
  /* calculate coordinates in odd and even bit positions */
  t = (s & swap) ^ comp;
  s = s ^ sr ^ t ^ (t << 1);

  /* unpad/clear out any junk on the left */
  s = s & ((1 << n << n) - 1);
 
  /* Now "unshuffle" to separate the x and y bits. */
  t = (s ^ (s >> 1)) & 0x22222222U; s ^= t ^ (t << 1);
  t = (s ^ (s >> 2)) & 0x0c0c0c0cU; s ^= t ^ (t << 2);
  t = (s ^ (s >> 4)) & 0x00f000f0U; s ^= t ^ (t << 4);
  t = (s ^ (s >> 8)) & 0x0000ff00U; s ^= t ^ (t << 8);
 
  /* now s contains two 16-bit coordinates */
  return s;
}

/* 64 bit, a straightforward extension to the 32 bit case */
ecb_function_ ecb_const uint64_t ecb_hilbert2d_index_to_coord64 (int n, uint64_t s);
ecb_function_ ecb_const uint64_t ecb_hilbert2d_index_to_coord64 (int n, uint64_t s)
{
  uint64_t comp, swap, cs, t, sr;

  /* pad s on the left (unused) bits with 01 (no change groups) */
  s |= 0x5555555555555555U << n << n;
  /* "s shift right" */
  sr = (s >> 1) & 0x5555555555555555U;
  /* compute complement and swap info in two-bit groups */
  cs = ((s & 0x5555555555555555U) + sr) ^ 0x5555555555555555U;

  /* parallel prefix xor op to propagate both complement
   * and swap info together from left to right (there is
   * no step "cs ^= cs >> 1", so in effect it computes
   * two independent parallel prefix operations on two
   * interleaved sets of thirty-two bits).
   */
  cs ^= cs >>  2;
  cs ^= cs >>  4;
  cs ^= cs >>  8;
  cs ^= cs >> 16;
  cs ^= cs >> 32;

  /* separate swap and complement bits */
  swap =  cs       & 0x5555555555555555U;
  comp = (cs >> 1) & 0x5555555555555555U;
 
  /* calculate coordinates in odd and even bit positions */
  t = (s & swap) ^ comp;
  s = s ^ sr ^ t ^ (t << 1);

  /* unpad/clear out any junk on the left */
  s = s & ((1 << n << n) - 1);
 
  /* Now "unshuffle" to separate the x and y bits. */
  t = (s ^ (s >>  1)) & 0x2222222222222222U; s ^= t ^ (t <<  1);
  t = (s ^ (s >>  2)) & 0x0c0c0c0c0c0c0c0cU; s ^= t ^ (t <<  2);
  t = (s ^ (s >>  4)) & 0x00f000f000f000f0U; s ^= t ^ (t <<  4);
  t = (s ^ (s >>  8)) & 0x0000ff000000ff00U; s ^= t ^ (t <<  8);
  t = (s ^ (s >> 16)) & 0x00000000ffff0000U; s ^= t ^ (t << 16);
 
  /* now s contains two 32-bit coordinates */
  return s;
}

/* algorithm from the book Hacker's Delight, but a similar algorithm*/
/* is given in https://doi.org/10.1002/spe.4380160103 */
/* this has been slightly improved over the original version */
ecb_function_ ecb_const uint32_t ecb_hilbert2d_coord_to_index32 (int n, uint32_t xy);
ecb_function_ ecb_const uint32_t ecb_hilbert2d_coord_to_index32 (int n, uint32_t xy)
{
  uint32_t row;
  uint32_t state = 0;
  uint32_t s = 0;

  do
    {
      --n;

      row =  4 * state
          | (2 & (xy >> n >> 15))
          | (1 & (xy >> n      ));

      /* these funky constants are lookup tables for two-bit values */
      s = (s << 2) | (0x361e9cb4U >> 2 * row) & 3;
      state = (0x8fe65831U >> 2 * row) & 3;
    }
  while (n > 0);

  return s;
}

/* 64 bit, essentially the same as 32 bit */
ecb_function_ ecb_const uint64_t ecb_hilbert2d_coord_to_index64 (int n, uint64_t xy);
ecb_function_ ecb_const uint64_t ecb_hilbert2d_coord_to_index64 (int n, uint64_t xy)
{
  uint32_t row;
  uint32_t state = 0;
  uint64_t s = 0;

  do
    {
      --n;

      row =  4 * state
          | (2 & (xy >> n >> 31))
          | (1 & (xy >> n      ));

      /* these funky constants are lookup tables for two-bit values */
      s = (s << 2) | (0x361e9cb4U >> 2 * row) & 3;
      state = (0x8fe65831U >> 2 * row) & 3;
    }
  while (n > 0);

  return s;
}

/*****************************************************************************/
/* division */

#if ECB_GCC_VERSION(3,0) || ECB_C99
  /* C99 tightened the definition of %, so we can use a more efficient version */
  #define ecb_mod(m,n) ((m) % (n) + ((m) % (n) < 0 ? (n) : 0))
#else
  #define ecb_mod(m,n) ((m) < 0 ? ((n) - 1 - ((-1 - (m)) % (n))) : ((m) % (n)))
#endif

#if ECB_CPP
  template<typename T>
  static inline T ecb_div_rd (T val, T div)
  {
    return val < 0 ? - ((-val + div - 1) / div) : (val          ) / div;
  }
  template<typename T>
  static inline T ecb_div_ru (T val, T div)
  {
    return val < 0 ? - ((-val          ) / div) : (val + div - 1) / div;
  }
#else
  #define ecb_div_rd(val,div) ((val) < 0 ? - ((-(val) + (div) - 1) / (div)) : ((val)            ) / (div))
  #define ecb_div_ru(val,div) ((val) < 0 ? - ((-(val)            ) / (div)) : ((val) + (div) - 1) / (div))
#endif

/*****************************************************************************/
/* array length */

#if ecb_cplusplus_does_not_suck
  /* does not work for local types (http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2657.htm) */
  template<typename T, int N>
  static inline int ecb_array_length (const T (&arr)[N])
  {
    return N;
  }
#else
  #define ecb_array_length(name) (sizeof (name) / sizeof (name [0]))
#endif

/*****************************************************************************/
/* IEEE 754-2008 half float conversions */

ecb_function_ ecb_const uint32_t ecb_binary16_to_binary32 (uint32_t x);
ecb_function_ ecb_const uint32_t ecb_binary16_to_binary32 (uint32_t x)
{
  unsigned int s = (x & 0x8000) << (31 - 15);
  int          e = (x >> 10) & 0x001f;
  unsigned int m =  x        & 0x03ff;

  if (ecb_expect_false (e == 31))
    /* infinity or NaN */
    e = 255 - (127 - 15);
  else if (ecb_expect_false (!e))
    {
      if (ecb_expect_true (!m))
        /* zero, handled by code below by forcing e to 0 */
        e = 0 - (127 - 15);
      else
        {
          /* subnormal, renormalise */
          unsigned int s = 10 - ecb_ld32 (m);

          m = (m << s) & 0x3ff; /* mask implicit bit */
          e -= s - 1;
        }
    }

  /* e and m now are normalised, or zero, (or inf or nan) */
  e += 127 - 15;

  return s | (e << 23) | (m << (23 - 10));
}

ecb_function_ ecb_const uint16_t ecb_binary32_to_binary16 (uint32_t x);
ecb_function_ ecb_const uint16_t ecb_binary32_to_binary16 (uint32_t x)
{
  unsigned int s =  (x >> 16) & 0x00008000; /* sign bit, the easy part */
  int          e = ((x >> 23) & 0x000000ff) - (127 - 15); /* the desired exponent */
  unsigned int m =   x        & 0x007fffff;

  x &= 0x7fffffff;

  /* if it's within range of binary16 normals, use fast path */
  if (ecb_expect_true (0x38800000 <= x && x <= 0x477fefff))
    {
      /* mantissa round-to-even */
      m += 0x00000fff + ((m >> (23 - 10)) & 1);

      /* handle overflow */
      if (ecb_expect_false (m >= 0x00800000))
        {
          m >>= 1;
          e +=  1;
        }

      return s | (e << 10) | (m >> (23 - 10));
    }

  /* handle large numbers and infinity */
  if (ecb_expect_true (0x477fefff < x && x <= 0x7f800000))
    return s | 0x7c00;

  /* handle zero, subnormals and small numbers */
  if (ecb_expect_true (x < 0x38800000))
    {
      /* zero */
      if (ecb_expect_true (!x))
        return s;

      /* handle subnormals */

      /* too small, will be zero */
      if (e < (14 - 24)) /* might not be sharp, but is good enough */
        return s;

      m |= 0x00800000; /* make implicit bit explicit */

      /* very tricky - we need to round to the nearest e (+10) bit value */
      {
        unsigned int bits = 14 - e;
        unsigned int half = (1 << (bits - 1)) - 1;
        unsigned int even = (m >> bits) & 1;

        /* if this overflows, we will end up with a normalised number */
        m = (m + half + even) >> bits;
      }

      return s | m;
    }

  /* handle NaNs, preserve leftmost nan bits, but make sure we don't turn them into infinities */
  m >>= 13;

  return s | 0x7c00 | m | !m;
}

/*******************************************************************************/
/* fast integer to ascii */

/*
 * This code is pretty complicated because it is general. The idea behind it,
 * however, is pretty simple: first, the number is multiplied with a scaling
 * factor (2**bits / 10**(digits-1)) to convert the integer into a fixed-point
 * number with the first digit in the upper bits.
 * Then this digit is converted to text and masked out. The resulting number
 * is then multiplied by 10, by multiplying the fixed point representation
 * by 5 and shifting the (binary) decimal point one to the right, so a 4.28
 * format becomes 5.27, 6.26 and so on.
 * The rest involves only advancing the pointer if we already generated a
 * non-zero digit, so leading zeroes are overwritten.
 */

/* simply return a mask with "bits" bits set */
#define ecb_i2a_mask(type,bits) ((((type)1) << (bits)) - 1)

/* oputput a single digit. maskvalue is 10**digitidx */
#define ecb_i2a_digit(type,bits,digitmask,maskvalue,digitidx) \
  if (digitmask >= maskvalue) /* constant, used to decide how many digits to generate */ \
    { \
      char digit = x >> (bits - digitidx); /* calculate the topmost digit */ \
      *ptr = digit + '0'; /* output it */ \
      nz = (digitmask == maskvalue) || nz || digit; /* first term == always output last digit */ \
      ptr += nz; /* output digit only if non-zero digit seen */ \
      x = (x & ecb_i2a_mask (type, bits - digitidx)) * 5; /* *10, but shift decimal point right */ \
    }

/* convert integer to fixed point format and multiply out digits, highest first */
/* requires magic constants: max. digits and number of bits after the decimal point */
#define ecb_i2a_def(suffix,ptr,v,type,bits,digitmask,lz) \
ecb_inline char *ecb_i2a_ ## suffix (char *ptr, uint32_t u) \
{ \
  char nz = lz; /* non-zero digit seen? */ \
  /* convert to x.bits fixed-point */ \
  type x = u * ((ecb_i2a_mask (type, bits) + digitmask) / digitmask); \
  /* output up to 10 digits */ \
  ecb_i2a_digit (type,bits,digitmask,          1, 0); \
  ecb_i2a_digit (type,bits,digitmask,         10, 1); \
  ecb_i2a_digit (type,bits,digitmask,        100, 2); \
  ecb_i2a_digit (type,bits,digitmask,       1000, 3); \
  ecb_i2a_digit (type,bits,digitmask,      10000, 4); \
  ecb_i2a_digit (type,bits,digitmask,     100000, 5); \
  ecb_i2a_digit (type,bits,digitmask,    1000000, 6); \
  ecb_i2a_digit (type,bits,digitmask,   10000000, 7); \
  ecb_i2a_digit (type,bits,digitmask,  100000000, 8); \
  ecb_i2a_digit (type,bits,digitmask, 1000000000, 9); \
  return ptr; \
}

/* predefined versions of the above, for various digits */
/* ecb_i2a_xN = almost N digits, limit defined by macro */
/* ecb_i2a_N = up to N digits, leading zeroes suppressed */
/* ecb_i2a_0N = exactly N digits, including leading zeroes */

/* non-leading-zero versions, limited range */
#define ECB_I2A_MAX_X5       59074 /* limit for ecb_i2a_x5 */
#define ECB_I2A_MAX_X10 2932500665 /* limit for ecb_i2a_x10 */
ecb_i2a_def ( x5, ptr, v, uint32_t, 26,      10000, 0)
ecb_i2a_def (x10, ptr, v, uint64_t, 60, 1000000000, 0)

/* non-leading zero versions, all digits, 4 and 9 are optimal for 32/64 bit */
ecb_i2a_def ( 2, ptr, v, uint32_t, 10,          10, 0)
ecb_i2a_def ( 3, ptr, v, uint32_t, 12,         100, 0)
ecb_i2a_def ( 4, ptr, v, uint32_t, 26,        1000, 0)
ecb_i2a_def ( 5, ptr, v, uint64_t, 30,       10000, 0)
ecb_i2a_def ( 6, ptr, v, uint64_t, 36,      100000, 0)
ecb_i2a_def ( 7, ptr, v, uint64_t, 44,     1000000, 0)
ecb_i2a_def ( 8, ptr, v, uint64_t, 50,    10000000, 0)
ecb_i2a_def ( 9, ptr, v, uint64_t, 56,   100000000, 0)

/* leading-zero versions, all digits, 04 and 09 are optimal for 32/64 bit */
ecb_i2a_def (02, ptr, v, uint32_t, 10,          10, 1)
ecb_i2a_def (03, ptr, v, uint32_t, 12,         100, 1)
ecb_i2a_def (04, ptr, v, uint32_t, 26,        1000, 1)
ecb_i2a_def (05, ptr, v, uint64_t, 30,       10000, 1)
ecb_i2a_def (06, ptr, v, uint64_t, 36,      100000, 1)
ecb_i2a_def (07, ptr, v, uint64_t, 44,     1000000, 1)
ecb_i2a_def (08, ptr, v, uint64_t, 50,    10000000, 1)
ecb_i2a_def (09, ptr, v, uint64_t, 56,   100000000, 1)

#define ECB_I2A_I32_DIGITS 11
#define ECB_I2A_U32_DIGITS 10
#define ECB_I2A_I64_DIGITS 20
#define ECB_I2A_U64_DIGITS 21
#define ECB_I2A_MAX_DIGITS 21

ecb_function_ char * ecb_i2a_u32 (char *ptr, uint32_t u);
ecb_function_ char * ecb_i2a_u32 (char *ptr, uint32_t u)
{
  #if ECB_64BIT_NATIVE
    if (ecb_expect_true (u <= ECB_I2A_MAX_X10))
      ptr = ecb_i2a_x10 (ptr, u);
    else /* x10 almost, but not fully, covers 32 bit */
      {
        uint32_t u1 = u % 1000000000;
        uint32_t u2 = u / 1000000000;

        *ptr++ = u2 + '0';
        ptr = ecb_i2a_09 (ptr, u1);
      }
  #else
    if (ecb_expect_true (u <= ECB_I2A_MAX_X5))
      ecb_i2a_x5 (ptr, u);
    else if (ecb_expect_true (u <= ECB_I2A_MAX_X5 * 10000))
      {
        uint32_t u1 = u % 10000;
        uint32_t u2 = u / 10000;

        ptr = ecb_i2a_x5 (ptr, u2);
        ptr = ecb_i2a_04 (ptr, u1);
      }
    else
      {
        uint32_t u1 = u  % 10000;
        uint32_t ua = u  / 10000;
        uint32_t u2 = ua % 10000;
        uint32_t u3 = ua / 10000;

        ptr = ecb_i2a_2  (ptr, u3);
        ptr = ecb_i2a_04 (ptr, u2);
        ptr = ecb_i2a_04 (ptr, u1);
      }
  #endif

  return ptr;
}

ecb_function_ char * ecb_i2a_i32 (char *ptr, int32_t v);
ecb_function_ char * ecb_i2a_i32 (char *ptr, int32_t v)
{
  *ptr = '-'; ptr += v < 0;
  uint32_t u = v < 0 ? -(uint32_t)v : v;

  #if ECB_64BIT_NATIVE
    ptr = ecb_i2a_x10 (ptr, u); /* x10 fully covers 31 bit */
  #else
    ptr = ecb_i2a_u32 (ptr, u);
  #endif

  return ptr;
}

ecb_function_ char * ecb_i2a_u64 (char *ptr, uint64_t u);
ecb_function_ char * ecb_i2a_u64 (char *ptr, uint64_t u)
{
  #if ECB_64BIT_NATIVE
    if (ecb_expect_true (u <= ECB_I2A_MAX_X10))
      ptr = ecb_i2a_x10 (ptr, u);
    else if (ecb_expect_false (u <= ECB_I2A_MAX_X10 * 1000000000))
      {
        uint64_t u1 = u % 1000000000;
        uint64_t u2 = u / 1000000000;

        ptr = ecb_i2a_x10 (ptr, u2);
        ptr = ecb_i2a_09  (ptr, u1);
      }
    else
      {
        uint64_t u1 = u  % 1000000000;
        uint64_t ua = u  / 1000000000;
        uint64_t u2 = ua % 1000000000;
        uint64_t u3 = ua / 1000000000;

        ptr = ecb_i2a_2  (ptr, u3);
        ptr = ecb_i2a_09 (ptr, u2);
        ptr = ecb_i2a_09 (ptr, u1);
      }
  #else
    if (ecb_expect_true (u <= ECB_I2A_MAX_X5))
      ptr = ecb_i2a_x5 (ptr, u);
    else
      {
        uint64_t u1 = u % 10000;
        uint64_t u2 = u / 10000;

        ptr = ecb_i2a_u64 (ptr, u2);
        ptr = ecb_i2a_04 (ptr, u1);
      }
  #endif

  return ptr;
}

ecb_function_ char * ecb_i2a_i64 (char *ptr, int64_t v);
ecb_function_ char * ecb_i2a_i64 (char *ptr, int64_t v)
{
  *ptr = '-'; ptr += v < 0;
  uint64_t u = v < 0 ? -(uint64_t)v : v;

  #if ECB_64BIT_NATIVE
    if (ecb_expect_true (u <= ECB_I2A_MAX_X10))
      ptr = ecb_i2a_x10 (ptr, u);
    else if (ecb_expect_false (u <= ECB_I2A_MAX_X10 * 1000000000))
      {
        uint64_t u1 = u % 1000000000;
        uint64_t u2 = u / 1000000000;

        ptr = ecb_i2a_x10 (ptr, u2);
        ptr = ecb_i2a_09  (ptr, u1);
      }
    else
      {
        uint64_t u1 = u  % 1000000000;
        uint64_t ua = u  / 1000000000;
        uint64_t u2 = ua % 1000000000;
        uint64_t u3 = ua / 1000000000;

        /* 2**31 is 19 digits, so the top is exactly one digit */
        *ptr++ = u3 + '0';
        ptr = ecb_i2a_09 (ptr, u2);
        ptr = ecb_i2a_09 (ptr, u1);
      }
  #else
    ptr = ecb_i2a_u64 (ptr, u);
  #endif

  return ptr;
}

/*******************************************************************************/
/* floating point stuff, can be disabled by defining ECB_NO_LIBM */

/* basically, everything uses "ieee pure-endian" floating point numbers */
/* the only noteworthy exception is ancient armle, which uses order 43218765 */
#if 0 \
    || __i386 || __i386__ \
    || ECB_GCC_AMD64 \
    || __powerpc__ || __ppc__ || __powerpc64__ || __ppc64__ \
    || defined __s390__ || defined __s390x__ \
    || defined __mips__ \
    || defined __alpha__ \
    || defined __hppa__ \
    || defined __ia64__ \
    || defined __m68k__ \
    || defined __m88k__ \
    || defined __sh__ \
    || defined _M_IX86 || defined ECB_MSVC_AMD64 || defined _M_IA64 \
    || (defined __arm__ && (defined __ARM_EABI__ || defined __EABI__ || defined __VFP_FP__ || defined _WIN32_WCE || defined __ANDROID__)) \
    || defined __aarch64__
  #define ECB_STDFP 1
#else
  #define ECB_STDFP 0
#endif

#ifndef ECB_NO_LIBM

  #include <math.h> /* for frexp*, ldexp*, INFINITY, NAN */

  /* only the oldest of old doesn't have this one. solaris. */
  #ifdef INFINITY
    #define ECB_INFINITY INFINITY
  #else
    #define ECB_INFINITY HUGE_VAL
  #endif

  #ifdef NAN
    #define ECB_NAN NAN
  #else
    #define ECB_NAN ECB_INFINITY
  #endif

  #if ECB_C99 || _XOPEN_VERSION >= 600 || _POSIX_VERSION >= 200112L
    #define ecb_ldexpf(x,e) ldexpf ((x), (e))
    #define ecb_frexpf(x,e) frexpf ((x), (e))
  #else
    #define ecb_ldexpf(x,e) (float) ldexp ((double) (x), (e))
    #define ecb_frexpf(x,e) (float) frexp ((double) (x), (e))
  #endif

  /* convert a float to ieee single/binary32 */
  ecb_function_ ecb_const uint32_t ecb_float_to_binary32 (float x);
  ecb_function_ ecb_const uint32_t ecb_float_to_binary32 (float x)
  {
    uint32_t r;

    #if ECB_STDFP
      memcpy (&r, &x, 4);
    #else
      /* slow emulation, works for anything but -0 */
      uint32_t m;
      int e;

      if (x == 0e0f                    ) return 0x00000000U;
      if (x > +3.40282346638528860e+38f) return 0x7f800000U;
      if (x < -3.40282346638528860e+38f) return 0xff800000U;
      if (x != x                       ) return 0x7fbfffffU;

      m = ecb_frexpf (x, &e) * 0x1000000U;

      r = m & 0x80000000U;

      if (r)
        m = -m;

      if (e <= -126)
        {
          m &= 0xffffffU;
          m >>= (-125 - e);
          e = -126;
        }

      r |= (e + 126) << 23;
      r |= m & 0x7fffffU;
    #endif

    return r;
  }

  /* converts an ieee single/binary32 to a float */
  ecb_function_ ecb_const float ecb_binary32_to_float (uint32_t x);
  ecb_function_ ecb_const float ecb_binary32_to_float (uint32_t x)
  {
    float r;

    #if ECB_STDFP
      memcpy (&r, &x, 4);
    #else
      /* emulation, only works for normals and subnormals and +0 */
      int neg = x >> 31;
      int e = (x >> 23) & 0xffU;

      x &= 0x7fffffU;

      if (e)
        x |= 0x800000U;
      else
        e = 1;

      /* we distrust ldexpf a bit and do the 2**-24 scaling by an extra multiply */
      r = ecb_ldexpf (x * (0.5f / 0x800000U), e - 126);

      r = neg ? -r : r;
    #endif

    return r;
  }

  /* convert a double to ieee double/binary64 */
  ecb_function_ ecb_const uint64_t ecb_double_to_binary64 (double x);
  ecb_function_ ecb_const uint64_t ecb_double_to_binary64 (double x)
  {
    uint64_t r;

    #if ECB_STDFP
      memcpy (&r, &x, 8);
    #else
      /* slow emulation, works for anything but -0 */
      uint64_t m;
      int e;

      if (x == 0e0                     ) return 0x0000000000000000U;
      if (x > +1.79769313486231470e+308) return 0x7ff0000000000000U;
      if (x < -1.79769313486231470e+308) return 0xfff0000000000000U;
      if (x != x                       ) return 0X7ff7ffffffffffffU;

      m = frexp (x, &e) * 0x20000000000000U;

      r = m & 0x8000000000000000;;

      if (r)
        m = -m;

      if (e <= -1022)
        {
          m &= 0x1fffffffffffffU;
          m >>= (-1021 - e);
          e = -1022;
        }

      r |= ((uint64_t)(e + 1022)) << 52;
      r |= m & 0xfffffffffffffU;
    #endif

    return r;
  }

  /* converts an ieee double/binary64 to a double */
  ecb_function_ ecb_const double ecb_binary64_to_double (uint64_t x);
  ecb_function_ ecb_const double ecb_binary64_to_double (uint64_t x)
  {
    double r;

    #if ECB_STDFP
      memcpy (&r, &x, 8);
    #else
      /* emulation, only works for normals and subnormals and +0 */
      int neg = x >> 63;
      int e = (x >> 52) & 0x7ffU;

      x &= 0xfffffffffffffU;

      if (e)
        x |= 0x10000000000000U;
      else
        e = 1;

      /* we distrust ldexp a bit and do the 2**-53 scaling by an extra multiply */
      r = ldexp (x * (0.5 / 0x10000000000000U), e - 1022);

      r = neg ? -r : r;
    #endif

    return r;
  }

  /* convert a float to ieee half/binary16 */
  ecb_function_ ecb_const uint16_t ecb_float_to_binary16 (float x);
  ecb_function_ ecb_const uint16_t ecb_float_to_binary16 (float x)
  {
    return ecb_binary32_to_binary16 (ecb_float_to_binary32 (x));
  }

  /* convert an ieee half/binary16 to float */
  ecb_function_ ecb_const float ecb_binary16_to_float (uint16_t x);
  ecb_function_ ecb_const float ecb_binary16_to_float (uint16_t x)
  {
    return ecb_binary32_to_float (ecb_binary16_to_binary32 (x));
  }

#endif

#endif

