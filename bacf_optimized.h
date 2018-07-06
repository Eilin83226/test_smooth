#ifndef BACF_OPTIMIZED_H
#define BACF_OPTIMIZED_H

#include "run_bacf.h"
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <QMessageBox>
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <time.h>
#define M_PI 3.14159265358979323846
using namespace cv;
using namespace std;


extern int dim_rg;
extern int dim_cg;

const double width = 426;
const double height = 240;
const double img_w = 426;
const double img_h = 240;

void BACF_optimized(parameters &params,track_result &results);
template<typename ty>
void circshift(ty &out, const ty &in, int xdim, int ydim, int xshift, int yshift);
void fft2(const Mat &src, Mat &Fourier);
void hanning(int N, vector <float> &ans);
void CopyMatVector(vector <Mat> &old_vec , vector <Mat> &new_vec);
void fftshift(Mat &out);
void circshift(Mat &out, const Point &delta);
vector <Mat> QT_conj(vector <Mat> &Vec_Src);
Mat QT_conj_m(Mat &src);
vector <Mat> QT_vec_mul_vec(vector <Mat> &Vec_Src1 , vector <Mat> &Vec_Src2);
Mat QT_M_mul_M(Mat &M_Src1,Mat &M_Src2);
#endif // BACF_OPTIMIZED_H
