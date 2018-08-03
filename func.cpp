#include "func.h"

Mat BGR2RGB(Mat &im){
    vector <Mat> src;

    split(im,src);

    vector <Mat> result(3);
    result.at(0) = src.at(2);
    result.at(1) = src.at(1);
    result.at(2) = src.at(0);

    Mat img;
    merge(result,img);

    return img;
}

Mat RGB2BGR(Mat &im){
    vector <Mat> src;

    split(im,src);

    vector <Mat> result(3);
    result.at(0) = src.at(2);
    result.at(1) = src.at(1);
    result.at(2) = src.at(0);

    Mat img;
    merge(result,img);

    return img;
}


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



//template<typename ty>
//void circshift(ty &out, const ty &in, int xdim, int ydim, int xshift, int yshift)
//{
//    for (int i =0; i < xdim; i++) {
//        int ii = (i + xshift) % xdim;
//        if (ii<0) ii = xdim + ii;
//        for (int j = 0; j < ydim; j++) {
//            int jj = (j + yshift) % ydim;
//            if (jj<0) jj = ydim + jj;
//            out[ii * ydim + jj] = in[i * ydim + j];
//        }
//    }
//}


////快速傅立葉轉換
//void fft2(const Mat &inputImg, Mat &Fourier)
//{
//    int mat_type = inputImg.type();
//    assert(mat_type<15); //不支持的格式

//    if (mat_type < 7)
//    {//單通道
//        //cout<<"single"<<endl;
//        Mat planes[] = { Mat_<float>(inputImg), Mat::zeros(inputImg.size(),CV_32F) };
//        merge(planes, 2, Fourier);
//        dft(Fourier, Fourier);
//    }
//    else // 7<mat_type<15
//    {//多通道
//        //cout<<"multiple"<<endl;
//        //Mat tmp;
//        dft(inputImg, Fourier);
//        /*vector<Mat> planes;
//        split(tmp, planes);
//        magnitude(planes[0], planes[1], planes[0]); //?复??化?幅值
//        Fourier = planes[0];*/
//    }
//}

//void hanning(int N, vector <float> &ans)
//{
//    for(int i = 0;i <= N-1 ; ++i){
//        ans[i] = 0.5*(1 - cos(2*M_PI*i/(N-1)));
//    }
//}

void CopyMatVector(vector <Mat> &old_vec , vector <Mat> &new_vec){
    new_vec.clear();
    for(int n = 0 ; n < old_vec.size() ; ++n){
        new_vec.push_back(old_vec[n].clone());
    }
}


//void fftshift(Mat &out)
//{
//    Size sz = out.size();
//    Point pt(0, 0);
//    pt.x = (int)floor(sz.width / 2.0);
//    pt.y = (int)floor(sz.height / 2.0);
//    circshift(out, pt);
//}

//void circshift(Mat &out, const Point &delta)
//{
//    Size sz = out.size();

//    // 錯誤檢查
//    assert(sz.height > 0 && sz.width > 0);
//    // 此種情況不需要移動
//    if ((sz.height == 1 && sz.width == 1) || (delta.x == 0 && delta.y == 0))
//        return;

//    // 需要移動參數的變換，這樣就能輸入各種整數了
//    int x = delta.x;
//    int y = delta.y;
//    if (x > 0) x = x % sz.width;
//    if (y > 0) y = y % sz.height;
//    if (x < 0) x = x % sz.width + sz.width;
//    if (y < 0) y = y % sz.height + sz.height;


//    // 多维的Mat也能移動
//    vector<Mat> planes;
//    split(out, planes);

//    for (size_t i = 0; i < planes.size(); i++)
//    {
//        // 垂直方向移動
//        Mat tmp0, tmp1, tmp2, tmp3;
//        Mat q0(planes[i], Rect(0, 0, sz.width, sz.height - y));
//        Mat q1(planes[i], Rect(0, sz.height - y, sz.width, y));
//        q0.copyTo(tmp0);
//        q1.copyTo(tmp1);
//        tmp0.copyTo(planes[i](Rect(0, y, sz.width, sz.height - y)));
//        tmp1.copyTo(planes[i](Rect(0, 0, sz.width, y)));

//        // 水平方向移動
//        Mat q2(planes[i], Rect(0, 0, sz.width - x, sz.height));
//        Mat q3(planes[i], Rect(sz.width - x, 0, x, sz.height));
//        q2.copyTo(tmp2);
//        q3.copyTo(tmp3);
//        tmp2.copyTo(planes[i](Rect(x, 0, sz.width - x, sz.height)));
//        tmp3.copyTo(planes[i](Rect(0, 0, x, sz.height)));
//    }

//    merge(planes, out);
//}
