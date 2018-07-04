#include "mainwindow.h"

#include <opencv2/core/ocl.hpp>
#include <QApplication>
using namespace cv::ocl;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

/*ocl::setUseOpenCL(true);
double start = getTickCount();
    UMat a(640,480,CV_8UC3,Scalar(22,23,23));
    UMat b;
    //cvtColor(a,b,COLOR_BGR2GRAY);
    //GaussianBlur(b, b, Size(7,7), 1.5);
    UMat ans;
    for(int i = 0 ; i < 1000 ; i ++){
        ans = a.mul(a);
    }
double end = getTickCount();
cout<<"UMat1 = "<<(end - start)/getTickFrequency()<<endl;

double start1 = getTickCount();
    Mat c(640,480,CV_8UC3,Scalar(22,23,23));
    Mat d;
    //cvtColor(c,d,COLOR_BGR2GRAY);
    //GaussianBlur(d, d, Size(7,7), 1.5);
    Mat ans1;
    for(int i = 0 ; i < 1000 ; i ++){
        ans1 = c.mul(c);
    }
double end1 = getTickCount();
cout<<"Mat = "<<(end1 - start1)/getTickFrequency()<<endl;

//double start2 = clock();
//    for(int i = 0 ; i < 1000 ; i ++){
//        ans = a.mul(b);
//    }
//double end2 = clock();
//cout<<"UMat2 = "<<(end2 - start2) / 1000<<endl;

const string filename = "C:/Users/Eilin/Documents/MATLAB/BACF/BACF_toUpload/seq/test/img/IMG_1849 001.jpg";
/*
int64 start1=0,end1=0;
 start1 = getTickCount();

 Mat img1,gray1;
 img1 = imread(filename, 1);

 cvtColor(img1,gray1,COLOR_BGR2GRAY);
 GaussianBlur(gray1, gray1, Size(7,7), 1.5);
 Canny(gray1, gray1, 0, 50);

 imshow("edges",gray1);

 end1 = getTickCount();
 printf("time: %f ms\n", (end1 - start1)/getTickFrequency());

 waitKey(1);



 ocl::setUseOpenCL(true);

  int64 start=0,end=0;
      start = getTickCount();

  UMat img,gray;  //
  //imread(filename, 1).copyTo(img);
         img = imread(filename, 1).getUMat(ACCESS_READ);

  cvtColor(img,gray,COLOR_BGR2GRAY);
  GaussianBlur(gray, gray, Size(7,7), 1.5);
  Canny(gray, gray, 0, 50);

  imshow("edges",gray);

         end = getTickCount();

         printf("time: %f ms\n", (end - start)/getTickFrequency());
  waitKey(0);
*/
 return 0;

}
