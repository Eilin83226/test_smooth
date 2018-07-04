//
// MATLAB Compiler: 6.1 (R2015b)
// Date: Tue Jun 05 10:48:45 2018
// Arguments: "-B" "macro_default" "-W" "cpplib:QTmtimesx" "-T" "link:lib" "-d"
// "C:\Users\Eilin\Documents\MATLAB\BACF\BACF_toUpload\QTmtimesx\for_testing"
// "-v" "C:\Users\Eilin\Documents\MATLAB\BACF\BACF_toUpload\mtimesx.mexw64"
// "C:\Users\Eilin\Documents\MATLAB\BACF\BACF_toUpload\QTmtimesx.m" 
//

#ifndef __QTmtimesx_h
#define __QTmtimesx_h 1

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

#ifdef EXPORTING_QTmtimesx
#define PUBLIC_QTmtimesx_C_API __global
#else
#define PUBLIC_QTmtimesx_C_API /* No import statement needed. */
#endif

#define LIB_QTmtimesx_C_API PUBLIC_QTmtimesx_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_QTmtimesx
#define PUBLIC_QTmtimesx_C_API __declspec(dllexport)
#else
#define PUBLIC_QTmtimesx_C_API __declspec(dllimport)
#endif

#define LIB_QTmtimesx_C_API PUBLIC_QTmtimesx_C_API


#else

#define LIB_QTmtimesx_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_QTmtimesx_C_API 
#define LIB_QTmtimesx_C_API /* No special import/export declaration */
#endif

extern LIB_QTmtimesx_C_API 
bool MW_CALL_CONV QTmtimesxInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_QTmtimesx_C_API 
bool MW_CALL_CONV QTmtimesxInitialize(void);

extern LIB_QTmtimesx_C_API 
void MW_CALL_CONV QTmtimesxTerminate(void);



extern LIB_QTmtimesx_C_API 
void MW_CALL_CONV QTmtimesxPrintStackTrace(void);

extern LIB_QTmtimesx_C_API 
bool MW_CALL_CONV mlxMtimesx(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_QTmtimesx_C_API 
bool MW_CALL_CONV mlxQTmtimesx(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_QTmtimesx
#define PUBLIC_QTmtimesx_CPP_API __declspec(dllexport)
#else
#define PUBLIC_QTmtimesx_CPP_API __declspec(dllimport)
#endif

#define LIB_QTmtimesx_CPP_API PUBLIC_QTmtimesx_CPP_API

#else

#if !defined(LIB_QTmtimesx_CPP_API)
#if defined(LIB_QTmtimesx_C_API)
#define LIB_QTmtimesx_CPP_API LIB_QTmtimesx_C_API
#else
#define LIB_QTmtimesx_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_QTmtimesx_CPP_API void MW_CALL_CONV mtimesx(int nargout, mwArray& varargout, const mwArray& varargin);

extern LIB_QTmtimesx_CPP_API void MW_CALL_CONV mtimesx(int nargout, mwArray& varargout);

extern LIB_QTmtimesx_CPP_API void MW_CALL_CONV mtimesx(const mwArray& varargin);

extern LIB_QTmtimesx_CPP_API void MW_CALL_CONV mtimesx();

extern LIB_QTmtimesx_CPP_API void MW_CALL_CONV QTmtimesx(int nargout, mwArray& b, const mwArray& a, const mwArray& c);

#endif
#endif
