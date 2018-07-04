#ifndef TEST_H
#define TEST_H

#include "myFunc.h"
#include "QTmtimesx.h"
#include "QTbsxfun.h"
#include "QTexp.h"
#include <QDebug>
#include "mainwindow.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

class test{
public:
    test();
    void temp();
};

vector <Mat> mulMatrix(vector <Mat> &Vec_Src1 , vector <Mat> &Vec_Src2);
vector <Mat> bsx_time(Mat &Vec_Src1 , vector <Mat> &Vec_Src2);
vector <Mat> exp_bsx(Mat &Vec_Src1 , vector <Mat> &Vec_Src2);
vector <Mat> exp_matlab(vector <Mat> &Vec_Src);
mwArray mat2mwArray(const Mat imgSrc);
Mat mwArray2mat(const mwArray data);


#endif // TEST_H
