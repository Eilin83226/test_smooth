#include "resp_newton.h"
#include "bacf_optimized.h"

void resp_newton(vector <Mat> &response,vector <Mat> &responsef,double iterations,Mat &ky,Mat &kx,double use_sz[],float &disp_row,float &disp_col,int &sind){
//cout<<"response = "<<response.size()<<","<<response[0].size()<<","<<response[0].type()<<endl;
//cout<<response.at(0)<<endl;


    //double START,END;
    //START = clock();

    vector <Mat> max_resp_row(response.size());
    vector <Mat> max_row(response.size());

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
    }


//    [init_max_response, max_col] = max(max_resp_row, [], 2);
    vector <Mat> init_max_response(response.size());
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



//    max_row_perm = permute(max_row, [2 3 1]);
    Mat max_row_perm = Mat::zeros(max_row.at(0).cols,response.size(),CV_32F);
    //cout<<"max_row_perm = ";
    for(int i = 0 ; i < max_row_perm.rows ; ++i){
        for(int j = 0 ; j < max_row_perm.cols ; ++j){
            max_row_perm.at<float>(i,j) = (float)max_row.at(j).at<float>(0,i);
        }
    }
    //cout<<max_row_perm<<endl;


//    col = max_col(:)';
    Mat col(1,max_col.size(),CV_32F);
    for(int i = 0 ; i < max_col.size() ; ++i){
        col.at<float>(0,i) = max_col.at(i).at<float>(0,0);
    }
    //cout<<col<<endl;


//    row = max_row_perm(sub2ind(size(max_row_perm), col, 1:size(response,3)));
    Mat row(1,col.cols,CV_32F);
    for(int i = 0 ; i < col.cols ; ++i){
        row.at<float>(0,i) = max_row_perm.at<float>(col.at<float>(0,i),i);
        //cout<<row[i]<<" ";
    }
    //cout<<row<<endl;


//    trans_row = mod(row - 1 + floor((use_sz(1)-1)/2), use_sz(1)) - floor((use_sz(1)-1)/2);
    Mat trans_row(1,row.cols,CV_32F);
    for(int i = 0 ; i < trans_row.cols ; ++i){
        float ans;
        ans = mod(row.at<float>(0,i) + floor((use_sz[0]-1)/2.0),float(use_sz[0]));
        trans_row.at<float>(0,i) = ans - floor(float(use_sz[0]-1)/2.0);
    }
    //cout<<trans_row<<endl;


//    trans_col = mod(col - 1 + floor((use_sz(2)-1)/2), use_sz(2)) - floor((use_sz(2)-1)/2);
    Mat trans_col(1,col.cols,CV_32F);
    for(int i = 0 ; i < trans_col.cols ; ++i){
        float ans;
        ans = mod(col.at<float>(0,i) + floor((use_sz[1]-1)/2.0),float(use_sz[1]));
        trans_col.at<float>(0,i) = ans - floor(float(use_sz[1]-1)/2.0);
    }
    //cout<<trans_col<<endl;


//    init_pos_y = permute(2*pi * trans_row / use_sz(1), [1 3 2]);
//    max_pos_y = init_pos_y;
    vector <Mat> init_pos_y(trans_row.cols);
    vector <Mat> max_pos_y(trans_row.cols);
    for(int i = 0 ; i < trans_row.cols ; ++i){
        Mat temp(1,1,CV_32F);
        temp.at<float>(0,0) = 2.0 * M_PI * trans_row.at<float>(0,i) / use_sz[0];
        init_pos_y.at(i).push_back(temp.clone());
        max_pos_y.at(i).push_back(temp.clone());
    }



//    init_pos_x = permute(2*pi * trans_col / use_sz(2), [1 3 2]);
//    max_pos_x = init_pos_x;
    vector <Mat> init_pos_x(trans_col.cols);
    vector <Mat> max_pos_x(trans_col.cols);
    for(int i = 0 ; i < trans_row.cols ; ++i){
        Mat temp(1,1,CV_32F);
        temp.at<float>(0,0) = 2.0 * M_PI * trans_col.at<float>(0,i) / use_sz[1];
        init_pos_x.at(i).push_back(temp.clone());
        max_pos_x.at(i).push_back(temp.clone());
        //cout<<init_pos_x.at(i)<<endl;
    }


//    % pre-compute complex exponential
//    exp_iky = exp(bsxfun(@times, 1i * ky, max_pos_y));
    Mat i_ky(1,ky.cols,CV_32FC2,Scalar(0));
    for(int i = 0 ; i < ky.cols ; ++i){
        i_ky.at<Vec2f>(0,i)[1] = ky.at<Vec2f>(0,i)[0];
    }

    vector <Mat> exp_bsxfun = QT_bsxfun(i_ky,max_pos_y);
    vector <Mat> exp_iky = QT_exp(exp_bsxfun);
    //vector <Mat> exp_iky = exp_bsx(i_ky,max_pos_y);
    /*for(int n = 0 ; n < exp_iky.size() ; ++n){
        cout<<exp_iky.at(n)<<endl;
    }*/


//    exp_ikx = exp(bsxfun(@times, 1i * kx, max_pos_x));
    Mat i_kx(kx.rows,1,CV_32FC2,Scalar(0));
    for(int i = 0 ; i < kx.rows ; ++i){
        i_kx.at<Vec2f>(i,0)[1] = kx.at<Vec2f>(i,0)[0];
    }

    exp_bsxfun.clear();
    exp_bsxfun = QT_bsxfun(i_kx,max_pos_x);
    vector <Mat> exp_ikx = QT_exp(exp_bsxfun);
    //vector <Mat> exp_ikx = exp_bsx(i_kx,max_pos_x);
    /*for(int n = 0 ; n < exp_ikx.size() ; ++n){
        cout<<exp_ikx.at(n)<<endl;
    }*/



//    % gradient_step_size = gradient_step_size / prod(use_sz);
//    ky2 = ky.*ky;
    Mat ky2;//(1,ky.size(),CV_32F);
    ky2 = ky.mul(ky);
    /*for(int j = 0 ; j < ky.size() ; ++j){
        ky2.at<float>(0,j) = (float)ky.at(j) * (float)ky.at(j);
    }*/

//    kx2 = kx.*kx;
    Mat kx2;//(kx.size(),1,CV_32F);
    kx2 = kx.mul(kx);
    /*for(int i = 0 ; i < kx.size() ; ++i){
        kx2.at<float>(i,0) = (float)kx.at(i) * (float)kx.at(i);
    }*/

    double start = clock();

//    iter = 1;
    int iter = 1;
//    while iter <= iterations
    while(iter <= iterations){

//        % Compute gradient
//        ky_exp_ky = bsxfun(@times, ky, exp_iky);

        vector <Mat> ky_exp_ky;
        ky_exp_ky = QT_bsxfun(ky,exp_iky);
        /*for(int n = 0 ; n < ky_exp_ky.size() ; ++n){
            cout<<ky_exp_ky.at(n)<<endl;
        }*/


//        kx_exp_kx = bsxfun(@times, kx, exp_ikx);
        vector <Mat> kx_exp_kx;
        kx_exp_kx = QT_bsxfun(kx,exp_ikx);
        /*for(int n = 0 ; n < kx_exp_kx.size() ; ++n){
            cout<<kx_exp_kx.at(n)<<endl;
        }*/


//        %exp_iky
//        %responsef
//        %fk = ndims(exp_iky)
//        %fu = ndims(responsef)
//        %se = size(exp_iky)
//        %sr = size(responsef)
//        y_resp = mtimesx(exp_iky, responsef, 'speed');
        vector <Mat> y_resp;
        y_resp = QT_mtimesx(exp_iky,responsef);
        /*for(int n = 0 ; n < y_resp.size() ; ++n){
            cout<<y_resp.at(n)<<endl;
            cout<<"exp_iky_size = "<<y_resp.at(n).size()<<endl;
        }*/


//        resp_x = mtimesx(responsef, exp_ikx, 'speed');
        vector <Mat> resp_x;
        resp_x = QT_mtimesx(responsef,exp_ikx);
        /*for(int n = 0 ; n < resp_x.size() ; ++n){
            cout<<resp_x.at(n)<<endl;
        }*/


//        grad_y = -imag(mtimesx(ky_exp_ky, resp_x, 'speed'));
        vector <Mat> grad_y_temp;
        grad_y_temp = QT_mtimesx(ky_exp_ky,resp_x);
        /*for(int n = 0 ; n < grad_y_temp.size() ; ++n){
            cout<<grad_y_temp.at(n)<<endl;
        }*/

        vector <Mat> grad_y;
        for(int n = 0 ; n < grad_y_temp.size() ; ++n){
            Mat temp(1,1,CV_32F);
            temp.at<float>(0,0) = (-1) * grad_y_temp.at(n).at<Vec2f>(0,0)[1];
            grad_y.push_back(temp);
            //cout<<grad_y.at(n)<<endl;
        }


//        grad_x = -imag(mtimesx(y_resp, kx_exp_kx, 'speed'));
        vector <Mat> grad_x_temp;
        grad_x_temp = QT_mtimesx(y_resp,kx_exp_kx);
        /*for(int n = 0 ; n < grad_y_temp.size() ; ++n){
            cout<<grad_x_temp.at(n)<<endl;
        }*/

        vector <Mat> grad_x;
        for(int n = 0 ; n < grad_x_temp.size() ; ++n){
            Mat temp(1,1,CV_32F);
            temp.at<float>(0,0) = (-1) * grad_x_temp.at(n).at<Vec2f>(0,0)[1];
            grad_x.push_back(temp);
            //cout<<grad_x.at(n)<<endl;
        }

//        ival = 1i * mtimesx(exp_iky, resp_x, 'speed');
        vector <Mat> ival;
        ival = QT_mtimesx(exp_iky,resp_x);
        for(int n = 0 ; n < ival.size() ; ++n){
            //cout<<"before = "<<ival.at(n)<<endl;
            float temp = ival.at(n).at<Vec2f>(0,0)[0];
            ival.at(n).at<Vec2f>(0,0)[0] = ival.at(n).at<Vec2f>(0,0)[1] * (-1);
            ival.at(n).at<Vec2f>(0,0)[1] = temp;
            //cout<<"after = "<<ival.at(n)<<endl;
        }



//        H_yy = real(-mtimesx(bsxfun(@times, ky2, exp_iky), resp_x, 'speed') + ival);
        vector <Mat> bsxfun_times;
        bsxfun_times.clear();
        bsxfun_times = QT_bsxfun(ky2,exp_iky);
        /*for(int n = 0 ; n < bsxfun_times.size() ; ++n){
            cout<<bsxfun_times.at(n)<<endl;
        }*/


        vector <Mat> H_yy_temp;
        H_yy_temp = QT_mtimesx(bsxfun_times,resp_x);
        vector <Mat> H_yy;
        for(int n = 0 ; n < H_yy_temp.size() ; ++n){
            Mat temp;
            add((-1)*H_yy_temp.at(n),ival.at(n),temp);
            Mat real(H_yy_temp.at(n).rows,H_yy_temp.at(n).cols,CV_32F);
            real.at<float>(0,0) = temp.at<Vec2f>(0,0)[0];
            H_yy.push_back(real.clone());
            //cout<<H_yy.at(n)<<endl;
        }


//        H_xx = real(-mtimesx(y_resp, bsxfun(@times, kx2, exp_ikx), 'speed') + ival);
        bsxfun_times.clear();
        bsxfun_times = QT_bsxfun(kx2,exp_ikx);
        /*for(int n = 0 ; n < bsxfun_times.size() ; ++n){
            cout<<bsxfun_times.at(n)<<endl;
        }*/


        vector <Mat> H_xx_temp;
        H_xx_temp = QT_mtimesx(y_resp,bsxfun_times);
        vector <Mat> H_xx;
        for(int n = 0 ; n < H_xx_temp.size() ; ++n){
            Mat temp;
            add((-1)*H_xx_temp.at(n),ival.at(n),temp);
            Mat real(H_xx_temp.at(n).rows,H_xx_temp.at(n).cols,CV_32F);
            real.at<float>(0,0) = temp.at<Vec2f>(0,0)[0];
            H_xx.push_back(real.clone());
            //cout<<H_xx.at(n)<<endl;
        }


//        H_xy = real(-mtimesx(ky_exp_ky, mtimesx(responsef, kx_exp_kx, 'speed'), 'speed'));
        vector <Mat> H_xy_temp1,H_xy_temp2;
        H_xy_temp1 = QT_mtimesx(responsef,kx_exp_kx);
        /*for(int n = 0 ; n < H_xy_temp1.size() ; ++n){
            cout<<H_xy_temp1.at(n)<<endl;
        }*/
        H_xy_temp2 = QT_mtimesx(ky_exp_ky,H_xy_temp1);
        /*for(int n = 0 ; n < H_xy_temp2.size() ; ++n){
            cout<<H_xy_temp2.at(n)<<endl;
        }*/
        vector <Mat> H_xy;
        for(int n = 0 ; n < H_xy_temp2.size() ; ++n){
            Mat real(H_xy_temp2.at(n).rows,H_xy_temp2.at(n).cols,CV_32F);
            real.at<float>(0,0) = H_xy_temp2.at(n).at<Vec2f>(0,0)[0] * (-1);
            H_xy.push_back(real.clone());
            //cout<<H_xy.at(n)<<endl;
        }


//        det_H = H_yy .* H_xx - H_xy .* H_xy;
        vector <Mat> det_H;
        for(int n = 0 ; n < H_yy.size() ; ++n){
            Mat a;
            a = H_yy.at(n).mul(H_xx.at(n));
            Mat b;
            b = H_xy.at(n).mul(H_xy.at(n));
            Mat output;
            addWeighted(a,1,b,-1,0,output);
            subtract(a,b,output);
            det_H.push_back(output.clone());
            //cout<<"d = "<<det_H.at(n)<<endl;
        }



//        % Compute new position using newtons method
//        max_pos_y = max_pos_y - (H_xx .* grad_y - H_xy .* grad_x) ./ det_H;
        for(int n = 0 ; n < max_pos_y.size() ; ++n){
            Mat a;
            a = H_xx.at(n).mul(grad_y.at(n));
            Mat b;
            b = H_xy.at(n).mul(grad_x.at(n));
            Mat c;
            subtract(a,b,c);

            Mat d;
            subtract(max_pos_y.at(n),c,d);

            Mat output;
            divide(d,det_H.at(n),output);
            max_pos_y.at(n) = output.clone();
            //cout<<max_pos_y.at(n)<<endl;
        }



//        max_pos_x = max_pos_x - (H_yy .* grad_x - H_xy .* grad_y) ./ det_H;
        for(int n = 0 ; n < max_pos_x.size() ; ++n){
            Mat a;
            a = H_yy.at(n).mul(grad_x.at(n));
            Mat b;
            b = H_xy.at(n).mul(grad_y.at(n));
            Mat c;
            subtract(a,b,c);

            Mat d;
            subtract(max_pos_x.at(n),c,d);

            Mat output;
            divide(d,det_H.at(n),output);
            max_pos_x.at(n) = output.clone();
            //cout<<max_pos_x.at(n)<<endl;
        }

//        % Evaluate maximum
//        exp_iky = exp(bsxfun(@times, 1i * ky, max_pos_y));
        exp_iky.clear();
        Mat i_ky(1,ky.cols,CV_32FC2,Scalar(0));
        for(int i = 0 ; i < ky.cols ; ++i){
            i_ky.at<Vec2f>(0,i)[1] = ky.at<Vec2f>(0,i)[0];
        }

        exp_bsxfun.clear();
        exp_bsxfun = QT_bsxfun(i_ky,max_pos_y);
        exp_iky = QT_exp(exp_bsxfun);
        /*for(int n = 0 ; n < exp_bsxfun.size() ; ++n){
            cout<<exp_bsxfun.at(n)<<endl;
        }*/


//        exp_ikx = exp(bsxfun(@times, 1i * kx, max_pos_x));
        exp_ikx.clear();
        Mat i_kx(kx.rows,1,CV_32FC2,Scalar(0));
        for(int i = 0 ; i < kx.rows ; ++i){
            i_kx.at<Vec2f>(i,0)[1] = kx.at<Vec2f>(i,0)[0];
        }

        exp_bsxfun.clear();
        exp_bsxfun = QT_bsxfun(i_kx,max_pos_x);
        exp_ikx = QT_exp(exp_bsxfun);
        //exp_ikx = exp_bsx(i_kx,max_pos_x);
        /*for(int n = 0 ; n < exp_ikx.size() ; ++n){
            cout<<exp_ikx.at(n)<<endl;
        }*/


//        iter = iter + 1;
        ++iter;
     }

    double end = clock();
    cout<<"time = "<<(end - start)/1000<<endl;

//    max_response = 1 / prod(use_sz) * real(mtimesx(mtimesx(exp_iky, responsef, 'speed'), exp_ikx, 'speed'));
    vector <Mat> max_response;
    for(int n = 0 ; n < responsef.size() ; ++n){
        vector <Mat> mtimesx_temp1;
        mtimesx_temp1 = QT_mtimesx(exp_iky,responsef);
        vector <Mat> mtimesx_temp2;
        mtimesx_temp2 = QT_mtimesx(mtimesx_temp1,exp_ikx);

        Mat output(mtimesx_temp2.at(n).rows,mtimesx_temp2.at(n).cols,CV_32F);
        output.at<float>(0,0) = 1 / (use_sz[0] * use_sz[1]) * mtimesx_temp2.at(n).at<Vec2f>(0,0)[0];
        max_response.push_back(output.clone());
        //cout<<max_response.at(n)<<endl;
    }



//    % check for scales that have not increased in score
//    ind = max_response < init_max_response;
    vector <bool> ind(max_response.size(),false);
    for(int n = 0 ; n < ind.size() ; ++n){
        //cout<<max_response.at(n).at<float>(0,0)<<","<<init_max_response.at(n).at<float>(0,0)<<endl;
        if(max_response.at(n).at<float>(0,0) < init_max_response.at(n).at<float>(0,0)){
            ind.at(n) = true;
        }
        //cout<<ind.at(n)<<endl;
    }


    for(int n = 0 ; n < ind.size() ; ++n){
        if(ind.at(n)){
//    max_response(ind) = init_max_response(ind);
            //cout<<"max_response["<<n<<"] = "<<max_response.at(n)<<",init_max_response["<<n<<"] = "<<init_max_response.at(n)<<endl;
            max_response.at(n) = init_max_response.at(n).clone();
//    max_pos_y(ind) = init_pos_y(ind);
            //cout<<"max_pos_y["<<n<<"] = "<<max_pos_y.at(n)<<",init_pos_y["<<n<<"] = "<<init_pos_y.at(n)<<endl;
            max_pos_y.at(n) = init_pos_y.at(n).clone();
//    max_pos_x(ind) = init_pos_x(ind);
            //cout<<"max_pos_x["<<n<<"] = "<<max_pos_x.at(n)<<",init_pos_x["<<n<<"] = "<<init_pos_x.at(n)<<endl;
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
    //cout<<"max_scale_response = "<<max_scale_response<<",sind = "<<sind<<endl;
//    disp_row = (mod(max_pos_y(1,1,sind) + pi, 2*pi) - pi) / (2*pi) * use_sz(1);
    disp_row = (mod(max_pos_y.at(sind).at<float>(0,0) + M_PI , 2 * M_PI) - M_PI) / (2 * M_PI) * use_sz[0];
    //cout<<"disp_row = "<<disp_row<<endl;
//    disp_col = (mod(max_pos_x(1,1,sind) + pi, 2*pi) - pi) / (2*pi) * use_sz(2);
    disp_col = (mod(max_pos_x.at(sind).at<float>(0,0) + M_PI , 2 * M_PI) - M_PI) / (2 * M_PI) * use_sz[1];
    //cout<<"disp_col = "<<disp_col<<endl;


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

