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

#define M_PI 3.1416

using namespace cv;
using namespace std;

// Define a pixel
typedef Point_<float> Pixel;


vector <Mat> QT_conj(vector <Mat> &Vec_Src);
Mat QT_conj_m(Mat &src);
vector <Mat> QT_vec_mul_vec(vector <Mat> &Vec_Src1 , vector <Mat> &Vec_Src2);
Mat QT_M_mul_M(Mat &M_Src1,Mat &M_Src2);
void CopyMatVector(vector <Mat> &old_vec , vector <Mat> &new_vec);
Mat BGR2RGB(Mat &im);
Mat RGB2BGR(Mat &im);

#endif // FUNC_H
