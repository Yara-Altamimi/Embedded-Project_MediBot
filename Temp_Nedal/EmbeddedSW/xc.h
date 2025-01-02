/*
 Copyright (C) 2006-2007 M.A.L. Marques

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 3 of the License, or
 (at your option) any later version.
  
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
  
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _XC_H
#define _XC_H

#ifdef __cplusplus
extern "C" {
#endif

#if SINGLE_PRECISION
#  define FLOAT float
#  define POW   powf
#  define LOG   logf
#  define ASINH asinhf
#  define ABS   fabsf
#ifdef HAVE_SQRTF
#  define SQRT  sqrtf
#else
#  define SQRT  sqrt
#endif
#  define XC(x) xc_s_ ## x
#  define XC_U(X) XC_S_ ## X
#  define FLOAT_EPSILON FLT_EPSILON
#  define FLOAT_MIN FLT_MIN
#  define FLOAT_MAX FLT_MAX
#ifdef HAVE_CBRTF
#define CBRT cbrtf
#elif defined(HAVE_CBRT)
#define CBRT cbrt
#else
#define CBRT(x) powf((x), 1.0/3.0)
#endif
#else
#  define FLOAT double
#  define POW   pow
#  define LOG   log
#  define ASINH asinh
#  define ABS   fabs
#  define SQRT  sqrt
#  define XC(x) xc_ ## x
#  define XC_U(X) XC_ ## X
#  define FLOAT_EPSILON DBL_EPSILON
#  define FLOAT_MIN DBL_MIN
#  define FLOAT_MAX DBL_MAX
#ifdef HAVE_CBRT
#define CBRT cbrt
#else
#define CBRT(x) pow((x), 1.0/3.0)
#endif
#endif

#define XC_FC_FUNC2(a,b) FC_FUNC_(a,b)
#define XC_FC_FUNC(a,b) XC_FC_FUNC2(XC(a), XC_U(b))
  
#define XC_UNPOLARIZED          1
#define XC_POLARIZED            2

#define XC_NON_RELATIVISTIC     0
#define XC_RELATIVISTIC         1

#define XC_EXCHANGE             0
#define XC_CORRELATION          1
#define XC_EXCHANGE_CORRELATION 2
#define XC_KINETIC              3

#define XC_FAMILY_UNKNOWN      -1
#define XC_FAMILY_LDA           1
#define XC_FAMILY_GGA           2
#define XC_FAMILY_MGGA          4
#define XC_FAMILY_LCA           8
#define XC_FAMILY_OEP          16
#define XC_FAMILY_HYB_GGA      32

/* flags that can be used in info.flags */
#define XC_FLAGS_HAVE_EXC         (1 <<  0) /*    1 */
#define XC_FLAGS_HAVE_VXC         (1 <<  1) /*    2 */
#define XC_FLAGS_HAVE_FXC         (1 <<  2) /*    4 */
#define XC_FLAGS_HAVE_KXC         (1 <<  3) /*    8 */
#define XC_FLAGS_HAVE_LXC         (1 <<  4) /*   16 */
#define XC_FLAGS_1D               (1 <<  5) /*   32 */
#define XC_FLAGS_2D               (1 <<  6) /*   64 */
#define XC_FLAGS_3D               (1 <<  7) /*  128 */
#define XC_FLAGS_STABLE           (1 <<  9) /*  512 */
#define XC_FLAGS_DEVELOPMENT      (1 << 10) /* 1024 */

#define XC_TAU_EXPLICIT         0
#define XC_TAU_EXPANSION        1

  /* This value was redefined as XC_GGA_X_LB, we define it here to
     keep compatibility. */
#define XC_GGA_XC_LB          160

typedef struct{
  int   number;   /* indentifier number */
  int   kind;     /* XC_EXCHANGE or XC_CORRELATION */

  char *name;     /* name of the functional, e.g. "PBE" */
  int   family;   /* type of the functional, e.g. XC_FAMILY_GGA */
  char *refs;     /* references                       */

  int   flags;    /* see above for a list of possible flags */

  void (*init)(void *p);
  void (*end) (void *p);
  void (*lda) (const void *p, int np, const FLOAT *rho, 
               FLOAT *zk, FLOAT *vrho, FLOAT *v2rho2, FLOAT *v3rho3);
  void (*gga) (const void *p, int np, const FLOAT *rho, const FLOAT *sigma, 
               FLOAT *zk, FLOAT *vrho, FLOAT *vsigma,
               FLOAT *v2rho2, FLOAT *v2rhosigma, FLOAT *v2sigma2);
  void (*mgga)(const void *p, int np, const FLOAT *rho, const FLOAT *sigma, const FLOAT *lapl_rho, const FLOAT *tau,
               FLOAT *zk, FLOAT *vrho, FLOAT *vsigma, FLOAT *vlapl_rho, FLOAT *vtau,
               FLOAT *v2rho2, FLOAT *v2sigma2, FLOAT *v2tau2, FLOAT *v2lapl2,
               FLOAT *v2rhosigma, FLOAT *v2rhotau, FLOAT *v2rholapl, 
               FLOAT *v2sigmatau, FLOAT *v2sigmalapl, FLOAT *v2taulapl);
} XC(func_info_type);


struct XC(struct_lda_type);
struct XC(struct_gga_type);
struct XC(struct_mgga_type);

typedef struct XC(struct_func_type){
  const XC(func_info_type) *info;       /* all the information concerning this functional */
  int nspin;                            /* this is a copy from the underlying functional */

  struct XC(struct_lda_type)  *lda;
  struct XC(struct_gga_type)  *gga;
  struct XC(struct_mgga_type) *mgga;
} XC(func_type);


/* functionals */
int  XC(family_from_id)(int id, int *family, int *number);
int  XC(func_init)(XC(func_type) *p, int functional, int nspin);
void XC(func_end)(XC(func_type) *p);

/*
 Copyright (C) 2006-2007 M.A.L. Marques

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* config.h.in.  Generated from configure.ac by autoheader.  */

/* The C type of a Fortran integer */
#undef CC_FORTRAN_INT

/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
#undef CRAY_STACKSEG_END

/* Define to 1 if using `alloca.c'. */
#undef C_ALLOCA

/* compiler supports line-number lines */
#undef F90_ACCEPTS_LINE_NUMBERS

/* Define to dummy `main' function (if any) required to link to the Fortran
   libraries. */
#undef FC_DUMMY_MAIN

/* Define if F77 and FC dummy `main' functions are identical. */
#undef FC_DUMMY_MAIN_EQ_F77

/* Define to a macro mangling the given C identifier (in lower and upper
   case), which must not contain underscores, for linking with Fortran. */
#undef FC_FUNC

/* As FC_FUNC, but for C identifiers containing underscores. */
#undef FC_FUNC_

/* The size of a Fortran integer */
#undef FC_INTEGER_SIZE

/* Define to 1 if you have `alloca', as a function or macro. */
#undef HAVE_ALLOCA

/* Define to 1 if you have <alloca.h> and it should be used (not on Ultrix).
   */
#undef HAVE_ALLOCA_H

/* libm includes cbrt */
#undef HAVE_CBRT

/* libm includes cbrtf */
#undef HAVE_CBRTF

/* Define to 1 if you have the <dlfcn.h> header file. */
#undef HAVE_DLFCN_H

/* Defined if libxc is compiled with fortran support */
#undef HAVE_FORTRAN

/* Define to 1 if you have the <inttypes.h> header file. */
#undef HAVE_INTTYPES_H

/* Define to 1 if you have the <memory.h> header file. */
#undef HAVE_MEMORY_H

/* libm includes sqrtf */
#undef HAVE_SQRTF

/* Define to 1 if you have the <stdint.h> header file. */
#undef HAVE_STDINT_H

/* Define to 1 if you have the <stdlib.h> header file. */
#undef HAVE_STDLIB_H

/* Define to 1 if you have the <strings.h> header file. */
#undef HAVE_STRINGS_H

/* Define to 1 if you have the <string.h> header file. */
#undef HAVE_STRING_H

/* Define to 1 if you have the <sys/stat.h> header file. */
#undef HAVE_SYS_STAT_H

/* Define to 1 if you have the <sys/types.h> header file. */
#undef HAVE_SYS_TYPES_H

/* Define to 1 if you have the <unistd.h> header file. */
#undef HAVE_UNISTD_H

/* compiler supports long lines */
#undef LONG_LINES

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#undef LT_OBJDIR

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
#undef NO_MINUS_C_MINUS_O

/* Name of package */
#undef PACKAGE

/* Define to the address where bug reports for this package should be sent. */
#undef PACKAGE_BUGREPORT

/* Define to the full name of this package. */
#undef PACKAGE_NAME

/* Define to the full name and version of this package. */
#undef PACKAGE_STRING

/* Define to the one symbol short name of this package. */
#undef PACKAGE_TARNAME

/* Define to the home page for this package. */
#undef PACKAGE_URL

/* Define to the version of this package. */
#undef PACKAGE_VERSION

/* The size of `void*', as computed by sizeof. */
#undef SIZEOF_VOIDP

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at runtime.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown */
#undef STACK_DIRECTION

/* Define to 1 if you have the ANSI C header files. */
#undef STDC_HEADERS

/* Version number of package */
#undef VERSION

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
#undef inline
#endif

/* Define to `unsigned int' if <sys/types.h> does not define. */
#undef size_t

#ifdef HAVE_FORTRAN


/*
 Copyright (C) 2003 M. Marques, A. Castro, A. Rubio, G. Bertsch

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2, or (at your option)
 any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 02111-1307, USA.

 $Id: string_f.h 3341 2007-10-12 15:47:30Z marques $
*/

/* --------------------- Fortran to C string compatibility ---------------------- */
#include <stdlib.h>

#if defined(_CRAY)
#include <fortran.h>

#define to_c_str(f, c) {				    \
  char *fc; int slen;                                       \
  fc = _fcdtocp(f);                                         \
  for(slen=_fcdlen(f)-1; slen>=0 && fc[slen]==' '; slen--); \
  slen++;                                                   \
  c = (char *)malloc(slen+1);                               \
  strncpy(c, _fcdtocp(f), slen);                            \
  c[slen] = '\0';                                           \
}

#define to_f_str(c, f) {          \
  char *fc;  int flen, clen, i;   \
  flen = _fcdlen(f);              \
  fc = _fcdtocp(f);               \
  clen = strlen(c);               \
  for(i=0; i<clen && i<flen; i++) \
    fc[i] = c[i];                 \
  for(; i<flen; i++)              \
    fc[i] = ' ';                  \
}

#define STR_F_TYPE _fcd
#define TO_C_STR1(s, c) to_c_str(s, c)
#define TO_C_STR2(s, c) to_c_str(s, c)
#define TO_C_STR3(s, c) to_c_str(s, c)
#define TO_F_STR1(c, f) to_f_str(c, f)
#define TO_F_STR2(c, f) to_f_str(c, f)
#define TO_F_STR3(c, f) to_f_str(c, f)
#define STR_ARG1
#define STR_ARG2
#define STR_ARG3

#else

#define to_c_str(f, c, l) {		   \
  int i, ll;                               \
  ll = (int)l;                             \
  for(ll--; ll>=0; ll--)                   \
    if(f[ll] != ' ') break;                \
  ll++;                                    \
  c = (char *)malloc((ll+1)*sizeof(char)); \
  for(i=0; i<ll; i++) c[i] = f[i];         \
  c[i] = '\0';                             \
}

#define to_f_str(c, f, l) {                \
  int i, ll;                               \
  ll = (int)l;                             \
  for(i=0; i<ll && c[i]!='\0'; i++)        \
    f[i] = c[i];                           \
  for(; i<ll; i++)                         \
    f[i] = ' ';                            \
}


#define STR_F_TYPE char *
#define TO_C_STR1(s, c) to_c_str(s, c, l1)
#define TO_C_STR2(s, c) to_c_str(s, c, l2)
#define TO_C_STR3(s, c) to_c_str(s, c, l3)
#define TO_F_STR1(c, f) to_f_str(c, f, l1)
#define TO_F_STR2(c, f) to_f_str(c, f, l2)
#define TO_F_STR3(c, f) to_f_str(c, f, l3)
#define STR_ARG1     , unsigned long l1
#define STR_ARG2     , unsigned long l1, unsigned long l2
#define STR_ARG3     , unsigned long l1, unsigned long l2, unsigned long l3

#endif

/* info */

CC_FORTRAN_INT XC_FC_FUNC(f90_info_number, F90_INFO_NUMBER)
     (void **info)
{
  return (CC_FORTRAN_INT) ((XC(func_info_type) *)(*info))->number;
}


CC_FORTRAN_INT XC_FC_FUNC(f90_info_kind, F90_INFO_KIND)
     (void **info)
{
  return (CC_FORTRAN_INT) ((XC(func_info_type) *)(*info))->kind;
}


void XC_FC_FUNC(f90_info_name, F90_INFO_NAME)
     (void **info, STR_F_TYPE s STR_ARG1)
{
  TO_F_STR1(((XC(func_info_type) *)(*info))->name, s);
}


CC_FORTRAN_INT  XC_FC_FUNC(f90_info_family, F90_INFO_FAMILY)
     (void **info)
{
  return (CC_FORTRAN_INT) ((XC(func_info_type) *)(*info))->family;
}

CC_FORTRAN_INT  XC_FC_FUNC(f90_info_flags, F90_INFO_FLAGS)
     (void **info)
{
  return (CC_FORTRAN_INT) ((XC(func_info_type) *)(*info))->flags;
}

void XC_FC_FUNC(f90_info_refs, F90_INFO_REFS)
  (void **info, CC_FORTRAN_INT *number, char **s, STR_F_TYPE ref_f STR_ARG1)
{
  char *c, ref[256]; /* hopefully no ref is longer than 256 characters ;) */
  XC(func_info_type) *func_p = (XC(func_info_type) *)(*info);

  if(*number == 0) *s = func_p->refs;

  if(*s == NULL || **s == '\0'){
    *number = -1;
    return;
  }

  for(c=ref; **s!='\0' && **s!='\n'; (*s)++, c++)
    *c = **s;
  *c = '\0';
  if(**s=='\n') (*s)++;

  TO_F_STR1(ref, ref_f);

  (*number)++;
  fflush(stdout);
}

/* functionals */
CC_FORTRAN_INT  XC_FC_FUNC(f90_family_from_id, F90_FAMILY_FROM_ID)
  (CC_FORTRAN_INT  *functional)
{
  return (CC_FORTRAN_INT) XC(family_from_id)((int) (*functional), NULL, NULL);
}

/* Standard initialization */
void XC_FC_FUNC(f90_func_init, F90_FUNC_INIT)
     (void **p, void **info, CC_FORTRAN_INT *functional, CC_FORTRAN_INT *nspin)
{
  XC(func_type) *func_p;

  func_p = (XC(func_type) *)malloc(sizeof(XC(func_type)));
  XC(func_init)(func_p, (int) (*functional), (int) (*nspin));

  *p    = (void *) func_p;
  *info = (void *)(func_p->info);
}

void XC_FC_FUNC(f90_func_end, F90_FUNC_END)
     (void **p)
{
  XC(func_end)((XC(func_type) *)(*p));
  free(*p);
  *p = NULL;
}


/* LDAs */

void XC_FC_FUNC(f90_lda, F90_LDA)
     (void **p, CC_FORTRAN_INT *np, FLOAT *rho,
      FLOAT *zk, FLOAT *vrho, FLOAT *v2rho2, FLOAT *v3rho3)
{
  XC(lda)((XC(func_type) *)(*p), *np, rho, zk, vrho, v2rho2, v3rho3);
}

void XC_FC_FUNC(f90_lda_exc, F90_LDA_EXC)
     (void **p, CC_FORTRAN_INT *np, FLOAT *rho,
      FLOAT *zk)
{
  XC(lda)((XC(func_type) *)(*p), *np, rho, zk, NULL, NULL, NULL);
}

void XC_FC_FUNC(f90_lda_exc_vxc, F90_LDA_EXC_VXC)
     (void **p, CC_FORTRAN_INT *np, FLOAT *rho,
      FLOAT *zk, FLOAT *vrho)
{
  XC(lda)((XC(func_type) *)(*p), *np, rho, zk, vrho, NULL, NULL);
}

void XC_FC_FUNC(f90_lda_vxc, F90_LDA_VXC)
     (void **p, CC_FORTRAN_INT *np, FLOAT *rho,
      FLOAT *vrho)
{
  XC(lda)((XC(func_type) *)(*p), *np, rho, NULL, vrho, NULL, NULL);
}

void XC_FC_FUNC(f90_lda_fxc, F90_LDA_FXC)
     (void **p, CC_FORTRAN_INT *np, FLOAT *rho,
      FLOAT *v2rho2)
{
  XC(lda)((XC(func_type) *)(*p), *np, rho, NULL, NULL, v2rho2, NULL);
}

void XC_FC_FUNC(f90_lda_kxc, F90_LDA_KXC)
     (void **p, CC_FORTRAN_INT *np, FLOAT *rho,
      FLOAT *v3rho3)
{
  XC(lda)((XC(func_type) *)(*p), *np, rho, NULL, NULL, NULL, v3rho3);
}


/* Now come some special initializations */

/* parameter of LDA_1D */
void XC_FC_FUNC(f90_lda_x_1d_set_par, F90_LDA_X_1D_SET_PAR)
  (void **p, CC_FORTRAN_INT *interaction, FLOAT *bb)
{
  XC(lda_x_1d_set_params)((XC(func_type) *)(*p), *interaction, *bb);
}

/* parameter of Xalpha */
void XC_FC_FUNC(f90_lda_c_xalpha_set_par, F90_LDA_C_XALPHA_SET_PAR)
  (void **p, FLOAT *alpha)
{
  XC(lda_c_xalpha_set_params)((XC(func_type) *)(*p), *alpha);
}

/* relativistic option of LDA_X */
void XC_FC_FUNC(f90_lda_x_set_par, F90_LDA_X_SET_PAR)
  (void **p, CC_FORTRAN_INT *relativistic)
{
  XC(lda_x_set_params)((XC(func_type) *)(*p), *relativistic);
}

/* parameter of CSC */
void XC_FC_FUNC(f90_lda_c_1d_csc_set_par, F90_LDA_C_1D_CSC_SET_PAR)
  (void **p, CC_FORTRAN_INT *interaction, FLOAT *bb)
{
  XC(lda_c_1d_csc_set_params)((XC(func_type) *)(*p), *interaction, *bb);
}

/* parameter of PRM */
void XC_FC_FUNC(f90_lda_c_2d_prm_set_par, F90_LDA_C_2D_PRM_SET_PAR)
  (void **p, FLOAT *N)
{
  XC(lda_c_2d_prm_set_params)((XC(func_type) *)(*p), *N);
}


/* GGAs */

void XC_FC_FUNC(f90_gga, F90_GGA)
     (void **p, CC_FORTRAN_INT *np, FLOAT *rho, FLOAT *sigma,
      FLOAT *zk, FLOAT *vrho, FLOAT *vsigma,
      FLOAT *v2rho2, FLOAT *v2rhosigma, FLOAT *v2sigma2)
{
  XC(gga)((XC(func_type) *)(*p), *np, rho, sigma, zk, vrho, vsigma, v2rho2, v2rhosigma, v2sigma2);
}

void XC_FC_FUNC(f90_gga_exc, F90_GGA_EXC)
     (void **p, CC_FORTRAN_INT *np, FLOAT *rho, FLOAT *sigma,
      FLOAT *zk)
{
  XC(gga)((XC(func_type) *)(*p), *np, rho, sigma, zk, NULL, NULL, NULL, NULL, NULL);
}

void XC_FC_FUNC(f90_gga_exc_vxc, F90_GGA_EXC_VXC)
     (void **p, CC_FORTRAN_INT *np, FLOAT *rho, FLOAT *sigma,
      FLOAT *zk, FLOAT *vrho, FLOAT *vsigma)
{
  XC(gga)((XC(func_type) *)(*p), *np, rho, sigma, zk, vrho, vsigma, NULL, NULL, NULL);
}

void XC_FC_FUNC(f90_gga_vxc, F90_GGA_VXC)
     (void **p, CC_FORTRAN_INT *np, FLOAT *rho, FLOAT *sigma,
      FLOAT *vrho, FLOAT *vsigma)
{
  XC(gga)((XC(func_type) *)(*p), *np, rho, sigma, NULL, vrho, vsigma, NULL, NULL, NULL);
}

void XC_FC_FUNC(f90_gga_fxc, F90_GGA_FXC)
     (void **p, CC_FORTRAN_INT *np, FLOAT *rho, FLOAT *sigma,
      FLOAT *v2rho2, FLOAT *v2rhosigma, FLOAT *v2sigma2)
{
  XC(gga)((XC(func_type) *)(*p), *np, rho, sigma, NULL, NULL, NULL, v2rho2, v2rhosigma, v2sigma2);
}

/* the van Leeuwen & Baerends functional is special */
void XC_FC_FUNC(f90_gga_lb_set_par, F90_GGA_LB_SET_PAR)
  (void **p, CC_FORTRAN_INT *modified, FLOAT *threshold, FLOAT *ip, FLOAT *qtot)
{
  XC(gga_lb_set_params)((XC(func_type) *)(*p), *modified, *threshold, *ip, *qtot);
}

void XC_FC_FUNC(f90_gga_lb_modified, F90_GGA_LB_MODIFIED)
     (void **p, CC_FORTRAN_INT *np, FLOAT *rho, FLOAT *sigma, FLOAT *r, FLOAT *vrho)
{
  const XC(gga_type) *gga = ((XC(func_type) *)(*p))->gga;
  assert(gga != NULL);

  XC(gga_lb_modified)(gga, *np, rho, sigma, *r, vrho);
}


void XC_FC_FUNC(f90_hyb_gga_exx_coef, F90_HYB_GGA_EXX_COEF)
   (void **p, FLOAT *coef)
{
   const XC(gga_type) *gga = ((XC(func_type) *)(*p))->gga;
   *coef = XC(hyb_gga_exx_coef)(gga);
}


/* meta-GGAs */

void XC_FC_FUNC(f90_mgga, F90_MGGA)
     (void **p, CC_FORTRAN_INT *np, FLOAT *rho, FLOAT *sigma, FLOAT *lapl, FLOAT *tau,
      FLOAT *zk, FLOAT *vrho, FLOAT *vsigma, FLOAT *vlapl, FLOAT *vtau,
      FLOAT *v2rho2, FLOAT *v2sigma2, FLOAT *v2lapl2, FLOAT *v2tau2,
      FLOAT *v2rhosigma, FLOAT *v2rholapl, FLOAT *v2rhotau,
      FLOAT *v2sigmalapl, FLOAT *v2sigmatau, FLOAT *v2lapltau)
{
  XC(mgga)((XC(func_type) *)(*p), *np, rho, sigma, lapl, tau,
	   zk, vrho, vsigma, vlapl, vtau,
	   v2rho2, v2sigma2, v2lapl2, v2tau2, v2rhosigma, v2rholapl, v2rhotau,
	   v2sigmalapl, v2sigmatau, v2lapltau);

}

void XC_FC_FUNC(f90_mgga_exc, F90_MGGA_EXC)
     (void **p, CC_FORTRAN_INT *np, FLOAT *rho, FLOAT *sigma, FLOAT *lapl, FLOAT *tau,
      FLOAT *zk)
{
  XC(mgga)((XC(func_type) *)(*p), *np, rho, sigma, lapl, tau,
	   zk, NULL, NULL, NULL, NULL,
	   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

void XC_FC_FUNC(f90_mgga_exc_vxc, F90_MGGA_EXC_VXC)
  (void **p, CC_FORTRAN_INT *np, FLOAT *rho, FLOAT *sigma, FLOAT *lapl, FLOAT *tau,
   FLOAT *zk, FLOAT *vrho, FLOAT *vsigma, FLOAT *vlapl, FLOAT *vtau)
{
  XC(mgga)((XC(func_type) *)(*p), *np, rho, sigma, lapl, tau,
	   zk, vrho, vsigma, vlapl, vtau,
	   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

void XC_FC_FUNC(f90_mgga_vxc, F90_MGGA_VXC)
  (void **p, CC_FORTRAN_INT *np, FLOAT *rho, FLOAT *sigma, FLOAT *lapl, FLOAT *tau,
   FLOAT *vrho, FLOAT *vsigma, FLOAT *vlapl, FLOAT *vtau)
{
  XC(mgga)((XC(func_type) *)(*p), *np, rho, sigma, lapl, tau,
	   NULL, vrho, vsigma, vlapl, vtau,
	   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

void XC_FC_FUNC(f90_mgga_fxc, F90_MGGA_FXC)
  (void **p, CC_FORTRAN_INT *np, FLOAT *rho, FLOAT *sigma, FLOAT *lapl, FLOAT *tau,
      FLOAT *v2rho2, FLOAT *v2sigma2, FLOAT *v2lapl2, FLOAT *v2tau2,
      FLOAT *v2rhosigma, FLOAT *v2rholapl, FLOAT *v2rhotau,
      FLOAT *v2sigmalapl, FLOAT *v2sigmatau, FLOAT *v2lapltau)
{
  XC(mgga)((XC(func_type) *)(*p), *np, rho, sigma, lapl, tau,
	   NULL, NULL, NULL, NULL, NULL,
	   v2rho2, v2sigma2, v2lapl2, v2tau2, v2rhosigma, v2rholapl, v2rhotau,
	   v2sigmalapl, v2sigmatau, v2lapltau);
}

/* parameter of TP09 */
void XC_FC_FUNC(f90_mgga_x_tb09_set_par, F90_MGGA_X_TB09_SET_PAR)
  (void **p, FLOAT *cc)
{
  XC(mgga_x_tb09_set_params)((XC(func_type) *)(*p), *cc);
}


/* LCAs */

void XC_FC_FUNC(f90_lca, F90_LCA)
     (void **p, FLOAT *rho, FLOAT *v,
      FLOAT *e, FLOAT *dedd, FLOAT *dedv)
{
  XC(lca)((XC(lca_type) *)(*p), rho, v, e, dedd, dedv);
}

#endif

/* the LDAs */
typedef struct XC(struct_lda_type) {
  const XC(func_info_type) *info;       /* all the information concerning this functional */
  int nspin;                            /* XC_UNPOLARIZED or XC_POLARIZED  */

  int func;                             /* Shortcut in case of several functionals sharing the same interface */
  int n_rho, n_zk, n_vrho, n_v2rho2, n_v3rho3; /* spin dimensions of arguments */

  void *params;                         /* this allows us to fix parameters in the functional */
} XC(lda_type);

int  XC(lda_init)(XC(func_type) *p, const XC(func_info_type) *info, int nspin);
void XC(lda_end) (XC(func_type) *p);

void XC(lda)        (const XC(func_type) *p, int np, const FLOAT *rho, FLOAT *zk, FLOAT *vrho, FLOAT *v2rho2, FLOAT *v3rho3);
void XC(lda_exc)    (const XC(func_type) *p, int np, const FLOAT *rho, FLOAT *zk);
void XC(lda_exc_vxc)(const XC(func_type) *p, int np, const FLOAT *rho, FLOAT *zk, FLOAT *vrho);
void XC(lda_vxc)    (const XC(func_type) *p, int np, const FLOAT *rho, FLOAT *vrho);
void XC(lda_fxc)    (const XC(func_type) *p, int np, const FLOAT *rho, FLOAT *v2rho2);
void XC(lda_kxc)    (const XC(func_type) *p, int np, const FLOAT *rho, FLOAT *v3rho3);

void XC(lda_x_1d_set_params)     (XC(func_type) *p, int interaction, FLOAT bb);
void XC(lda_c_1d_csc_set_params) (XC(func_type) *p, int interaction, FLOAT bb);
void XC(lda_c_xalpha_set_params) (XC(func_type) *p, FLOAT alpha);
void XC(lda_x_set_params)        (XC(func_type) *p, int relativistic);
void XC(lda_c_2d_prm_set_params) (XC(func_type) *p, FLOAT N);
void XC(lda_c_vwn_set_params)    (XC(func_type) *p, int spin_interpolation);


/* the GGAs */
typedef struct XC(struct_gga_type){
  const XC(func_info_type) *info;       /* which functional did we choose   */
  int nspin;                            /* XC_UNPOLARIZED or XC_POLARIZED   */
  
  int n_func_aux;                       /* how many auxiliary functions we need */
  XC(func_type) **func_aux;             /* most GGAs are based on a LDA or other GGAs  */
  FLOAT *mix_coef;                      /* coefficients for the mixing */

  FLOAT exx_coef;                       /* the Hartree-Fock mixing parameter for the hybrids */

  int func;                             /* Shortcut in case of several functionals sharing the same interface */
  int n_rho, n_zk, n_vrho, n_v2rho2;    /* spin dimensions of arguments */
  int n_sigma, n_vsigma, n_v2rhosigma, n_v2sigma2;

  void *params;                         /* this allows us to fix parameters in the functional */
} XC(gga_type);

int  XC(gga_init)(XC(func_type) *p, const XC(func_info_type) *info, int nspin);
void XC(gga_end) (XC(func_type) *p);
void XC(gga)     (const XC(func_type) *p, int np, const FLOAT *rho, const FLOAT *sigma, 
                  FLOAT *zk, FLOAT *vrho, FLOAT *vsigma,
                  FLOAT *v2rho2, FLOAT *v2rhosigma, FLOAT *v2sigma2);
void XC(gga_exc)(const XC(func_type) *p, int np, const FLOAT *rho, const FLOAT *sigma, 
                 FLOAT *zk);
void XC(gga_exc_vxc)(const XC(func_type) *p, int np, const FLOAT *rho, const FLOAT *sigma,
                     FLOAT *zk, FLOAT *vrho, FLOAT *vsigma);
void XC(gga_vxc)(const XC(func_type) *p, int np, const FLOAT *rho, const FLOAT *sigma,
                 FLOAT *vrho, FLOAT *vsigma);
void XC(gga_fxc)(const XC(func_type) *p, int np, const FLOAT *rho, const FLOAT *sigma,
                 FLOAT *v2rho2, FLOAT *v2rhosigma, FLOAT *v2sigma2);

void XC(gga_lb_modified)  (const XC(gga_type) *p, int np, const FLOAT *rho, const FLOAT *sigma, 
                           FLOAT r, FLOAT *vrho);

void XC(gga_x_b88_set_params) (XC(func_type) *p, FLOAT beta, FLOAT gamma);
void XC(gga_x_pbe_set_params) (XC(func_type) *p, FLOAT kappa, FLOAT mu);
void XC(gga_x_rpbe_set_params)(XC(func_type) *p, FLOAT kappa, FLOAT mu);
void XC(gga_c_lyp_set_params) (XC(func_type) *p, FLOAT A, FLOAT B, FLOAT c, FLOAT d);
void XC(gga_lb_set_params)    (XC(func_type) *p, int modified, FLOAT threshold, FLOAT ip, FLOAT qtot);
void XC(gga_k_tflw_set_params)(XC(func_type) *p, FLOAT gamma, FLOAT lambda, FLOAT N);

FLOAT XC(hyb_gga_exx_coef)(const XC(gga_type) *p);


/* the meta-GGAs */
typedef struct XC(struct_mgga_type){
  const XC(func_info_type) *info;       /* which functional did we choose   */
  int nspin;                            /* XC_UNPOLARIZED or XC_POLARIZED  */
  
  int n_func_aux;                       /* how many auxiliary functions we need */
  XC(func_type) **func_aux;             /* most GGAs are based on a LDA or other GGAs  */
  FLOAT *mix_coef;                      /* coefficients for the mixing */

  int func;                             /* Shortcut in case of several functionals sharing the same interface */

  int n_rho, n_sigma, n_tau, n_lapl,    /* spin dimensions of the arrays */
    n_zk, n_vrho, n_vsigma, n_vtau, n_vlapl,
    n_v2rho2, n_v2sigma2, n_v2tau2, n_v2lapl2,
    n_v2rhosigma, n_v2rhotau, n_v2rholapl, 
    n_v2sigmatau, n_v2sigmalapl, n_v2lapltau;
  
  void *params;                         /* this allows us to fix parameters in the functional */
} XC(mgga_type);

int  XC(mgga_init)(XC(func_type) *p, const XC(func_info_type) *info, int nspin);
void XC(mgga_end) (XC(func_type) *p);
void XC(mgga)        (const XC(func_type) *p, int np,
                      const FLOAT *rho, const FLOAT *sigma, const FLOAT *lapl, const FLOAT *tau,
                      FLOAT *zk, FLOAT *vrho, FLOAT *vsigma, FLOAT *vlapl, FLOAT *vtau,
                      FLOAT *v2rho2, FLOAT *v2sigma2, FLOAT *v2lapl2, FLOAT *v2tau2,
                      FLOAT *v2rhosigma, FLOAT *v2rholapl, FLOAT *v2rhotau, 
                      FLOAT *v2sigmalapl, FLOAT *v2sigmatau, FLOAT *v2lapltau);
void XC(mgga_exc)    (const XC(func_type) *p, int np,  
                      const FLOAT *rho, const FLOAT *sigma, const FLOAT *lapl, const FLOAT *tau, 
                      FLOAT *zk);
void XC(mgga_exc_vxc)(const XC(func_type) *p, int np, 
                      const FLOAT *rho, const FLOAT *sigma, const FLOAT *lapl, const FLOAT *tau,
                      FLOAT *zk, FLOAT *vrho, FLOAT *vsigma, FLOAT *vlapl, FLOAT *vtau);
void XC(mgga_vxc)    (const XC(func_type) *p, int np,
                      const FLOAT *rho, const FLOAT *sigma, const FLOAT *lapl, const FLOAT *tau,
                      FLOAT *vrho, FLOAT *vsigma, FLOAT *vlapl, FLOAT *vtau);
void XC(mgga_fxc)    (const XC(func_type) *p, int np, 
                      const FLOAT *rho, const FLOAT *sigma, const FLOAT *lapl, const FLOAT *tau,
                      FLOAT *v2rho2, FLOAT *v2sigma2, FLOAT *v2lapl2, FLOAT *v2tau2,
                      FLOAT *v2rhosigma, FLOAT *v2rholapl, FLOAT *v2rhotau, 
                      FLOAT *v2sigmalapl, FLOAT *v2sigmatau, FLOAT *v2lapltau);

void XC(mgga_set_handle_tau)(XC(func_type) *p, int handle_tau);
void XC(mgga_x_tb09_set_params)(XC(func_type) *p, FLOAT c);

/* Functionals that are defined as mixtures of others */
void XC(mix_func)(const XC(func_type) *dest_func, int n_func_aux, XC(func_type) **func_aux, FLOAT *mix_coef,
                  int np, const FLOAT *rho, const FLOAT *sigma,
                  FLOAT *zk, FLOAT *vrho, FLOAT *vsigma,
                  FLOAT *v2rho2, FLOAT *v2rhosigma, FLOAT *v2sigma2);
  
/* the LCAs */

#define XC_LCA_OMC            301 /* Orestes, Marcasso & Capelle */
#define XC_LCA_LCH            302 /* Lee, Colwell & Handy        */


typedef struct{
  XC(func_info_type) *info;  /* which functional did we choose   */
  int nspin;                 /* XC_UNPOLARIZED or XC_POLARIZED  */

} XC(lca_type);

void XC(lca_init)(XC(lca_type) *p, int functional, int nspin);
void XC(lca)     (XC(lca_type) *p, FLOAT *rho, FLOAT *v, FLOAT *e, FLOAT *dedd, FLOAT *dedv);

#ifdef __cplusplus
}
#endif

#endif