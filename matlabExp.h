//
// MATLAB Compiler: 6.1 (R2015b)
// Date: Tue Jun 19 01:16:39 2018
// Arguments: "-B" "macro_default" "-W" "cpplib:matlabExp" "-T" "link:lib" "-d"
// "C:\Users\Eilin\Documents\MATLAB\matlabExp\for_testing" "-v"
// "C:\Users\Eilin\Documents\MATLAB\BACF\BACF_toUpload\QTexp_only.m" 
//

#ifndef __matlabExp_h
#define __matlabExp_h 1

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

#ifdef EXPORTING_matlabExp
#define PUBLIC_matlabExp_C_API __global
#else
#define PUBLIC_matlabExp_C_API /* No import statement needed. */
#endif

#define LIB_matlabExp_C_API PUBLIC_matlabExp_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_matlabExp
#define PUBLIC_matlabExp_C_API __declspec(dllexport)
#else
#define PUBLIC_matlabExp_C_API __declspec(dllimport)
#endif

#define LIB_matlabExp_C_API PUBLIC_matlabExp_C_API


#else

#define LIB_matlabExp_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_matlabExp_C_API 
#define LIB_matlabExp_C_API /* No special import/export declaration */
#endif

extern LIB_matlabExp_C_API 
bool MW_CALL_CONV matlabExpInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_matlabExp_C_API 
bool MW_CALL_CONV matlabExpInitialize(void);

extern LIB_matlabExp_C_API 
void MW_CALL_CONV matlabExpTerminate(void);



extern LIB_matlabExp_C_API 
void MW_CALL_CONV matlabExpPrintStackTrace(void);

extern LIB_matlabExp_C_API 
bool MW_CALL_CONV mlxQTexp_only(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_matlabExp
#define PUBLIC_matlabExp_CPP_API __declspec(dllexport)
#else
#define PUBLIC_matlabExp_CPP_API __declspec(dllimport)
#endif

#define LIB_matlabExp_CPP_API PUBLIC_matlabExp_CPP_API

#else

#if !defined(LIB_matlabExp_CPP_API)
#if defined(LIB_matlabExp_C_API)
#define LIB_matlabExp_CPP_API LIB_matlabExp_C_API
#else
#define LIB_matlabExp_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_matlabExp_CPP_API void MW_CALL_CONV QTexp_only(int nargout, mwArray& b, const mwArray& c);

#endif
#endif
