#ifndef RUN_BACF_H
#define RUN_BACF_H


#include <iostream>
#include <vector>
#include "mainwindow.h"

using namespace std;

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
    string video_path;
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
    vector <string> s_frame;
    int no_fram;
    int seq_st_frame;
    int seq_en_frame;
    //notice : end

    int admm_iterations;
    double admm_lambda;
    int visualization;
};


extern struct hog_parameters hog_params;
extern parameters params;
extern struct GrayF_parameters grayscale_params;
void run_BACF(image_info seq,string video_path,double lr,track_result &results);

#endif // RUN_BACF_H
