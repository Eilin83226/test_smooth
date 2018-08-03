#ifndef THREAD_BACF_TRACKING_H
#define THREAD_BACF_TRACKING_H

//#include "run_bacf.h"
#include "mainwindow.h"
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <QMessageBox>
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <time.h>
#include <QObject>
#include <QThread>
#include <QLabel>
#include <QtDebug>
#include <QtCore>
#include <QTimer>
#define M_PI 3.14159265358979323846
using namespace cv;
using namespace std;



class thread_BACF_tracking : public QThread{

    Q_OBJECT

public:
    thread_BACF_tracking(parameters &tparams ,queue <Mat> *tInput_im ,bool *tFrameLock ,bool *tIsEnd);


protected:
    void run();

//signals:
private slots:
    //void VideoCaptureSlot();
    //void showTime();


private:
    //調整追蹤大小
    const double width = 640;
    const double height = 480;
    const double img_w = 640;
    const double img_h = 480;
    const double show_w = 640;
    const double show_h = 480;

    bool frameLoce = false;

    //初始化的參數
    double learning_rate;
    int nScales;
    int interpolate_response;
    struct para_features_struct features;
    string video_path;
    vector <string> s_frames;
    double pos[2];
    double target_sz[2];
    int visualization;
    int featureRatio;
    struct cell global_feat_params;
    float currentScaleFactor;
    double base_target_sz[2];
    vector <double> sz;
    double use_sz[2];
    int dim_rg;
    int dim_cg;
    Mat rs;
    Mat cs;
    Mat yf;
    int interp_sz[2];
    Mat cos_window;
    Mat read_im,threadFrame;
    bool colorImage = true;
    int feature_dim = 0;
    vector <float> scaleFactors;
    double min_scale_factor;
    double max_scale_factor;
    Mat ky;
    Mat kx;
    double newton_iterations;
    parameters params;


    //tracking參數
    vector <Mat> model_xf;
    int scale_ind;
    vector <Mat> g_f;

    queue <Mat> *Input_im;
    //vector <Mat> *Input_im;
    bool *FrameLock;
    bool isFirstFrame = true;
    bool isRun = true;
    bool *isEnd;
    int frame_num = 0;


    template<typename ty>
    void circshift(ty &out, const ty &in, int xdim, int ydim, int xshift, int yshift);
    void fft2(const Mat &src, Mat &Fourier);
    void hanning(int N, vector <float> &ans);
    void fftshift(Mat &out);
    void circshift(Mat &out, const Point &delta);
//    vector <Mat> QT_conj(vector <Mat> &Vec_Src);
//    Mat QT_conj_m(Mat &src);
//    vector <Mat> QT_vec_mul_vec(vector <Mat> &Vec_Src1 , vector <Mat> &Vec_Src2);
//    Mat QT_M_mul_M(Mat &M_Src1,Mat &M_Src2);
//    void CopyMatVector(vector <Mat> &old_vec , vector <Mat> &new_vec);
//    Mat BGR2RGB(Mat &im);
//    Mat RGB2BGR(Mat &im);


};


#endif // THREAD_BACF_TRACKING_H
