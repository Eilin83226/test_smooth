﻿#ifndef RESP_NEWTON_H
#define RESP_NEWTON_H

//#include "bacf_optimized.h"
#include "thread_bacf_tracking.h"
#include "time.h"

void resp_newton(vector <Mat> &response,vector <Mat> &responsef,double iterations,Mat &ky,Mat &kx,double use_sz[],float &disp_row,float &disp_col,int &sind);
Mat QT_M_mtimesx(Mat &M_Src1 ,Mat &M_Src2);
Mat QT_M_exp(Mat &M_Src);
float mod(float div1 , float div2);
#endif // RESP_NEWTON_H
