#include "run_bacf.h"
#include <cmath>
#include "bacf_optimized.h"
#include "thread_bacf_tracking.h"
#include "widget.h"

void run_BACF(image_info seq,string video_path,double lr,track_result &results){

    //設置參數

    struct hog_parameters hog_params;
    parameters params;
    struct GrayF_parameters grayscale_params;


    //%   HOG feature parameters
    hog_params.nDim.first = "nDim";
    hog_params.nDim.second = 31;

    params.video_path = video_path;


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
    params.wsize[0] = seq.init_rect[3];
    params.wsize[1] = seq.init_rect[2];
    params.init_pos[0] = seq.init_rect[1] + floor(params.wsize[0]/2);
    params.init_pos[1] = seq.init_rect[0] + floor(params.wsize[1]/2);
    //notice : 讀取camera後沒有frame數，整合的時候需要更動
    params.s_frame = seq.s_frame;
    params.no_fram = seq.en_frame - seq.st_frame + 1;
    params.seq_st_frame = seq.st_frame;
    params.seq_en_frame = seq.en_frame;
    //notice : end

    //%   ADMM parameters, # of iteration, and lambda- mu and betha are set in the main function.
    params.admm_iterations = 2;
    params.admm_lambda = 0.01;


    //%   Debug and visualization
    params.visualization = 1;

    //BACF_optimized(params,results);
    //thread_BACF_tracking trackinThread(params);
    //trackinThread.start(QThread::TimeCriticalPriority);


    Widget w;
    w.start(QThread::TimeCriticalPriority);


}
