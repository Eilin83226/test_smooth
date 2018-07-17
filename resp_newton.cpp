#include "resp_newton.h"
#include "bacf_optimized.h"

void resp_newton(vector <Mat> &response,vector <Mat> &responsef,double iterations,Mat &ky,Mat &kx,double use_sz[],float &disp_row,float &disp_col,int &sind){

    //double START,END;
    //START = clock();

    vector <Mat> max_resp_row(response.size());
    vector <Mat> max_row(response.size());

    vector <Mat> init_max_response(response.size());
    vector <Mat> max_col(response.size());

    for(int n = 0 ; n < response.size() ; ++n){

//    [max_resp_row, max_row] = max(response, [], 1);
        //注意 : 1 -> 行向取得最大
        Mat m_Max1(1,response.at(n).cols,CV_32F,Scalar(-10000));
        Mat m_index1(1,response.at(n).cols,CV_32F);
        for(int j = 0 ; j < response.at(n).cols ; ++j){
            for(int i = 0 ; i < response.at(n).rows ; ++i){
                //cout<<"i,j = "<<i<<", "<<j<<" : "<<response.at(n).at<float>(i,j)<<endl;
                if(m_Max1.at<float>(0,j) < response.at(n).at<float>(i,j)){
                    m_Max1.at<float>(0,j) = response.at(n).at<float>(i,j);
                    m_index1.at<float>(0,j) = (float)i;
                    //cout<<Max<<","<<index<<endl;
                }
            }
        }
        max_resp_row.at(n).push_back(m_Max1);
        //cout<<max_resp_row.at(n)<<endl;
        max_row.at(n).push_back(m_index1);
        //cout<<max_row.at(n)<<endl;


//    [init_max_response, max_col] = max(max_resp_row, [], 2);
        //注意 : 2 -> 列向取得最大
        Mat m_Max2(1,1,CV_32F,Scalar(-10000));
        Mat m_index2(1,1,CV_32F);

        for(int j = 0 ; j < max_resp_row.at(n).cols ; ++j){
            if(m_Max2.at<float>(0,0) < max_resp_row.at(n).at<float>(0,j)){
                m_Max2.at<float>(0,0) = max_resp_row.at(n).at<float>(0,j);
                m_index2.at<float>(0,0) = (float)j;
            }
        }
        init_max_response.at(n).push_back(m_Max2);
        max_col.at(n).push_back(m_index2);
    }


//    [init_max_response, max_col] = max(max_resp_row, [], 2);
/*    vector <Mat> init_max_response(response.size());
    vector <Mat> max_col(response.size());
    for(int n = 0 ; n < response.size() ; ++n){
        //注意 : 2 -> 列向取得最大
        Mat m_Max(1,1,CV_32F,Scalar(-10000));
        Mat m_index(1,1,CV_32F);

        for(int j = 0 ; j < max_resp_row.at(n).cols ; ++j){
            if(m_Max.at<float>(0,0) < max_resp_row.at(n).at<float>(0,j)){
                m_Max.at<float>(0,0) = max_resp_row.at(n).at<float>(0,j);
                m_index.at<float>(0,0) = (float)j;
            }
        }
        init_max_response.at(n).push_back(m_Max);
        //cout<<init_max_response.at(n)<<endl;
        max_col.at(n).push_back(m_index);
        //cout<<max_col.at(n)<<endl;
    }
*/


//    max_row_perm = permute(max_row, [2 3 1]);
    Mat max_row_perm = Mat::zeros(max_row.at(0).cols,response.size(),CV_32F);
    for(int i = 0 ; i < max_row_perm.rows ; ++i){
        for(int j = 0 ; j < max_row_perm.cols ; ++j){
            max_row_perm.at<float>(i,j) = (float)max_row.at(j).at<float>(0,i);
        }
    }


//    col = max_col(:)';
    Mat col(1,max_col.size(),CV_32F);
    Mat row(1,col.cols,CV_32F);
    Mat trans_row(1,row.cols,CV_32F);
    Mat trans_col(1,col.cols,CV_32F);
    vector <Mat> init_pos_y(trans_row.cols);
    vector <Mat> max_pos_y(trans_row.cols);
    vector <Mat> init_pos_x(trans_col.cols);
    vector <Mat> max_pos_x(trans_col.cols);
    for(int i = 0 ; i < max_col.size() ; ++i){

//    col = max_col(:)';
        col.at<float>(0,i) = max_col.at(i).at<float>(0,0);


//    row = max_row_perm(sub2ind(size(max_row_perm), col, 1:size(response,3)));
        row.at<float>(0,i) = max_row_perm.at<float>(col.at<float>(0,i),i);


//    trans_row = mod(row - 1 + floor((use_sz(1)-1)/2), use_sz(1)) - floor((use_sz(1)-1)/2);
        float ans1;
        ans1 = mod(row.at<float>(0,i) + floor((use_sz[0]-1)/2.0),float(use_sz[0]));
        trans_row.at<float>(0,i) = ans1 - floor(float(use_sz[0]-1)/2.0);


//    trans_col = mod(col - 1 + floor((use_sz(2)-1)/2), use_sz(2)) - floor((use_sz(2)-1)/2);
        float ans2;
        ans2 = mod(col.at<float>(0,i) + floor((use_sz[1]-1)/2.0),float(use_sz[1]));
        trans_col.at<float>(0,i) = ans2 - floor(float(use_sz[1]-1)/2.0);


//    init_pos_y = permute(2*pi * trans_row / use_sz(1), [1 3 2]);
//    max_pos_y = init_pos_y;
        Mat temp1(1,1,CV_32F);
        temp1.at<float>(0,0) = 2.0 * M_PI * trans_row.at<float>(0,i) / use_sz[0];
        init_pos_y.at(i).push_back(temp1.clone());
        max_pos_y.at(i).push_back(temp1.clone());


//    init_pos_x = permute(2*pi * trans_col / use_sz(2), [1 3 2]);
//    max_pos_x = init_pos_x;
        Mat temp2(1,1,CV_32F);
        temp2.at<float>(0,0) = 2.0 * M_PI * trans_col.at<float>(0,i) / use_sz[1];
        init_pos_x.at(i).push_back(temp2.clone());
        max_pos_x.at(i).push_back(temp2.clone());
    }


//    % pre-compute complex exponential
//    exp_iky = exp(bsxfun(@times, 1i * ky, max_pos_y));
    //1i * ky
    Mat i_ky(1,ky.cols,CV_32FC2,Scalar(0));
    for(int i = 0 ; i < ky.cols ; ++i){
        i_ky.at<Vec2f>(0,i)[1] = ky.at<Vec2f>(0,i)[0];
    }


    //1i * kx
    Mat i_kx(kx.rows,1,CV_32FC2,Scalar(0));
    for(int i = 0 ; i < kx.rows ; ++i){
        i_kx.at<Vec2f>(i,0)[1] = kx.at<Vec2f>(i,0)[0];
    }

    vector <Mat> exp_bsxfun;
    vector <Mat> exp_iky;
    vector <Mat> exp_ikx;
    for(int n = 0 ; n < max_pos_y.size() ; ++n){
//    exp_iky = exp(bsxfun(@times, 1i * ky, max_pos_y));
        Mat exp_bsxfun1 = QT_M_mul_M(i_ky,max_pos_y.at(n));
        exp_iky.push_back(QT_M_exp(exp_bsxfun1));


//    exp_ikx = exp(bsxfun(@times, 1i * kx, max_pos_x));
        Mat exp_bsxfun2 = QT_M_mul_M(i_kx,max_pos_x.at(n));
        exp_ikx.push_back(QT_M_exp(exp_bsxfun2));
    }



//    % gradient_step_size = gradient_step_size / prod(use_sz);
//    ky2 = ky.*ky;
    Mat ky2;
    ky2 = ky.mul(ky);


//    kx2 = kx.*kx;
    Mat kx2;
    kx2 = kx.mul(kx);


//    iter = 1;
    int iter = 1;

    while(iter <= iterations){

//        % Compute gradient
//        ky_exp_ky = bsxfun(@times, ky, exp_iky);

        vector <Mat> ky_exp_ky;
        vector <Mat> kx_exp_kx;
        vector <Mat> y_resp;
        vector <Mat> resp_x;
        vector <Mat> grad_y;
        vector <Mat> grad_x;
        vector <Mat> ival;
        vector <Mat> H_yy;
        vector <Mat> H_xx;
        vector <Mat> H_xy;
        vector <Mat> det_H;
        for(int n = 0 ; n < exp_iky.size() ; ++n){
//        ky_exp_ky = bsxfun(@times, ky, exp_iky);
            Mat bsx_time1 = QT_M_mul_M(ky,exp_iky.at(n));
            ky_exp_ky.push_back(bsx_time1);


//        kx_exp_kx = bsxfun(@times, kx, exp_ikx);
            Mat bsx_time2 = QT_M_mul_M(kx,exp_ikx.at(n));
            kx_exp_kx.push_back(bsx_time2);



//        %exp_iky
//        %responsef
//        %fk = ndims(exp_iky)
//        %fu = ndims(responsef)
//        %se = size(exp_iky)
//        %sr = size(responsef)

//        y_resp = mtimesx(exp_iky, responsef, 'speed');
            y_resp.push_back(QT_M_mtimesx(exp_iky.at(n),responsef.at(n)));


//        resp_x = mtimesx(responsef, exp_ikx, 'speed');
            resp_x.push_back(QT_M_mtimesx(responsef.at(n),exp_ikx.at(n)));


//        grad_y = -imag(mtimesx(ky_exp_ky, resp_x, 'speed'));
            Mat grad_y_temp = QT_M_mtimesx(ky_exp_ky.at(n),resp_x.at(n));
            Mat temp_y(1,1,CV_32F);
            temp_y.at<float>(0,0) = (-1) * grad_y_temp.at<Vec2f>(0,0)[1];
            grad_y.push_back(temp_y.clone());


//        grad_x = -imag(mtimesx(y_resp, kx_exp_kx, 'speed'));
            Mat grad_x_temp = QT_M_mtimesx(y_resp.at(n),kx_exp_kx.at(n));
            Mat temp_x(1,1,CV_32F);
            temp_x.at<float>(0,0) = (-1) * grad_x_temp.at<Vec2f>(0,0)[1];
            grad_x.push_back(temp_x.clone());


//        ival = 1i * mtimesx(exp_iky, resp_x, 'speed');
            ival.push_back(QT_M_mtimesx(exp_iky.at(n),resp_x.at(n)));
            float temp_ival = ival.at(n).at<Vec2f>(0,0)[0];
            ival.at(n).at<Vec2f>(0,0)[0] = ival.at(n).at<Vec2f>(0,0)[1] * (-1);
            ival.at(n).at<Vec2f>(0,0)[1] = temp_ival;


//        H_yy = real(-mtimesx(bsxfun(@times, ky2, exp_iky), resp_x, 'speed') + ival);
            Mat bsx_times3 = QT_M_mul_M(ky2,exp_iky.at(n));
            Mat H_yy_temp = QT_M_mtimesx(bsx_times3,resp_x.at(n));
            Mat temp_yy;
            add((-1)*H_yy_temp,ival.at(n),temp_yy);
            Mat real_yy(H_yy_temp.rows,H_yy_temp.cols,CV_32F);
            real_yy.at<float>(0,0) = temp_yy.at<Vec2f>(0,0)[0];
            H_yy.push_back(real_yy.clone());


//        H_xx = real(-mtimesx(y_resp, bsxfun(@times, kx2, exp_ikx), 'speed') + ival);
            Mat bsx_times4 = QT_M_mul_M(kx2,exp_ikx.at(n));
            Mat H_xx_temp = QT_M_mtimesx(y_resp.at(n),bsx_times4);
            Mat temp_xx;
            add((-1)*H_xx_temp,ival.at(n),temp_xx);
            Mat real_xx(H_xx_temp.rows,H_xx_temp.cols,CV_32F);
            real_xx.at<float>(0,0) = temp_xx.at<Vec2f>(0,0)[0];
            H_xx.push_back(real_xx.clone());


//        H_xy = real(-mtimesx(ky_exp_ky, mtimesx(responsef, kx_exp_kx, 'speed'), 'speed'));
            Mat H_xy_temp1,H_xy_temp2;
            H_xy_temp1 = QT_M_mtimesx(responsef.at(n),kx_exp_kx.at(n));
            H_xy_temp2 = QT_M_mtimesx(ky_exp_ky.at(n),H_xy_temp1);
            Mat real_xy(H_xy_temp2.rows,H_xy_temp2.cols,CV_32F);
            real_xy.at<float>(0,0) = H_xy_temp2.at<Vec2f>(0,0)[0] * (-1);
            H_xy.push_back(real_xy.clone());


//        det_H = H_yy .* H_xx - H_xy .* H_xy;
            det_H.push_back((H_yy.at(n).mul(H_xx.at(n)) - (H_xy.at(n).mul(H_xy.at(n)))));


//        % Compute new position using newtons method
//        max_pos_y = max_pos_y - (H_xx .* grad_y - H_xy .* grad_x) ./ det_H;
            Mat max_pos_y_temp = max_pos_y.at(n) - (H_xx.at(n).mul(grad_y.at(n)) - (H_xy.at(n).mul(grad_x.at(n))));
            Mat max_pos_y_div;
            divide(max_pos_y_temp,det_H.at(n),max_pos_y_div);
            max_pos_y.at(n) = max_pos_y_div.clone();


//        max_pos_x = max_pos_x - (H_yy .* grad_x - H_xy .* grad_y) ./ det_H;
            Mat max_pos_x_temp = max_pos_x.at(n) - (H_yy.at(n).mul(grad_x.at(n)) - (H_xy.at(n).mul(grad_y.at(n))));
            Mat max_pos_x_div;
            divide(max_pos_x_temp,det_H.at(n),max_pos_x_div);
            max_pos_x.at(n) = max_pos_x_div.clone();


//        % Evaluate maximum
//        exp_iky = exp(bsxfun(@times, 1i * ky, max_pos_y));
            Mat bsx_times5 = QT_M_mul_M(i_ky,max_pos_y.at(n));
            exp_iky.at(n) = QT_M_exp(bsx_times5);


//        exp_ikx = exp(bsxfun(@times, 1i * kx, max_pos_x));
            Mat bsx_times6 = QT_M_mul_M(i_kx,max_pos_x.at(n));
            exp_ikx.at(n) = QT_M_exp(bsx_times6);

        }


//        iter = iter + 1;
        ++iter;
     }


//    max_response = 1 / prod(use_sz) * real(mtimesx(mtimesx(exp_iky, responsef, 'speed'), exp_ikx, 'speed'));
    vector <Mat> max_response;
    for(int n = 0 ; n < responsef.size() ; ++n){
//        vector <Mat> mtimesx_temp1;
//        mtimesx_temp1 = QT_mtimesx(exp_iky,responsef);
//        vector <Mat> mtimesx_temp2;
//        mtimesx_temp2 = QT_mtimesx(mtimesx_temp1,exp_ikx);

        Mat mtimesx_temp1;
        mtimesx_temp1 = QT_M_mtimesx(exp_iky.at(n),responsef.at(n));
        Mat mtimesx_temp2;
        mtimesx_temp2 = QT_M_mtimesx(mtimesx_temp1,exp_ikx.at(n));

        Mat output(mtimesx_temp2.rows,mtimesx_temp2.cols,CV_32F);
        output.at<float>(0,0) = 1 / (use_sz[0] * use_sz[1]) * mtimesx_temp2.at<Vec2f>(0,0)[0];
        max_response.push_back(output.clone());
        //cout<<max_response.at(n)<<endl;
    }



//    % check for scales that have not increased in score
//    ind = max_response < init_max_response;
    vector <bool> ind(max_response.size(),false);
    for(int n = 0 ; n < ind.size() ; ++n){
        if(max_response.at(n).at<float>(0,0) < init_max_response.at(n).at<float>(0,0)){
            ind.at(n) = true;
        }
    }


    for(int n = 0 ; n < ind.size() ; ++n){
        if(ind.at(n)){
//    max_response(ind) = init_max_response(ind);
            max_response.at(n) = init_max_response.at(n).clone();

//    max_pos_y(ind) = init_pos_y(ind);
            max_pos_y.at(n) = init_pos_y.at(n).clone();

//    max_pos_x(ind) = init_pos_x(ind);
            max_pos_x.at(n) = init_pos_x.at(n).clone();
        }
    }


//    [max_scale_response, sind] = max(max_response(:));
    float max_scale_response = -10000;
    for(int n = 0 ; n < max_response.size() ; ++n){
        if(max_scale_response < max_response.at(n).at<float>(0,0)){
            max_scale_response = max_response.at(n).at<float>(0,0);
            sind = n;
        }
    }


//    disp_row = (mod(max_pos_y(1,1,sind) + pi, 2*pi) - pi) / (2*pi) * use_sz(1);
    disp_row = (mod(max_pos_y.at(sind).at<float>(0,0) + M_PI , 2 * M_PI) - M_PI) / (2 * M_PI) * use_sz[0];


//    disp_col = (mod(max_pos_x(1,1,sind) + pi, 2*pi) - pi) / (2*pi) * use_sz(2);
    disp_col = (mod(max_pos_x.at(sind).at<float>(0,0) + M_PI , 2 * M_PI) - M_PI) / (2 * M_PI) * use_sz[1];

    //END = clock();
    //cout<<"strat = "<<START<<",end = "<<END<<endl;
    //cout  << "executing time : " << (END - START) / CLOCKS_PER_SEC << "s" << endl;

    //imshow("im",response[0]);
    //waitKey(0);

}

vector <Mat> QT_mtimesx(vector <Mat> &Vec_Src1 , vector <Mat> &Vec_Src2){
    int row = Vec_Src1.at(0).rows;
    int col = Vec_Src2.at(0).cols;
    int same_length = Vec_Src1.at(0).cols;
    int Num_dim = Vec_Src1.size();

    //double START,END;
    //START = clock();

    vector <Mat> mul_ans;
    for(int n = 0 ; n < Num_dim ; ++n){
        vector <Mat> src1;
        vector <Mat> src2;
        vector <Mat> mul_result(2);

        split(Vec_Src1.at(n),src1);
        split(Vec_Src2.at(n),src2);

        mul_result.at(0) = (src1.at(0) * src2.at(0)) - (src1.at(1) * src2.at(1));
        mul_result.at(1) = (src1.at(0) * src2.at(1)) + (src1.at(1) * src2.at(0));

        Mat result;
        merge(mul_result,result);

        mul_ans.push_back(result.clone());
    }

    //END = clock();
    //cout<<"strat = "<<START<<",end = "<<END<<endl;
    //cout  << "executing time : " << (END - START) / CLOCKS_PER_SEC << "s" << endl;


    return mul_ans;
}

Mat QT_M_mtimesx(Mat &M_Src1 ,Mat &M_Src2){
    vector <Mat> src1;
    vector <Mat> src2;
    vector <Mat> mul_result(2);

    split(M_Src1,src1);
    split(M_Src2,src2);

    mul_result.at(0) = (src1.at(0) * src2.at(0)) - (src1.at(1) * src2.at(1));
    mul_result.at(1) = (src1.at(0) * src2.at(1)) + (src1.at(1) * src2.at(0));

    Mat result;
    merge(mul_result,result);

    return result;
}

vector <Mat> QT_bsxfun(Mat &Vec_Src1 , vector <Mat> &Vec_Src2){
    int row = Vec_Src1.rows;
    int col = Vec_Src1.cols;
    int Num_dim = Vec_Src2.size();

    //Vec_Src2是否只有一個元素
    bool one_element = false;
    if(Vec_Src2.at(0).rows == 1 && Vec_Src2.at(0).cols == 1){
        one_element = true;
    }

    bool two_channel = false;
    if(Vec_Src1.type() >= 8){
        two_channel = true;
    }
//cout<<"row = "<<row<<" col = "<<col<<" Num_dim = "<<Num_dim<<endl;

    //double START,END;
    //START = clock();

    vector <Mat> bsx_ans;
    vector <Mat> src1;
    split(Vec_Src1,src1);

    if(one_element){
        for(int n = 0 ; n < Num_dim ; ++n){
            vector <Mat> bsx_result(2);
            vector <Mat> src2;
            split(Vec_Src2.at(n),src2);

            //Vec_Src2 && Vec_Src1 -> 2 channels
            if(Vec_Src2.at(n).type() >= 8 && two_channel){
                bsx_result.at(0) = (src1.at(0).mul(src2.at(0).at<float>(0,0))) - (src1.at(1).mul(src2.at(1).at<float>(0,0)));
                bsx_result.at(1) = (src1.at(0).mul(src2.at(1).at<float>(0,0))) + (src1.at(1).mul(src2.at(0).at<float>(0,0)));
            }
            //Vec_Src2 -> 1 channel , Vec_Src1 -> 2 channels
            else if(Vec_Src2.at(n).type() < 8 && two_channel){
                bsx_result.at(0) = src1.at(0).mul(src2.at(0).at<float>(0,0));
                bsx_result.at(1) = src1.at(1).mul(src2.at(0).at<float>(0,0));
            }
            //Vec_Src2 -> 2 channels , Vec_Src1 -> 1 channel
            else if(Vec_Src2.at(n).type() >= 8 && !two_channel){
                bsx_result.at(0) = src1.at(0).mul(src2.at(0).at<float>(0,0));
                bsx_result.at(1) = src1.at(0).mul(src2.at(1).at<float>(0,0));
            }
            //Vec_Src2 && Vec_Src1 -> 1 channels
            else{
                bsx_result.at(0) = src1.at(0).mul(src2.at(0).at<float>(0,0));
                bsx_result.at(1) = src1.at(0).mul(0);
            }

            Mat result;
            merge(bsx_result,result);

            bsx_ans.push_back(result.clone());
        }
    }
    else{
        for(int n = 0 ; n < Num_dim ; ++n){
            vector <Mat> bsx_result(2);
            vector <Mat> src2;
            split(Vec_Src2.at(n),src2);

            //Vec_Src2 && Vec_Src1 -> 2 channels
            if(Vec_Src2.at(n).type() >= 8 && two_channel){
                bsx_result.at(0) = (src1.at(0).mul(src2.at(0))) - (src1.at(1).mul(src2.at(1)));
                bsx_result.at(1) = (src1.at(0).mul(src2.at(1))) + (src1.at(1).mul(src2.at(0)));
            }
            //Vec_Src2 -> 1 channel , Vec_Src1 -> 2 channels
            else if(Vec_Src2.at(n).type() < 8 && two_channel){
                bsx_result.at(0) = src1.at(0).mul(src2.at(0));
                bsx_result.at(1) = src1.at(1).mul(src2.at(0));
            }
            //Vec_Src2 -> 2 channels , Vec_Src1 -> 1 channel
            else if(Vec_Src2.at(n).type() >= 8 && !two_channel){
                bsx_result.at(0) = src1.at(0).mul(src2.at(0));
                bsx_result.at(1) = src1.at(0).mul(src2.at(1));
            }
            //Vec_Src2 && Vec_Src1 -> 1 channels
            else{
                bsx_result.at(0) = src1.at(0).mul(src2.at(0));
                bsx_result.at(1) = src1.at(0).mul(0);
            }


            Mat result;
            merge(bsx_result,result);

            bsx_ans.push_back(result.clone());

        }
    }

    //END = clock();
    //cout<<"strat = "<<START<<",end = "<<END<<endl;
    //cout  << "executing time : " << (END - START) / CLOCKS_PER_SEC << "s" << endl;

    return bsx_ans;
}

vector <Mat> QT_exp(vector <Mat> &Vec_Src){
    int row = Vec_Src.at(0).rows;
    int col = Vec_Src.at(0).cols;
    int Num_dim = Vec_Src.size();

    vector <Mat> exp_ans;
    for(int n = 0 ; n < Num_dim ; ++n){
        vector <Mat> src;

        split(Vec_Src.at(n),src);

        Mat mat_ans(row,col,CV_32FC2);

        Mat exp_real;
        exp(src.at(0),exp_real);
        //cout<<"exp_real.type() = "<<exp_real.type()<<endl;
        for(int i = 0 ; i < row ; ++i){
            for(int j = 0 ; j < col ; ++j){
                mat_ans.at<Vec2f>(i,j)[0] = exp_real.at<float>(i,j)*cos(src.at(1).at<float>(i,j));
                mat_ans.at<Vec2f>(i,j)[1] = exp_real.at<float>(i,j)*sin(src.at(1).at<float>(i,j));
            }
        }

        exp_ans.push_back(mat_ans.clone());

    }
    return exp_ans;
}

Mat QT_M_exp(Mat &M_Src){
    int row = M_Src.rows;
    int col = M_Src.cols;

    vector <Mat> src;

    split(M_Src,src);

    Mat mat_ans(row,col,CV_32FC2);

    Mat exp_real;
    exp(src.at(0),exp_real);
    for(int i = 0 ; i < row ; ++i){
        for(int j = 0 ; j < col ; ++j){
            mat_ans.at<Vec2f>(i,j)[0] = exp_real.at<float>(i,j)*cos(src.at(1).at<float>(i,j));
            mat_ans.at<Vec2f>(i,j)[1] = exp_real.at<float>(i,j)*sin(src.at(1).at<float>(i,j));
        }
    }
    return mat_ans;

}

float mod(float div1 , float div2){
    float c,ans;
    c = floor(div1/div2);
    ans = div1 - c*div2;
    if(div2>0){
        if(ans < 0){
            ans += div2;
        }
    }
    else{
        if(ans > 0){
            ans -= div2;
        }
    }
    return ans;
}

