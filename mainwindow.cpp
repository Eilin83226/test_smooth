#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "load_video_info.h"
#include "run_bacf.h"
#include "bacf_optimized.h"

#include "resp_newton.h"

//#include "mclmcr.h" // mwArray聲明
//#include "mtimesx.c"
//#include "mtimesx_realtimesreal.c"
//#include "MxArray.hpp"
//#include "mex.h"
//#include "opencvmex.hpp"
//#include "mexopencv.hpp"
#include "test.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "piotr_fhog/fhog.hpp"

#define resolution_width 3840
#define resolution_height 2160

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //%   Load video information
    string base_path = "C:/Users/Eilin/Documents/MATLAB/BACF/BACF_toUpload/seq";
    string video = "test";
    string video_path = base_path +"/"+ video;

    //設定ground_truth
    load_video_info(video_path,&seq,&ground_truth);

    seq.VidName = video;
    seq.st_frame = 1;
    seq.en_frame = seq.len;
    //--gt_boxes = [ground_truth(:,1:2), ground_truth(:,1:2) + ground_truth(:,3:4) - ones(size(ground_truth,1), 2)];

    //%   Run BACF- main function
    //%   you can use different learning rate for different benchmarks.
    learning_rate = 0.005;

    //執行BACF追蹤演算法
    run_BACF(seq,video_path,learning_rate,results);




//    Mat a(5,5,CV_32FC2,Scalar(3.2,1.2));
//    a.at<Vec2f>(2,2)[0] = 2.2;
//    a.at<Vec2f>(2,2)[0] = 1.5;
//    Mat c(5,5,CV_32FC2,Scalar(4.1,3.5));
//    c.at<Vec2f>(2,2)[0] = 2.2;
//    c.at<Vec2f>(2,2)[0] = 1.5;
//    Mat e(5,5,CV_32F,Scalar(3.2));
//    Mat e1(5,5,CV_32FC2,Scalar(3.2,0));

//    Mat ans = a+c+e;
//    cout<<ans<<endl;
//    Mat ans1 = a+c+e1;
//    cout<<ans1<<endl;
//    cout<<(-1)*c + a<<endl;
//    Mat d;
//    add((-1)*c,a,d);
//    cout<<d<<endl;



//    vector <Mat> a;
//    Mat c(3,3,CV_32F,Scalar(2));
//    Mat d = Mat::zeros(3,3,CV_32F);
//    a.push_back(c.mul(3));
//    a.push_back(c.mul(3));
//    //a.assign(3,d.clone());
//    cout<<a.at(0)<<endl;
//    cout<<a.at(1)<<endl;
//    //cout<<a.at(2)<<endl;
//    a.at(0).at<float>(0,0) = 1;
//    cout<<a.at(0)<<endl;
//    cout<<a.at(1)<<endl;
//    //cout<<a.at(2)<<endl;



//    vector <Mat> Src1;
//    Mat d(3,3,CV_32F,Scalar(2));
//    Mat f(3,3,CV_32F,Scalar(2));
//    //d.at<Vec2f>(0,0)[1] = 1.1;
//    //d.at<Vec2f>(0,1)[1] = 2.2;
//    d.at<float>(0,1) = 1;
//    d.at<float>(1,0) = 1;
//    d.at<float>(2,1) = 5;
//    d.at<float>(2,0) = 5;
//    cout<<d<<endl;
//    double maxVal1;
//    Point maxLoc1;
//    double minVal;
//    Point minLoc;
//    minMaxLoc(d, &minVal, &maxVal1, &minLoc, &maxLoc1);
//    cout<<maxVal1<<","<<maxLoc1<<endl;
//    cout<<minVal<<","<<minLoc<<endl;
//    cout<<d.at<float>(maxLoc1.y,maxLoc1.x)<<","<<d.at<float>(minLoc.y,minLoc.x)<<endl;
//    Src1.push_back(d);
//    f.at<float>(2,0) = 6;
//    Src1.push_back(f);


//    double maxVal = -10000;
//    Point maxLoc;
//    int dim_max = -1;
//    for(int n = 0 ; n <Src1.size() ; ++n){cout<<Src1.at(n)<<endl;
//        double maxV;
//        Point maxL;
//        //opencv找出的最大值是以列為主，因此需要找以行為主最大值的座標
//        minMaxLoc(Src1.at(n),0,&maxV,0,&maxL);
//        if(maxVal < maxV){
//            dim_max = n;
//            maxVal = maxV;
//            maxLoc = maxL;
//        }
//    }
//    bool find = false;
//    for(int j = 0 ; j < maxLoc.x  ; ++j){
//        for(int  i = maxLoc.y ; i < Src1.at(dim_max).rows ; ++i){
//            if(maxVal == Src1.at(dim_max).at<float>(i,j)){
//                maxLoc.x = j;
//                maxLoc.y = i;
//                find = true;
//                break;
//            }
//        }
//        if(find){
//            break;
//        }
//    }
//    cout<<dim_max<<","<<maxVal<<","<<maxLoc<<endl;


//    Mat k;
//    k = Src1.at(0).mul(-1);
//    cout<<k<<endl;

//    vector <Mat> Src2;
//    Mat e(1,1,CV_32FC2,Scalar(0));
//    //e.at<Vec2f>(0,0)[0] = 2;
//    //e.at<Vec2f>(0,0)[1] = 1.1;
//    //e.at<Vec2f>(0,1)[1] = 1.1;
//    cout<<e<<endl;
//    Src2.push_back(e);
//    Src2.push_back(e);

//    vector <Mat> g;
//    g = exp_bsx(d,Src2);
//    cout<<g.at(0)<<endl;


//    vector <Mat> ans;
//    ans = bsx_time(e,Src1);
//    cout<<"ans = "<<endl;
//    for(int n = 0 ; n < ans.size() ; ++n){
//        cout<<ans.at(n)<<endl;
//    }

//    vector <Mat> ans1;
//    ans1 = mulMatrix(Src2,Src1);
//    cout<<"ans = "<<endl;
//    for(int n = 0 ; n < ans1.size() ; ++n){
//        cout<<ans1.at(n)<<endl;
//    }


    //cv::Mat a(3,3,CV_8U,Scalar(255));
    //mxArray *x = ocvMxArrayFromImage_uint8(a);
    //x = ocvMxArrayFromImage

/*    Mat c = Mat::zeros(2,2,CV_64F);
    Mat d = Mat::ones(2,2,CV_64F);
    Mat g(2,2,CV_64F,Scalar(2));
    Mat e(2,2,CV_32F,Scalar(1.1));
    Mat f = Mat::zeros(2,2,CV_32FC2);
    c.at<double>(0,0) = 1.3;
    c.at<double>(0,1) = 2.5534;


    c.at<double>(1,0) = 3.1;
    c.at<double>(1,1) = 4.5;
    //d = c.mul(e);
    float dd = c.at<double>(0,1) * e.at<float>(1,1);
    cout<<dd<<endl;
    //MxArray x ;
    //Resize(MxArray(d),MxArray(c),"auto",x);


/*
    vector <int> a[2];
    a[0].push_back(1);
    a[0].push_back(2);
    a[0].push_back(3);
    a[1].push_back(1);
    a[1].push_back(2);
    a[1].push_back(3);
    Mat max_row_perm = Mat::zeros(a[0].size(),2,CV_64F);
    for(int i = 0 ; i < max_row_perm.rows ; ++i){
        for(int j = 0 ; j < max_row_perm.cols ; ++j){
            max_row_perm.at<double>(i,j) = (double)a[j].at(i);
            cout<<max_row_perm.at<double>(i,j)<<" ";
        }cout<<endl;
    }
*/
/*
    complex <double> comp(1.1,2.2);
    vector <Mat> x,y;
    Mat c = Mat::zeros(2,2,CV_64F);
    Mat d = Mat::zeros(2,2,CV_32FC2);
    Mat e = Mat::zeros(2,2,CV_32FC2);
    Mat f = Mat::zeros(2,2,CV_32FC2);
    e = Scalar(1);
    c.at<double>(0,0) = 1;
    //c.at<Vec2f>(0,0)[1] = 0;
    c.at<double>(0,1) = 0.26359;
    //c.at<Vec2f>(0,1)[1] = 0;
    c.at<double>(1,0) = 0.00482;
    //c.at<Vec2f>(1,0)[1] = 0;
    c.at<double>(1,1) = 5;
    //c.at<Vec2f>(1,1)[1] = 0;

    exp(c,d);

    e.at<Vec2f>(0,0)[0] = 0;
    e.at<Vec2f>(0,0)[1] = 0;
    e.at<Vec2f>(0,1)[0] = 2;
    e.at<Vec2f>(0,1)[1] = 2;
    e.at<Vec2f>(1,0)[0] = 3;
    e.at<Vec2f>(1,0)[1] = 3;
    e.at<Vec2f>(1,1)[0] = 4;
    e.at<Vec2f>(1,1)[1] = 4;

    exp(e,f);
    //d = c.mul(e);
    //f = e*c;
    //d = c.mul(e);
    //fft2(c,f);
    //dft(c,d,DFT_COMPLEX_OUTPUT);
    //dft(e,f,DFT_COMPLEX_OUTPUT);
    //idft(e, f, DFT_COMPLEX_OUTPUT+DFT_SCALE, 0);
    for(int i = 0 ; i < 2 ; ++i){
        for(int j = 0 ; j < 2 ; ++j){
            //d = d + c;
            cout<<d.at<Vec2d>(i,j)[0]<<","<<d.at<Vec2d>(i,j)[1]<<" ";
            //cout<<d.at<float>(i,j)<<" ";
        }cout<<endl;
    }x.push_back(d.clone());
    for(int i = 0 ; i < 2 ; ++i){
        for(int j = 0 ; j < 2 ; ++j){
            cout<<f.at<Vec2f>(i,j)[0]*cos(e.at<Vec2f>(i,j)[1])<<","<<f.at<Vec2f>(i,j)[1]*sin(e.at<Vec2f>(i,j)[0])<<" ";
            //cout<<x[0].at<Vec2f>(i,j)[0]<<","<<x[0].at<Vec2f>(i,j)[1]<<" ";
        }cout<<endl;
    }

    //cout<<d.at<Vec2f>(1,1)[0]<<" "<<d.at<Vec2f>(1,1)[1]<<endl;

/*
    Mat a = Mat::zeros(3, 3, CV_32FC2);
    Mat b = Mat::zeros(3, 3, CV_32FC2);
    Mat c = Mat::zeros(3, 3, CV_64F);


     c.at<double>(0,0) = 1;
     c.at<double>(0,1) = 2;
     c.at<double>(0,2) = 3;

     c.at<double>(1,0) = 4;
     c.at<double>(1,1) = 5;
     c.at<double>(1,2) = 6;

     c.at<double>(2,0) = 7;
     c.at<double>(2,1) = 8;
     c.at<double>(2,2) = 9;

    //idft(a, b, DFT_COMPLEX_OUTPUT+DFT_SCALE, 0);
    //idft(a, c, DFT_REAL_OUTPUT+DFT_SCALE, 0);
    //dft(c,b,DFT_COMPLEX_OUTPUT);
     fft2(c,b);
    for(int i = 0 ; i < 3 ; ++i){
        for(int j = 0 ; j < 3 ; ++j){
            cout<<b.at<Vec2f>(i,j)[0]<<","<<b.at<Vec2f>(i,j)[1]<<" ";
            //cout<<b.at<Vec2f>(i,j)<<endl;
        }cout<<endl;
    }
    for(int i = 0 ; i < 3 ; ++i){
        for(int j = 0 ; j < 3 ; ++j){
            cout<<c.at<double>(i,j)<<" ";
        }cout<<endl;
    }

    /*const int size[3] = {4,3,5};
    Mat a[3];
    for(int i = 0 ; i < 3 ; ++i){
        a[i].create(3,size,CV_32F);
        a[i] = Scalar(0);
    }*/

//    Mat b = Mat::ones(2, 2, CV_32FC2);
//    Mat e = Mat::zeros(2, 2, CV_32FC2);
//    Mat c(2,2,CV_32FC2,Scalar(3.154,1.124)),d(2,2,CV_32FC2,Scalar(3.2143,2.3458));
//    Mat f;
//    c.at<Vec2f>(0,0)[0] = 1;
//    c.at<Vec2f>(0,0)[1] = 1;
//    c.at<Vec2f>(0,1)[0] = 2;
//    c.at<Vec2f>(0,1)[1] = 2;
//    c.at<Vec2f>(1,0)[0] = 3;
//    c.at<Vec2f>(1,0)[1] = 3;
//    c.at<Vec2f>(1,1)[0] = 4;
//    c.at<Vec2f>(1,1)[1] = 4;
//    d.at<Vec2f>(0,0)[1] = c.at<Vec2f>(1,1)[1] + b.at<Vec2f>(1,1)[1];
//    cout<<"c = "<<endl;
//    cout<<c<<endl;
//    cout<<"b = "<<endl;
//    cout<<d<<endl;
//    f = c.mul(10);
//    cout<<f<<endl;
//    f = c / b;
//    cout<<f<<endl;





//    vector <Mat> src1,src2,src;
//    src1.push_back(c);
////    src2.push_back(d);
////    src2.push_back(d);
////    src2.push_back(d);
////    src2.push_back(d);
//    src2 = QT_conj(src1);
//    src = QT_matrix_mul(src1,src2);
//    cout<<src.at(0)<<endl;
    //add(2,c,d);
//cout<<d.at<Vec2f>(1,1)[1]<<","<<c.at<Vec2f>(1,1)[1]<<","<<b.at<Vec2f>(1,1)[1]<<endl;




}

MainWindow::~MainWindow()
{
    delete ui;
}
