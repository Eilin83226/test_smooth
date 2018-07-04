//
// MATLAB Compiler: 6.1 (R2015b)
// Date: Sat Jun 09 20:50:37 2018
// Arguments: "-B" "macro_default" "-W" "cpplib:QTbsxfun" "-T" "link:lib" "-d"
// "C:\Users\Eilin\Documents\MATLAB\BACF\BACF_toUpload\QTbsxfun\for_testing"
// "-v" "C:\Users\Eilin\Documents\MATLAB\BACF\BACF_toUpload\QTbsxfun.m" 
//

#ifndef __QTbsxfun_h
#define __QTbsxfun_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_QTbsxfun
#define PUBLIC_QTbsxfun_C_API __global
#else
#define PUBLIC_QTbsxfun_C_API /* No import statement needed. */
#endif

#define LIB_QTbsxfun_C_API PUBLIC_QTbsxfun_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_QTbsxfun
#define PUBLIC_QTbsxfun_C_API __declspec(dllexport)
#else
#define PUBLIC_QTbsxfun_C_API __declspec(dllimport)
#endif

#define LIB_QTbsxfun_C_API PUBLIC_QTbsxfun_C_API


#else

#define LIB_QTbsxfun_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_QTbsxfun_C_API 
#define LIB_QTbsxfun_C_API /* No special import/export declaration */
#endif

extern LIB_QTbsxfun_C_API 
bool MW_CALL_CONV QTbsxfunInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_QTbsxfun_C_API 
bool MW_CALL_CONV QTbsxfunInitialize(void);

extern LIB_QTbsxfun_C_API 
void MW_CALL_CONV QTbsxfunTerminate(void);



extern LIB_QTbsxfun_C_API 
void MW_CALL_CONV QTbsxfunPrintStackTrace(void);

extern LIB_QTbsxfun_C_API 
bool MW_CALL_CONV mlxQTbsxfun(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_QTbsxfun
#define PUBLIC_QTbsxfun_CPP_API __declspec(dllexport)
#else
#define PUBLIC_QTbsxfun_CPP_API __declspec(dllimport)
#endif

#define LIB_QTbsxfun_CPP_API PUBLIC_QTbsxfun_CPP_API

#else

#if !defined(LIB_QTbsxfun_CPP_API)
#if defined(LIB_QTbsxfun_C_API)
#define LIB_QTbsxfun_CPP_API LIB_QTbsxfun_C_API
#else
#define LIB_QTbsxfun_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_QTbsxfun_CPP_API void MW_CALL_CONV QTbsxfun(int nargout, mwArray& b, const mwArray& a, const mwArray& c);

#endif
#endif
