#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QProcess>
#include <QPixmap>
#include <QScreen>
#include <QImage>
#include <QtSql/QSqlDatabase>
#include <QDesktopWidget>
#include <QMutex>
#include <QMainWindow>
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

#include "mclmcrrt.h"
#include "mclcppclass.h"


using namespace cv;
using namespace std;

//extern struct image_info seq;
//extern vector <vector <double> > ground_truth;

class image_info{
public:
    int len=0;
    double init_rect[4];
    vector <string> s_frame;
    string VidName;
    int st_frame;
    int en_frame;
};

class track_result{
public:
    string type;
    vector <Rect> res;
    double fps;
};

struct hog_parameters{
public:
    pair<string,int> nDim;
    pair<string,bool> useForColor;
    pair<string,bool> useForGray;
    pair<string,double> nOrients;
};

struct GrayF_parameters{
public:
    string colorspace;
    int nDim;
};

struct para_features_struct{
    pair<string,string> getFeature;
    pair<string,hog_parameters> fparams;
};

struct cell{
    pair<string,int> cell_size;
    pair<string,double> cell_selection_thresh;
};

class parameters{
public:
    //delete
    //string video_path;

    struct para_features_struct t_features;
    struct cell t_global;
    string search_area_shape;
    double search_area_scale;
    double filter_max_area;
    double learning_rate;
    double output_sigma_factor;
    int interpolate_response;
    double newton_iterations;
    int number_of_scales;
    double scale_step;
    double wsize[2];
    double init_pos[2];

    //notice : 讀取camera後沒有frame數，整合的時候需要更動
    //vector <string> s_frame;
    //int no_fram;
    //int seq_st_frame;
    //int seq_en_frame;
    //notice : end

    int admm_iterations;
    double admm_lambda;
    int visualization;
};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

//signals:
private slots:
    void VideoCaptureSlot();


private:
    Ui::MainWindow *ui;

    double learning_rate; //you can use different learning rate for different benchmarks.
    image_info seq;
    track_result results;
    vector <vector <double> > ground_truth;

    //偵測後的bounding box
    vector <double> init_rect;

    struct hog_parameters hog_params;
    parameters params;
    struct GrayF_parameters grayscale_params;


    VideoCapture cap;
    QTimer *mytimer;
    bool isFirstFrame = true;
    bool isEnd = false;
    bool isRun = true;
    bool frameLock = false;
    Mat read_im;
    queue <Mat> Input_im;
    //vector <Mat> Input_im;
    vector <Mat> total;

    void load_video_info(string video_path,image_info *seq,vector <vector <double> > *ground_truth);
    int getdir(string dir, vector<string> &files);


    void run_BACF(vector <double> init_rect,double lr,track_result &results);
};



#endif // MAINWINDOW_H
