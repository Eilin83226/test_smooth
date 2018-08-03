#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "load_video_info.h"
//#include "run_bacf.h"
//#include "bacf_optimized.h"
#include "thread_bacf_tracking.h"

#include "resp_newton.h"
#include "widget.h"

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
//    string base_path = "C:/Users/Eilin/Documents/MATLAB/BACF/BACF_toUpload/seq";
//    string video = "test";
//    string video_path = base_path +"/"+ video;

    //設定ground_truth
    //load_video_info(video_path,&seq,&ground_truth);

    //-----start:初始化bounding box-----//
    ifstream fin;
    //--ground_truth = dlmread([video_path '/groundtruth_rect.txt']);
    string ground_truth_path = "C:/Users/Eilin/Documents/MATLAB/BACF/BACF_toUpload/seq/test/groundtruth_rect.txt";
    fin.open(ground_truth_path.c_str());
    char temp[30];
    fin.getline(temp,30);

    const char *delim = ",";
    char *pch;
    pch = strtok(temp,delim);
    while(pch != NULL){
        double num = atoi(pch);
        init_rect.push_back(num);
        pch = strtok(NULL, delim);
    }

    fin.close();
    //-----end:初始化bounding box-----//

//    seq.VidName = video;
//    seq.st_frame = 1;
//    seq.en_frame = seq.len;
    //--gt_boxes = [ground_truth(:,1:2), ground_truth(:,1:2) + ground_truth(:,3:4) - ones(size(ground_truth,1), 2)];

    //%   Run BACF- main function
    //%   you can use different learning rate for different benchmarks.
    learning_rate = 0.005;

    //執行BACF追蹤演算法
    run_BACF(init_rect,learning_rate,results);





}

MainWindow::~MainWindow()
{
    delete ui;
}


//讀groundtruth_rect.txt取得BundingBox
void MainWindow::load_video_info(string video_path,image_info *seq,vector <vector <double> > *ground_truth){
    ifstream fin;
    //--ground_truth = dlmread([video_path '/groundtruth_rect.txt']);
    string ground_truth_path = video_path+"/groundtruth_rect.txt";
    fin.open(ground_truth_path.c_str());
    char temp[30];
    vector <double> rect;
    while(fin.getline(temp,30)){
        //--seq.len = size(ground_truth, 1);

        (*seq).len++;
        const char *delim = ",";
        char *pch;
        pch = strtok(temp,delim);
        while(pch != NULL){
            double num = atoi(pch);
            rect.push_back(num);
            pch = strtok(NULL, delim);
        }
        (*ground_truth).push_back(rect);
        rect.clear();
    }
    fin.close();

    //--seq.init_rect = ground_truth(1,:);
    for(int i = 0 ; i < 4 ; ++i){
        (*seq).init_rect[i] = (*ground_truth)[0][i];
    }

    //--img_path = [video_path '/img/'];
    string img_path;
    //img_path = video_path+"/img/";

    //--img_files = dir(fullfile(img_path, '*.jpg'));
    //--img_files = {img_files.name};
    img_path = "C://Users//Eilin//Documents//MATLAB//BACF//BACF_toUpload//seq//test//test2_853x480//";
    getdir(img_path, (*seq).s_frame);
}

//取得資料夾內所有檔案
int MainWindow::getdir(string dir, vector<string> &files){
    DIR *dp;//創立資料夾指標
    struct dirent *dirp;
    if((dp = opendir(dir.c_str())) == NULL){
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    int ignore=2;
    while((dirp = readdir(dp)) != NULL){//如果dirent指標非空
        if(ignore==0){
            files.push_back(string(dirp->d_name));//將資料夾和檔案名放入vector
        }
        else{//忽略.&..
            ignore--;
        }
    }
    closedir(dp);//關閉資料夾指標
    //return 0;
}

void MainWindow::run_BACF(vector <double> init_rect,double lr,track_result &results){

    //設置參數
    //%   HOG feature parameters
    hog_params.nDim.first = "nDim";
    hog_params.nDim.second = 31;


    //%   Grayscale feature parameters
    grayscale_params.colorspace = "gray";
    grayscale_params.nDim = 1;


    //%   Global feature parameters
    params.t_features.getFeature = make_pair("getFeature","@get_fhog");
    params.t_features.fparams = make_pair("fparams",hog_params);


    //%   Feature cell size
    params.t_global.cell_size = make_pair("cell_size",4);
    //%   Threshold for reducing the cell size in low-resolution cases
    params.t_global.cell_selection_thresh = make_pair("cell_selection_thresh",pow(0.75,2));


    //%   Search region + extended background parameters
    //% the shape of the training/detection window: 'proportional', 'square' or 'fix_padding'
    params.search_area_shape = "square";
    //% the size of the training/detection area proportional to the target size
    params.search_area_scale = 5;
    //% the size of the training/detection area in feature grid cells
    params.filter_max_area = pow(50,2);


    //%   Learning parameters
    //% learning rate
    params.learning_rate = lr;
    //% standard deviation of the desired correlation output (proportional to target)
    params.output_sigma_factor = 1.0/16.0;


    //%   Detection parameters
    //% correlation score interpolation strategy: 0 - off, 1 - feature grid, 2 - pixel grid, 4 - Newton's method
    params.interpolate_response = 4;
    //% number of Newton's iteration to maximize the detection scores
    params.newton_iterations = 50;


    //%   Scale parameters
    params.number_of_scales = 5;
    params.scale_step = 1.01;


    //%   size, position, frames initialization
    //--params.wsize    = [seq.init_rect(1,4), seq.init_rect(1,3)];
    params.wsize[0] = init_rect[3];
    params.wsize[1] = init_rect[2];
    params.init_pos[0] = init_rect[1] + floor(params.wsize[0]/2);
    params.init_pos[1] = init_rect[0] + floor(params.wsize[1]/2);
    //notice : 讀取camera後沒有frame數，整合的時候需要更動
//    params.s_frame = seq.s_frame;
//    params.no_fram = seq.en_frame - seq.st_frame + 1;
//    params.seq_st_frame = seq.st_frame;
//    params.seq_en_frame = seq.en_frame;
    //notice : end

    //%   ADMM parameters, # of iteration, and lambda- mu and betha are set in the main function.
    params.admm_iterations = 2;
    params.admm_lambda = 0.01;


    //%   Debug and visualization
    params.visualization = 1;

    //BACF_optimized(params,results);
    //thread_BACF_tracking trackinThread(params);
    //trackinThread.start(QThread::TimeCriticalPriority);


    //-----------------------------------------------------------------------
    cap.open("C:/Users/Eilin/Desktop/testVideo/test2_640x480.mp4");
    //cap.open(0);
    if (!cap.isOpened()) {
        cout << "video open fail!" << endl;
        system("pause");
    }
    cout << "video open success!" << endl;

    mytimer = new QTimer(this);
    //showTime();
    mytimer->start(1);                   //以1000毫秒為周期起動定時器

    cout<<"first"<<endl;
    connect(mytimer,SIGNAL(timeout()),this,SLOT(VideoCaptureSlot()));

    thread_BACF_tracking *trackinThread = new thread_BACF_tracking(params ,&Input_im ,&frameLock ,&isEnd);
    trackinThread->start(QThread::TimeCriticalPriority);

    //Widget *w = new Widget(&Input_im ,&frameLock ,&isRun);
    //w->start(QThread::TimeCriticalPriority);
}

void MainWindow::VideoCaptureSlot()
{
    //qDebug()<<"fuck";
    for(int i = 0 ; i < 50; ++i){
        if(!frameLock){
            frameLock = true;
            cout << "videoCaptureSlot start" <<endl;
            cap >> read_im;
            if( read_im.empty()){
                cout << "video End." <<endl;
                isEnd = true;
                frameLock = false;

                //停止Qtimer
                mytimer->stop();

                cap.release();
                return;
            }
            //Input_im.push_back(read_im.clone());
            Input_im.push(read_im.clone());
            //total.push_back(read_im);
            cout<<"Input_size = "<<Input_im.size()<<endl;
            //cout<<"total = "<<total.size()<<endl;
            cout << "videoCaptureSlot end" <<endl;

            frameLock = false;
//            if( read_im.empty()){
//                cout << "End." <<endl;
//                isRun = false;

//                //return;
//            }
            //imshow("im",read_im);
            //waitKey(1);
            //cout<<"isRun = "<<isRun<<endl;
            //isRun = true;
            break;
        }
    }
}
