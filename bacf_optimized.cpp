#include "get_pixels.h"
#include "get_features.h"
#include "get_subwindow_no_window.h"
#include "resizedft2.h"
#include "resp_newton.h"

//% This function implements the BACF tracker.
void BACF_optimized(parameters &params,track_result &results){

    vector <Mat> model_xf;
    int scale_ind;
    vector <Mat> g_f;
    float old_pos[2];

    //%   Setting parameters for local use.
    double search_area_scale = params.search_area_scale;
    double output_sigma_factor = params.output_sigma_factor;
    double learning_rate = params.learning_rate;
    double filter_max_area = params.filter_max_area;
    int nScales = params.number_of_scales;
    double scale_step = params.scale_step;
    int interpolate_response = params.interpolate_response;


    struct para_features_struct features = params.t_features;
    //notice : 讀取camera後沒有frame數，整合的時候需要更動
    string video_path  = params.video_path;
    vector <string> s_frames = params.s_frame;
    //notice : end
    double pos[2];
    cout<<"pos = "<<params.init_pos[0] <<","<<params.init_pos[1]<<endl;
    pos[0] = floor((params.init_pos[0] * height) / img_h);
    pos[1] = floor((params.init_pos[1] * width) / img_w);
    cout<<"pos = "<<pos[0] <<","<<pos[1]<<endl;
    double target_sz[2];
    cout<<"target_sz = "<<params.wsize[0] <<","<<params.wsize[1]<<endl;
    target_sz[0] = floor((params.wsize[0] * height) / img_h);
    target_sz[1] = floor((params.wsize[1] * width) / img_w);
    cout<<"target_sz = "<<target_sz[0] <<","<<target_sz[1]<<endl;


    int visualization = params.visualization;
    //notice : 讀取camera後沒有frame數，整合的時候需要更動
    int num_frames = params.no_fram;
    //notice : end
    double init_target_sz[2];
    init_target_sz[0] = target_sz[0];
    init_target_sz[1] = target_sz[1];


    //%set the feature ratio to the feature-cell size
    int featureRatio = params.t_global.cell_size.second;
    double search_area,temp[2];
    for(int i = 0 ; i < 2 ; ++i){
        temp[i] = init_target_sz[i] / featureRatio * search_area_scale;
    }
    search_area = temp[0] * temp[1];



    //% when the number of cells are small, choose a smaller cell size
    if (params.t_global.cell_selection_thresh.first == "cell_selection_thresh"){
        if(search_area < params.t_global.cell_selection_thresh.second * filter_max_area){
            double prod_val = (init_target_sz[0] * search_area_scale) * (init_target_sz[1] * search_area_scale);
            params.t_global.cell_size.second = min(featureRatio, max(1, (int)ceil(sqrt(prod_val/(params.t_global.cell_selection_thresh.second * filter_max_area)))));

            featureRatio = params.t_global.cell_size.second;
            search_area = (init_target_sz[0] / featureRatio * search_area_scale) * (init_target_sz[1] / featureRatio * search_area_scale);
        }
    }


    struct cell global_feat_params;
    global_feat_params = params.t_global;



    float currentScaleFactor;
    if(search_area > filter_max_area){
        currentScaleFactor = sqrt(search_area / filter_max_area);
    }
    else{
        currentScaleFactor = 1.0;
    }


    //% target size at the initial scale
    double base_target_sz[2];
    base_target_sz[0] = target_sz[0] / currentScaleFactor;
    base_target_sz[1] = target_sz[1] / currentScaleFactor;


    //% window size, taking padding into account
    vector <double> sz(2);
    if(params.search_area_shape == "proportional") {
        //% proportional area, same aspect ratio as the target
        sz[0] = floor(base_target_sz[0] * search_area_scale);
        sz[1] = floor(base_target_sz[1] * search_area_scale);
    }
    else if(params.search_area_shape == "square"){
        //% square area, ignores the target aspect ratio
        sz[0] = sqrt((base_target_sz[0] * search_area_scale) * (base_target_sz[1] * search_area_scale));
        sz[1] = sqrt((base_target_sz[0] * search_area_scale) * (base_target_sz[1] * search_area_scale));
    }
    else if(params.search_area_shape == "fix_padding"){
        //% const padding
        sz[0] = base_target_sz[0] + sqrt((base_target_sz[0] * search_area_scale) * (base_target_sz[1] * search_area_scale) + (base_target_sz[0] - base_target_sz[1]) / 4) - (base_target_sz[0] + base_target_sz[1]) / 2;
        sz[1] = base_target_sz[1] + sqrt((base_target_sz[0] * search_area_scale) * (base_target_sz[1] * search_area_scale) + (base_target_sz[0] - base_target_sz[1]) / 4) - (base_target_sz[0] + base_target_sz[1]) / 2;
    }
    else{
        QMessageBox::warning(NULL, "Failed","Unknown 'params.search_area_shape'. Must be ''proportional'', ''square'' or ''fix_padding''");
    }



    //% set the size to exactly match the cell size
    sz[0] = round(sz[0] / featureRatio) * featureRatio;
    sz[1] = round(sz[1] / featureRatio) * featureRatio;
    double use_sz[2];
    use_sz[0] = floor(sz[0] / featureRatio);
    use_sz[1] = floor(sz[1] / featureRatio);



    //計算相關值
    //% construct the label function- correlation output, 2D gaussian function, with a peak located upon the target
    double output_sigma;
    output_sigma = sqrt(floor(base_target_sz[0]/featureRatio) * floor(base_target_sz[1]/featureRatio)) * output_sigma_factor;

    int dim_rg = ceil((use_sz[0]-1)/2.0) - (-floor((use_sz[0]-1)/2.0)) + 1;
    vector <int> rg(dim_rg , 0),temp_rg;
    for(int i = -floor((use_sz[0]-1)/2.0) ; i <= ceil((use_sz[0]-1)/2.0) ; ++i){
        temp_rg.push_back(i);
    }
    circshift(rg , temp_rg , 1 , dim_rg , 0 , -floor((use_sz[0]-1)/2.0));

    int dim_cg = ceil((use_sz[1]-1)/2.0) - (-floor((use_sz[1]-1)/2.0)) + 1;
    vector <int> cg(dim_cg , 0),temp_cg;
    for(int i = -floor((use_sz[1]-1)/2.0) ; i <= ceil((use_sz[1]-1)/2.0) ; ++i){
        temp_cg.push_back(i);
    }
    circshift(cg , temp_cg , 1 , dim_cg , 0 , -floor((use_sz[1]-1)/2.0));

    Mat rs(dim_rg,dim_cg,CV_64F);
    Mat cs(dim_rg,dim_cg,CV_64F);
    for (int i = 0; i < dim_rg; i++) {
        for (int k = 0; k < dim_cg; k++) {
            rs.at<double>(i,k) = (double)rg[i];
        }
    }
    for (int i = 0; i < dim_rg; i++) {
        for (int k = 0; k < dim_cg; k++) {
            cs.at<double>(i,k) = (double)cg[k];
        }
    }

    Mat y(dim_rg,dim_cg,CV_64F);
    y = rs.mul(rs) + cs.mul(cs);
    divide(y,pow(output_sigma,2),y);
    y = y.mul(-0.5);
    exp(y,y);

    Mat yf;
    yf = Mat::zeros(dim_rg, dim_cg, CV_32FC2);
    fft2(y,yf);




    int interp_sz[2];
    if(interpolate_response == 1){
        interp_sz[0] = use_sz[0] * featureRatio;
        interp_sz[1] = use_sz[1] * featureRatio;
    }
    else{
        interp_sz[0] = use_sz[0];
        interp_sz[1] = use_sz[1];
    }



    //% construct cosine window
    Mat cos_window(use_sz[0],use_sz[1],CV_32F);
    vector <float> hann_val(use_sz[0]);
    vector <float> hann_valT(use_sz[1]);
    hanning(use_sz[0],hann_val);
    hanning(use_sz[1],hann_valT);
    for(int i = 0 ; i < use_sz[0] ; ++i){
        for(int j = 0 ; j < use_sz[1] ; ++j){
            cos_window.at<float>(i,j) = hann_val[i] * hann_valT[j];
        }
    }


    //% Calculate feature dimension
    Mat im;
    try{
        im = imread(video_path + "/img0/" + s_frames[0]);
        resize(im,im,Size(width,height));
    }
    catch(exception& e){
        try{
            im = imread(s_frames[0]);
            resize(im,im,Size(width,height));
        }
        catch(exception& e){
            //%disp([video_path '/' s_frames{1}])
            im = imread(video_path + "/" + s_frames[0]);
            resize(im,im,Size(width,height));
        }
    }


    bool colorImage;
    if(im.channels() == 3){
        //notice : 判斷3個channel是否都一樣
        int cnt = 0;
        for(int i = 0 ; i < im.rows ; ++i){
            for(int j = 0 ; j < im.cols ; ++j){
                if((im.at<Vec3b>(i,j)[0]) != (im.at<Vec3b>(i,j)[1])){
                    cnt++;
                    if(cnt > 0){
                        break;
                    }
                }
            }
            if(cnt > 0){
                break;
            }
        }
        if(cnt == 0){
            colorImage = false;
        }
        else{
            colorImage = true;
        }
    }
    else{
        colorImage = false;
    }


    //% compute feature dimensionality
    int feature_dim = 0;
    //-length(features) = 1-//
    for(int i = 0 ; i < 1 ; ++i){
        if(!(features.fparams.second.useForColor.first == "useForColor")){
            features.fparams.second.useForColor.first = "useForColor";
            features.fparams.second.useForColor.second = true;
        }
        if(!(features.fparams.second.useForColor.first == "useForGray")){
            features.fparams.second.useForGray.first = "useForGray";
            features.fparams.second.useForGray.second = true;
        }
        if((features.fparams.second.useForColor.second && colorImage) || (features.fparams.second.useForGray.second && !colorImage)){
            feature_dim = feature_dim + features.fparams.second.nDim.second;
        }
    }



    if(im.channels() > 3 && colorImage == false){
        cvtColor(im,im,CV_BGR2GRAY);
    }



    vector <int> scale_exp;
    vector <float> scaleFactors;
    double min_scale_factor;
    double max_scale_factor;
    if(nScales > 0){
        for(int i = -floor((nScales-1)/2) ; i <= ceil((nScales-1)/2) ; ++i){
            scale_exp.push_back(i);
        }
        for(int i = 0 ; i < scale_exp.size() ; ++i){
            scaleFactors.push_back(pow(scale_step,scale_exp[i]));
        }
        min_scale_factor = pow(scale_step,ceil(log(max(5 / sz[0] , 5 / sz[1])) / log(scale_step)));
        max_scale_factor = pow(scale_step,floor(log(min(im.rows / base_target_sz[0] , im.cols / base_target_sz[1])) / log(scale_step)));
    }




    int dim_ky = ceil((use_sz[0]-1)/2.0) - (-floor((use_sz[0]-1)/2.0)) + 1;
    int dim_kx = ceil((use_sz[1]-1)/2.0) - (-floor((use_sz[1]-1)/2.0)) + 1;
    vector <int> vec_ky(dim_ky , 0);
    Mat ky(1,vec_ky.size(),CV_32FC2,Scalar(0,0));
    vector <int> vec_kx(dim_kx , 0);
    Mat kx(vec_kx.size(),1,CV_32FC2,Scalar(0,0));
    double newton_iterations;
    if(interpolate_response >= 3){
        //% Pre-computes the grid that is used for score optimization
        vector <int> temp_ky;
        for(int i = -floor((use_sz[0]-1)/2) ; i <= ceil((use_sz[0]-1)/2) ; ++i){
            temp_ky.push_back(i);
        }
        circshift(vec_ky , temp_ky , 1 , dim_ky , 1 , -floor((use_sz[0]-1)/2));
        for(int i = 0 ; i < vec_ky.size() ; ++i){
            ky.at<Vec2f>(0,i)[0] = vec_ky.at(i);
        }

        vector <int> temp_kx;
        for(int i = -floor((use_sz[1]-1)/2) ; i <= ceil((use_sz[1]-1)/2) ; ++i){
            temp_kx.push_back(i);
        }
        circshift(vec_kx , temp_kx , 1 , dim_kx , 1 , -floor((use_sz[1]-1)/2));
        for(int i = 0 ; i < vec_kx.size() ; ++i){
            kx.at<Vec2f>(i,0)[0] = vec_kx.at(i);
        }

        newton_iterations = params.newton_iterations;
    }


    //% initialize the projection matrix (x,y,h,w)
    //--rect_position = zeros(num_frames, 4);
    //vector <vector <double> > rect_position(num_frames,vector <double>(4,0));
    //think
    //vector <Rect> rect_position(num_frames,Rect(0,0,0,0));


    //--time = 0;
    double time = 0;


    //% allocate memory for multi-scale tracking
    vector <Mat> multires_pixel_template(nScales);

    vector <int> small_filter_sz(2);
    small_filter_sz[0] = floor(base_target_sz[0]/featureRatio);
    small_filter_sz[1] = floor(base_target_sz[1]/featureRatio);




    double loop_frame = 1;
    int num_images = 1;
    for(int frame_num = 1 ; frame_num <= s_frames.size() ; ++frame_num){
        //%load image
        try{
            im = imread(video_path + "/img0/" + s_frames[frame_num-1]);
            resize(im,im,Size(width,height));
        }
        catch(exception& e){
            try{
                im = imread(s_frames[frame_num-1]);
                resize(im,im,Size(width,height));
            }
            catch(exception& e){
                im = imread(video_path + "/" + s_frames[frame_num-1]);
                resize(im,im,Size(width,height));
            }
        }
        if(im.channels() > 1 && colorImage == false){
            cvtColor(im,im,CV_BGR2GRAY);
        }


        //紀錄起始時間
        //--tic();
        double start_time = clock();


        //%do not estimate translation and scaling on the first frame, since we
        //%just want to initialize the tracker there
        if(frame_num > 1){
            for(scale_ind = 0 ; scale_ind < nScales ; ++scale_ind){
                //--multires_pixel_template(:,:,:,scale_ind) = ...
                    //--get_pixels(im, pos, round(sz*currentScaleFactor*scaleFactors(scale_ind)), sz);
                vector <double> sz_round(2);
                sz_round[0] = round(sz[0]*currentScaleFactor*scaleFactors[scale_ind]);
                sz_round[1] = round(sz[1]*currentScaleFactor*scaleFactors[scale_ind]);
                Mat get_pixels_img = get_pixels(im , pos , sz_round , sz);
                multires_pixel_template[scale_ind] = get_pixels_img.clone();

            }


            //--xtf = fft2(bsxfun(@times,get_features(multires_pixel_template,features,global_feat_params),cos_window));
            num_images = nScales;
            vector <vector <Mat>> feature_pixels(num_images);
            double support_sz[2];

            get_features(multires_pixel_template,features,global_feat_params,num_images,feature_pixels,support_sz);


            vector <vector <Mat>> xtf(num_images);
            vector <Mat> responsef;
            for(int k = 0 ; k < num_images ; ++k){
                Mat sum_temp = Mat::zeros(g_f.at(0).rows, g_f.at(0).cols, CV_32FC2);

                for(int n = 0 ; n < feature_dim ; ++n){
                    Mat mul_value;
                    mul_value = feature_pixels[k].at(n).mul(cos_window);

                    Mat xtf_temp;
                    fft2(mul_value,xtf_temp);
                    xtf[k].push_back(xtf_temp.clone());


                    //--responsef = permute(sum(bsxfun(@times, conj(g_f), xtf), 3), [1 2 4 3]);
                    Mat g_f_conj = QT_conj_m(g_f.at(n));
                    Mat res_bsx_times = QT_M_mul_M(g_f_conj,xtf.at(k).at(n));

                    sum_temp = sum_temp + res_bsx_times;

                }

                responsef.push_back(sum_temp.clone());
            }



            //% if we undersampled features, we want to interpolate the
            //% response so it has the same size as the image patch
            if(interpolate_response == 2){
                //% use dynamic interp size
                //--interp_sz = floor(size(y) * featureRatio * currentScaleFactor);
                interp_sz[0] = floor(dim_rg * featureRatio * currentScaleFactor);
                interp_sz[1] = floor(dim_cg * featureRatio * currentScaleFactor);
            }
            //--responsef_padded = resizeDFT2(responsef, interp_sz);
            vector <Mat> responsef_padded;
            resizeDFT2(responsef,interp_sz,responsef_padded);


            //% response in the spatial domain
            //--response = ifft2(responsef_padded, 'symmetric');
            vector <Mat> response;
            for(int n = 0 ; n < responsef_padded.size() ; ++n){
                Mat idft_symmetric ;//= Mat::zeros(responsef_padded[0].rows,responsef_padded[0].cols,CV_32F);
                idft(responsef_padded.at(n),idft_symmetric,DFT_REAL_OUTPUT+DFT_SCALE,0);
                response.push_back(idft_symmetric.clone());
            }

            //% find maximum peak
            float disp_row,disp_col;
            int sind;
            if(interpolate_response == 3){
                //--error('Invalid parameter value for interpolate_response');
                QMessageBox::warning(NULL, "Failed","Invalid parameter value for interpolate_response");
            }
            else if(interpolate_response == 4){
                //--[disp_row, disp_col, sind] = resp_newton(response, responsef_padded, newton_iterations, ky, kx, use_sz);
                resp_newton(response, responsef_padded, newton_iterations, ky, kx, use_sz, disp_row, disp_col, sind);
            }
            else{
                //matlab以行為主
                //--[row, col, sind] = ind2sub(size(response), find(response == max(response(:)), 1));
                double maxVal = -10000;
                Point maxLoc;
                int dim_max = -1;
                for(int n = 0 ; n <response.size() ; ++n){
                    double maxV;
                    Point maxL;
                    //opencv找出的最大值是以列為主，因此需要找以行為主最大值的座標
                    minMaxLoc(response.at(n),0,&maxV,0,&maxL);
                    if(maxVal < maxV){
                        dim_max = n;
                        maxVal = maxV;
                        maxLoc = maxL;
                    }
                }
                bool find = false;
                for(int j = 0 ; j < maxLoc.x  ; ++j){
                    for(int  i = maxLoc.y ; i < response.at(dim_max).rows ; ++i){
                        if(maxVal == response.at(dim_max).at<float>(i,j)){
                            maxLoc.x = j;
                            maxLoc.y = i;
                            find = true;
                            break;
                        }
                    }
                    if(find){
                        break;
                    }
                }
                int row = maxLoc.y;
                int col = maxLoc.x;
                sind = dim_max;


                //--disp_row = mod(row - 1 + floor((interp_sz(1)-1)/2), interp_sz(1)) - floor((interp_sz(1)-1)/2);
                disp_row = mod((float)row - 1 + floor((float)(interp_sz[0]-1)/2), interp_sz[0]) - floor((float)(interp_sz[0]-1)/2);
                //--disp_col = mod(col - 1 + floor((interp_sz(2)-1)/2), interp_sz(2)) - floor((interp_sz(2)-1)/2);
                disp_col = mod((float)col - 1 + floor((float)(interp_sz[1]-1)/2), interp_sz[1]) - floor((float)(interp_sz[1]-1)/2);
            }


            //% calculate translation
            vector <int> translation_vec;
            //--switch interpolate_response
            switch(interpolate_response){
                case 0:
                    //--translation_vec = round([disp_row, disp_col] * featureRatio * currentScaleFactor * scaleFactors(sind));
                    translation_vec.push_back(round(disp_row * featureRatio * currentScaleFactor * scaleFactors.at(sind)));
                    translation_vec.push_back(round(disp_col * featureRatio * currentScaleFactor * scaleFactors.at(sind)));
                case 1:
                    //--translation_vec = round([disp_row, disp_col] * currentScaleFactor * scaleFactors(sind));
                    translation_vec.push_back(round(disp_row * currentScaleFactor * scaleFactors.at(sind)));
                    translation_vec.push_back(round(disp_col * currentScaleFactor * scaleFactors.at(sind)));
                case 2:
                    //--translation_vec = round([disp_row, disp_col] * scaleFactors(sind));
                    translation_vec.push_back(round(disp_row * scaleFactors.at(sind)));
                    translation_vec.push_back(round(disp_col * scaleFactors.at(sind)));
                case 3:
                    //--translation_vec = round([disp_row, disp_col] * featureRatio * currentScaleFactor * scaleFactors(sind));
                    translation_vec.push_back(round(disp_row * featureRatio * currentScaleFactor * scaleFactors.at(sind)));
                    translation_vec.push_back(round(disp_col * featureRatio * currentScaleFactor * scaleFactors.at(sind)));
                case 4:
                    //--translation_vec = round([disp_row, disp_col] * featureRatio * currentScaleFactor * scaleFactors(sind));
                    translation_vec.push_back(round(disp_row * featureRatio * currentScaleFactor * scaleFactors.at(sind)));
                    translation_vec.push_back(round(disp_col * featureRatio * currentScaleFactor * scaleFactors.at(sind)));
            }


            //% set the scale
            //--currentScaleFactor = currentScaleFactor * scaleFactors(sind);
            currentScaleFactor = currentScaleFactor * scaleFactors.at(sind);


            //% adjust to make sure we are not too large or too small
            if(currentScaleFactor < min_scale_factor){
                //--currentScaleFactor = min_scale_factor;
                currentScaleFactor = (float)min_scale_factor;
            }
            else if(currentScaleFactor > max_scale_factor){
                //--currentScaleFactor = max_scale_factor;
                currentScaleFactor = (float)max_scale_factor;
            }

            //% update position
            //--old_pos = pos;
            old_pos[0] = (float)pos[0];
            old_pos[1] = (float)pos[1];

            //--pos = pos + translation_vec;
            pos[0] = pos[0] + translation_vec.at(0);
            pos[1] = pos[1] + translation_vec.at(1);


        }


        num_images = 1;

        //% extract training sample image region
        vector <double> round_sz_out(2);
        round_sz_out[0] = round(sz[0]*currentScaleFactor);
        round_sz_out[1] = round(sz[1]*currentScaleFactor);
        vector <Mat> pixels(1);
        pixels[0]= get_pixels(im , pos , round_sz_out , sz);

        //imshow("pixel",pixels.at(0));
        //waitKey(1);

        //% extract features and do windowing
        //--xf = fft2(bsxfun(@times,get_features(pixels,features,global_feat_params),cos_window));
        vector <vector <Mat>> feature_pixels_out(num_images);
        double support_sz_out[2];
        get_features(pixels,features,global_feat_params,num_images,feature_pixels_out,support_sz_out);

        //imshow("feature",feature_pixels_out.at(0).at(0));
        //waitKey(0);

        vector <vector <Mat>> bsx_times(num_images);
        for(int k = 0 ; k < num_images ; ++k){
            for(int n = 0 ; n < feature_dim ; ++n){
                //Mat mul_value = Mat::zeros(use_sz[0],use_sz[1],CV_32F);
                //mul_value = feature_pixels_out[k].at(n).mul(cos_window);
                bsx_times[k].push_back(feature_pixels_out[k].at(n).mul(cos_window));
            }
        }
        vector <Mat> xf;
        for(int k = 0 ; k < num_images ; ++k){
            for(int n = 0 ; n < bsx_times[k].size() ; ++n){
                Mat xf_temp ;
                fft2(bsx_times[k][n],xf_temp);
                xf.push_back(xf_temp.clone());
            }
        }



        if(frame_num == 1){
            CopyMatVector(xf,model_xf);
        }
        else{
            for(int n = 0 ; n < model_xf.size() ; n++){
                //Mat temp;
                //temp = (model_xf[n].mul(1.0 - (float)learning_rate)) + (xf[n].mul((float)learning_rate));
                model_xf[n] = (model_xf[n].mul(1.0 - (float)learning_rate)) + (xf[n].mul((float)learning_rate));

            }
        }



        g_f.clear();
        vector <Mat> h_f;
        vector <Mat> l_f;
        Mat zero = Mat::zeros(xf[0].rows,xf[0].cols,CV_32FC2);

        for(int j = 0 ; j < xf.size() ; ++j){
            g_f.push_back(zero.clone());
            h_f.push_back(zero.clone());
            l_f.push_back(zero.clone());
        }


        double mu = 1;

        double betha = 10;

        double mumax = 10000;

        double i = 1;


        double T = use_sz[0] * use_sz[1];


        //--S_xx = sum(conj(model_xf) .* model_xf, 3);
        //vector <Mat> model_xf_conj = QT_conj(model_xf);
        //vector <Mat> mul_model_xf = QT_vec_mul_vec(model_xf_conj,model_xf);
        Mat S_xx_temp(model_xf[0].rows,model_xf[0].cols,CV_32FC2,Scalar(0,0));
        /*for(int n = 0 ; n < mul_model_xf.size() ; ++n){
            S_xx_temp = S_xx_temp + mul_model_xf.at(n);
        }*/
        for(int n = 0 ; n < model_xf.size() ; ++n){
            Mat model_xf_conj2 = QT_conj_m(model_xf.at(n));
            Mat mul_model_xf2 = QT_M_mul_M(model_xf_conj2,model_xf.at(n));
            S_xx_temp = S_xx_temp + mul_model_xf2;
        }
        vector <Mat> temp;
        split(S_xx_temp,temp);

        Mat S_xx;
        S_xx = temp.at(0).clone();


        params.admm_iterations = 2;


        //%   ADMM
        while (i <= params.admm_iterations ) {
            //%   solve for G- please refer to the paper for more details
            //-- B = S_xx + (T * mu);
            Mat B; //沒有虛數
            add((T * mu),S_xx,B);


            //--S_lx = sum(conj(model_xf) .* l_f, 3);
            Mat S_lx(model_xf[0].rows,model_xf[0].cols,CV_32FC2,Scalar(0,0));
            Mat S_hx(model_xf[0].rows,model_xf[0].cols,CV_32FC2,Scalar(0,0));
            vector <Mat> h;

            for(int n = 0 ; n < model_xf.size() ; ++n){
                //--S_lx = sum(conj(model_xf) .* l_f, 3);
                Mat model_xf_conj2 = QT_conj_m(model_xf.at(n));
                Mat mul_model_xf2 = QT_M_mul_M(model_xf_conj2,l_f.at(n));
                S_lx = S_lx + mul_model_xf2;

                //--S_hx = sum(conj(model_xf) .* h_f, 3);
                mul_model_xf2 = QT_M_mul_M(model_xf_conj2,h_f.at(n));
                S_hx = S_hx + mul_model_xf2;


                //各別算出值
                //1. one = ((1/(T*mu)) * bsxfun(@times, yf, model_xf))
                //2. two = ((1/mu) * l_f)
                //3. h_f
                //4. three = ((1/(T*mu)) * bsxfun(@times, model_xf, (S_xx .* yf)))
                //5. four = ((1/mu) * bsxfun(@times, model_xf, S_lx))
                //6. five = (bsxfun(@times, model_xf, S_hx))
                //7. six = bsxfun(@rdivide,(three - four + five), B)
                //g_f = (one - two + h_f) - six;
                //--g_f = (((1/(T*mu)) * bsxfun(@times, yf, model_xf)) - ((1/mu) * l_f) + h_f) - ...
                    //--bsxfun(@rdivide,(((1/(T*mu)) * bsxfun(@times, model_xf, (S_xx .* yf))) - ((1/mu) * bsxfun(@times, model_xf, S_lx)) + (bsxfun(@times, model_xf, S_hx))), B);


                //three - four + five
                Mat three_four_five = QT_M_mul_M(model_xf.at(n),QT_M_mul_M(S_xx,yf)).mul(1.0/(T*mu)) //three
                        - QT_M_mul_M(model_xf.at(n),S_lx).mul(1.0/mu) //four
                        + QT_M_mul_M(model_xf.at(n),S_hx).clone(); //five

                vector <Mat> temp2;
                split(three_four_five,temp2);
                vector <Mat> temp3(2);
                temp3.at(0) = temp2.at(0) / B;
                temp3.at(1) = temp2.at(1) / B;

                Mat six;
                merge(temp3,six);
                g_f.at(n) = (QT_M_mul_M(yf,model_xf.at(n)).mul(1.0/(T*mu)) - l_f.at(n).mul(1.0/mu) + h_f.at(n)) - six;


                //%   solve for H
                //--h = (T/((mu*T)+ params.admm_lambda))* ifft2((mu*g_f) + l_f);
                Mat iff2_para = g_f.at(n).mul(mu) + l_f.at(n);
                Mat iff2_temp ;
                idft(iff2_para, iff2_temp, DFT_COMPLEX_OUTPUT+DFT_SCALE, 0);

                h.push_back(iff2_temp.mul(T/((mu*T)+ params.admm_lambda)));

            }



            //--[sx,sy,h] = get_subwindow_no_window(h, floor(use_sz/2) , small_filter_sz);
            vector <int> use_sz_temp(2);
            use_sz_temp[0] = floor(use_sz[0]/2);
            use_sz_temp[1] = floor(use_sz[1]/2);
            vector <int> sx;
            vector <int> sy;
            get_subwindow_no_window(h,use_sz_temp,small_filter_sz,sx,sy);


            vector <Mat> t;
            Mat zero = Mat::zeros(use_sz[0],use_sz[1],CV_32FC2);
            Rect roi(sy[0],sx[0],sy.size(),sx.size());
            for(int n = 0 ; n < h.size() ; ++n){
                //--t = single(zeros(use_sz(1), use_sz(2), size(h,3)));
                t.push_back(zero.clone());


                //--t(sx,sy,:) = h;
                addWeighted(t.at(n)(roi),0,h.at(n),1,0,t.at(n)(roi));


                //--h_f = fft2(t);
                Mat t_fft;
                fft2(t.at(n),t_fft);
                //dft(t[j],t_fft,DFT_COMPLEX_OUTPUT);
                h_f.at(n) = t_fft.clone();


                //%   update L
                //--l_f = l_f + (mu * (g_f - h_f));
                Mat value = l_f.at(n) + (mu * (g_f.at(n) - h_f.at(n)));
                l_f.at(n) = value.clone();
            }



            //%   update mu- betha = 10.
            //--mu = min(betha * mu, mumax);
            mu = min(betha * mu, mumax);


            //--i = i+1;
            ++i;

        }


        //--target_sz = floor(base_target_sz * currentScaleFactor);
        target_sz[0] = floor(base_target_sz[0] * currentScaleFactor);
        target_sz[1] = floor(base_target_sz[1] * currentScaleFactor);

        //%save position and calculate FPS
        //--rect_position(loop_frame,:) = [pos([2,1]) - floor(target_sz([2,1])/2), target_sz([2,1])];
        //think
        /*if(loop_frame < 4){
            rect_position.at(loop_frame-1).x = pos[1] - floor(target_sz[1]/2);
            rect_position.at(loop_frame-1).y = pos[0] - floor(target_sz[0]/2);
            rect_position.at(loop_frame-1).width = target_sz[1];
            rect_position.at(loop_frame-1).height = target_sz[0];
        }
        else{
            Rect rect(pos[1] - floor(target_sz[1]/2),pos[0] - floor(target_sz[0]/2),target_sz[1],target_sz[0]);
            rect_position.push_back(rect);
        }*/


        //--time = time + toc();
        double end_time = clock();
        time = 1 / ((end_time - start_time) / CLOCKS_PER_SEC);
        cout<<"fps = "<<time<<endl;
//        cout<<"-----------------------------------"<<endl;
//        cout  << "executing time : " << (end_time - start_time) / CLOCKS_PER_SEC << "s" << endl;
//        cout<<"-----------------------------------"<<endl;


//        %visualization
        if(visualization == 1){

//                rect_position_vis = [pos([2,1]) - target_sz([2,1])/2, target_sz([2,1])];
            double rect_position_vis[4] = {(pos[1] - target_sz[1]/2) , (pos[0] - target_sz[0]/2) , target_sz[1] , target_sz[0]};


//                im_to_show = double(im)/255;
            Mat im_to_show;
            im.convertTo(im_to_show,CV_64FC3);
            im_to_show = im_to_show / 255;

            if(im_to_show.channels() == 1){
//                    im_to_show = repmat(im_to_show, [1 1 3]);
                for(int i = 0 ; i < im_to_show.rows ; ++i){
                    for(int j = 0 ; j < im_to_show.cols ; ++j){
                        im_to_show.at<Vec3f>(i,j)[1] = im_to_show.at<Vec3f>(i,j)[0];
                        im_to_show.at<Vec3f>(i,j)[2] = im_to_show.at<Vec3f>(i,j)[0];
                    }
                }
            }

            double scale=2;
            Size dsize = Size(im_to_show.cols*scale,im_to_show.rows*scale);


            if(frame_num == 1){
                //putText(im_to_show,"FPS: " + to_string(time) ,      Point(20,40),  FONT_HERSHEY_COMPLEX ,       0.5,Scalar(0,255,0));
                rectangle(im_to_show,Point(rect_position_vis[0],rect_position_vis[1]),Point((rect_position_vis[0]+rect_position_vis[2]),(rect_position_vis[1]+rect_position_vis[3])),Scalar(0,255,0),2);
                //resize(im_to_show,im_to_show,dsize);
                imshow("Tracking",im_to_show);
                waitKey(0);

            }
            else{
                //putText(im_to_show,"FPS: " + to_string(time) ,      Point(20,40),  FONT_HERSHEY_COMPLEX ,       0.5,Scalar(0,255,0));
                rectangle(im_to_show,Point(rect_position_vis[0],rect_position_vis[1]),Point((rect_position_vis[0]+rect_position_vis[2]),(rect_position_vis[1]+rect_position_vis[3])),Scalar(0,255,0),2);
                //resize(im_to_show,im_to_show,dsize);
                imshow("Tracking",im_to_show);
                waitKey(1);

            }

        }


        ++loop_frame;

    }

    cout<<"time = "<<time<<endl;
//    %   save resutls.
//    fps = loop_frame / time;
    double fps = loop_frame / time;
//    results.type = 'rect';
    results.type = "rect";
//    results.res = rect_position;
    //results.res = rect_position;
//    results.fps = fps;
    results.fps = fps;
    Mat c(250,250,CV_32F,Scalar(3));
    imshow("Tracking",c);
    waitKey(0);
}


/*Mat QT_M1_mul_M2(Mat &M_Src1,Mat &M_Src2){
    //不同channel的mat相乘,M_Src1是1 channel,M_Src2是2 channels

    vector <Mat> src2;
    split(M_Src2,src2);

    vector <Mat> mul_result(2);

    mul_result.at(0) = M_Src1.mul(src2.at(0));
    mul_result.at(1) = M_Src1.mul(src2.at(1));

    Mat result;
    merge(mul_result,result);

    return result;

}*/

Mat QT_M_mul_M(Mat &M_Src1,Mat &M_Src2){

    //M_Src2是否只有一個元素
    bool one_element = false;
    if(M_Src2.rows == 1 && M_Src2.cols == 1){
        one_element = true;
    }


    vector <Mat> src1;
    vector <Mat> src2;
    vector <Mat> mul_result(2);

    split(M_Src1,src1);
    split(M_Src2,src2);


    if(one_element){

        //M_Src2 && M_Src1 -> 2 channels
        if(M_Src2.type() >= 8 && M_Src1.type() >= 8){
            mul_result.at(0) = (src1.at(0).mul(src2.at(0).at<float>(0,0))) - (src1.at(1).mul(src2.at(1).at<float>(0,0)));
            mul_result.at(1) = (src1.at(0).mul(src2.at(1).at<float>(0,0))) + (src1.at(1).mul(src2.at(0).at<float>(0,0)));
        }
        //M_Src2 -> 1 channel , M_Src1 -> 2 channels
        else if(M_Src2.type() < 8 && M_Src1.type() >= 8){
            mul_result.at(0) = src1.at(0).mul(src2.at(0).at<float>(0,0));
            mul_result.at(1) = src1.at(1).mul(src2.at(0).at<float>(0,0));
        }
        //M_Src2 -> 2 channels , M_Src1 -> 1 channel
        else if(M_Src2.type() >= 8 && M_Src1.type() < 8){
            mul_result.at(0) = src1.at(0).mul(src2.at(0).at<float>(0,0));
            mul_result.at(1) = src1.at(0).mul(src2.at(1).at<float>(0,0));
        }
        //M_Src2 && M_Src1 -> 1 channels
        else{
            mul_result.at(0) = src1.at(0).mul(src2.at(0).at<float>(0,0));
            mul_result.at(1) = src1.at(0).mul(0);
        }


    }
    else{

        //M_Src2 && M_Src1 -> 2 channels
        if(M_Src2.type() >= 8 && M_Src1.type() >= 8){
            mul_result.at(0) = (src1.at(0).mul(src2.at(0))) - (src1.at(1).mul(src2.at(1)));
            mul_result.at(1) = (src1.at(0).mul(src2.at(1))) + (src1.at(1).mul(src2.at(0)));
        }
        //M_Src2 -> 1 channel , M_Src1 -> 2 channels
        else if(M_Src2.type() < 8 && M_Src1.type() >= 8){
            mul_result.at(0) = src1.at(0).mul(src2.at(0));
            mul_result.at(1) = src1.at(1).mul(src2.at(0));
        }
        //M_Src2 -> 2 channels , M_Src1 -> 1 channel
        else if(M_Src2.type() >= 8 && M_Src1.type() < 8){
            mul_result.at(0) = src1.at(0).mul(src2.at(0));
            mul_result.at(1) = src1.at(0).mul(src2.at(1));
        }
        //M_Src2 && M_Src1 -> 1 channels
        else{
            mul_result.at(0) = src1.at(0).mul(src2.at(0));
            mul_result.at(1) = src1.at(0).mul(0);
        }


    }


    Mat result;
    merge(mul_result,result);

    return result;
}


vector <Mat> QT_vec_mul_vec(vector <Mat> &Vec_Src1 , vector <Mat> &Vec_Src2){
    int Num_dim = Vec_Src1.size();

    vector <Mat> mul_ans;

    for(int n = 0 ; n < Num_dim ; ++n){
        vector <Mat> src1;
        vector <Mat> src2;
        vector <Mat> mul_result(2);

        split(Vec_Src1.at(n),src1);
        split(Vec_Src2.at(n),src2);


        mul_result.at(0) = (src1.at(0).mul(src2.at(0))) - (src1.at(1).mul(src2.at(1)));
        mul_result.at(1) = (src1.at(0).mul(src2.at(1))) + (src1.at(1).mul(src2.at(0)));


        Mat result;
        merge(mul_result,result);

        mul_ans.push_back(result.clone());
    }

    return mul_ans;
}

Mat QT_conj_m(Mat &src){
    vector <Mat> src_temp;

    split(src,src_temp);

    vector <Mat> conj_result(2);


    conj_result.at(0) = src_temp.at(0).clone();
    conj_result.at(1) = src_temp.at(1).mul(-1);

    Mat result;
    merge(conj_result,result);

    return result;
}

vector <Mat> QT_conj(vector <Mat> &Vec_Src){
    int Num_dim = Vec_Src.size();

    vector <Mat> conj_ans;
    for(int n = 0 ; n < Num_dim ; ++n){
        vector <Mat> src;

        split(Vec_Src.at(n),src);

        vector <Mat> conj_result(2);


        conj_result.at(0) = src.at(0).clone();
        conj_result.at(1) = src.at(1).mul(-1);

        Mat result;
        merge(conj_result,result);
        conj_ans.push_back(result.clone());

    }
    return conj_ans;
}



template<typename ty>
void circshift(ty &out, const ty &in, int xdim, int ydim, int xshift, int yshift)
{
    for (int i =0; i < xdim; i++) {
        int ii = (i + xshift) % xdim;
        if (ii<0) ii = xdim + ii;
        for (int j = 0; j < ydim; j++) {
            int jj = (j + yshift) % ydim;
            if (jj<0) jj = ydim + jj;
            out[ii * ydim + jj] = in[i * ydim + j];
        }
    }
}

/*void ndgrid(const int rg[], const int cg[], int rs[][dim_cg] ,int cs[][dim_cg])
{
   for (int i = 0; i < dim_rg; i++) {
       for (int k = 0; k < dim_cg; k++) {
           rs[i][k] = rg[i];
       }
   }
   for (int i = 0; i < dim_rg; i++) {
       for (int k = 0; k < dim_cg; k++) {
           cs[i][k] = cg[k];
       }
   }
}*/

//快速傅立葉轉換
void fft2(const Mat &inputImg, Mat &Fourier)
{
    int mat_type = inputImg.type();
    assert(mat_type<15); //不支持的格式

    if (mat_type < 7)
    {//單通道
        //cout<<"single"<<endl;
        Mat planes[] = { Mat_<float>(inputImg), Mat::zeros(inputImg.size(),CV_32F) };
        merge(planes, 2, Fourier);
        dft(Fourier, Fourier);
    }
    else // 7<mat_type<15
    {//多通道
        //cout<<"multiple"<<endl;
        //Mat tmp;
        dft(inputImg, Fourier);
        /*vector<Mat> planes;
        split(tmp, planes);
        magnitude(planes[0], planes[1], planes[0]); //?复??化?幅值
        Fourier = planes[0];*/
    }
}

void hanning(int N, vector <float> &ans)
{
    for(int i = 0;i <= N-1 ; ++i){
        ans[i] = 0.5*(1 - cos(2*M_PI*i/(N-1)));
    }
}

void CopyMatVector(vector <Mat> &old_vec , vector <Mat> &new_vec){
    new_vec.clear();
    for(int n = 0 ; n < old_vec.size() ; ++n){
        new_vec.push_back(old_vec[n].clone());
    }
}


void fftshift(Mat &out)
{
    Size sz = out.size();
    Point pt(0, 0);
    pt.x = (int)floor(sz.width / 2.0);
    pt.y = (int)floor(sz.height / 2.0);
    circshift(out, pt);
}

void circshift(Mat &out, const Point &delta)
{
    Size sz = out.size();

    // 錯誤檢查
    assert(sz.height > 0 && sz.width > 0);
    // 此種情況不需要移動
    if ((sz.height == 1 && sz.width == 1) || (delta.x == 0 && delta.y == 0))
        return;

    // 需要移動參數的變換，這樣就能輸入各種整數了
    int x = delta.x;
    int y = delta.y;
    if (x > 0) x = x % sz.width;
    if (y > 0) y = y % sz.height;
    if (x < 0) x = x % sz.width + sz.width;
    if (y < 0) y = y % sz.height + sz.height;


    // 多维的Mat也能移動
    vector<Mat> planes;
    split(out, planes);

    for (size_t i = 0; i < planes.size(); i++)
    {
        // 垂直方向移動
        Mat tmp0, tmp1, tmp2, tmp3;
        Mat q0(planes[i], Rect(0, 0, sz.width, sz.height - y));
        Mat q1(planes[i], Rect(0, sz.height - y, sz.width, y));
        q0.copyTo(tmp0);
        q1.copyTo(tmp1);
        tmp0.copyTo(planes[i](Rect(0, y, sz.width, sz.height - y)));
        tmp1.copyTo(planes[i](Rect(0, 0, sz.width, y)));

        // 水平方向移動
        Mat q2(planes[i], Rect(0, 0, sz.width - x, sz.height));
        Mat q3(planes[i], Rect(sz.width - x, 0, x, sz.height));
        q2.copyTo(tmp2);
        q3.copyTo(tmp3);
        tmp2.copyTo(planes[i](Rect(x, 0, sz.width - x, sz.height)));
        tmp3.copyTo(planes[i](Rect(0, 0, x, sz.height)));
    }

    merge(planes, out);
}
