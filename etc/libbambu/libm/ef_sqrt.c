/**
 * Porting of the libm library to the PandA framework
 * starting from the original FDLIBM 5.3 (Freely Distributable LIBM) developed by SUN
 * plus the newlib version 1.19 from RedHat and plus uClibc version 0.9.32.1 developed by Erik Andersen.
 * The author of this port is Fabrizio Ferrandi from Politecnico di Milano.
 * The porting fall under the LGPL v2.1, see the files COPYING.LIB and COPYING.LIBM_PANDA in this directory.
 * Date: September, 11 2013.
 */
/* ef_sqrtf.c -- float version of e_sqrt.c.
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

#include "math_privatef.h"

static const float one = 1.0, tiny = 1.0e-30;

float __hide_ieee754_sqrtf(float x) __attribute__((optimize("-fno-unsafe-math-optimizations")));
float __hide_ieee754_sqrtf(float x)
{
   float z;
   unsigned r, hx;
   int ix, s, q, m, t, i;

   GET_FLOAT_WORD(ix, x);
   hx = ix & 0x7fffffff;
   if(FLT_UWORD_IS_NAN(hx)) /* sqrt(NaN)=NaN */
      return __builtin_nanf("");
   /* take care of zero and -ves */
   if(FLT_UWORD_IS_ZERO(hx))
      return x; /* sqrt(+-0) = +-0 */
   if(ix < 0)
      return __builtin_nanf(""); /* sqrt(-ve) = sNaN */
   /* take care of +Inf  */
   if(!FLT_UWORD_IS_FINITE(hx))
      return __builtin_inff(); /* sqrt(+inf)=+inf */

   /* normalize x */
   m = (ix >> 23);
   if(FLT_UWORD_IS_SUBNORMAL(hx))
   { /* subnormal x */
      for(i = 0; (ix & 0x00800000L) == 0; i++)
         ix <<= 1;
      m -= i - 1;
   }
   m -= 127; /* unbias exponent */
   ix = (ix & 0x007fffffL) | 0x00800000L;
   if(m & 1) /* odd m, double x to make it even */
      ix += ix;
   m >>= 1; /* m = [m/2] */

   /* generate sqrt(x) bit by bit */
   ix += ix;
   q = s = 0;       /* q = sqrt(x) */
   r = 0x01000000L; /* r = moving bit from right to left */

   while(r != 0)
   {
      t = s + r;
      if(t <= ix)
      {
         s = t + r;
         ix -= t;
         q += r;
      }
      ix += ix;
      r >>= 1;
   }

   /* use floating add to find out rounding direction */
   if(ix != 0)
   {
      z = one - tiny; /* trigger inexact flag */
      if(z >= one)
      {
         z = one + tiny;
         if(z > one)
            q += 2;
         else
            q += (q & 1);
      }
   }
   ix = (q >> 1) + 0x3f000000L;
   ix += (m << 23);
   SET_FLOAT_WORD(z, ix);
   return z;
}
