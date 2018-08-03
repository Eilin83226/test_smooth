#ifndef FUNC_H
#define FUNC_H

#include <string.h>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <complex>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <queue>

#define M_PI 3.14159265358979323846

using namespace cv;
using namespace std;

//template<typename ty>
//void circshift(ty &out, const ty &in, int xdim, int ydim, int xshift, int yshift);
//void fft2(const Mat &src, Mat &Fourier);
//void hanning(int N, vector <float> &ans);
//void fftshift(Mat &out);
//void circshift(Mat &out, const Point &delta);
vector <Mat> QT_conj(vector <Mat> &Vec_Src);
Mat QT_conj_m(Mat &src);
vector <Mat> QT_vec_mul_vec(vector <Mat> &Vec_Src1 , vector <Mat> &Vec_Src2);
Mat QT_M_mul_M(Mat &M_Src1,Mat &M_Src2);
void CopyMatVector(vector <Mat> &old_vec , vector <Mat> &new_vec);
Mat BGR2RGB(Mat &im);
Mat RGB2BGR(Mat &im);

#endif // FUNC_H
