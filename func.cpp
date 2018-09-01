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


//    vector <Mat> src1;
//    vector <Mat> src2;
//    vector <Mat> mul_result(2);

//    split(M_Src1,src1);
//    split(M_Src2,src2);

    //------

    Mat ans = Mat::zeros(M_Src1.rows,M_Src1.cols,CV_32FC2);

    //------


    if(one_element){

        //M_Src2 && M_Src1 -> 2 channels
        if(M_Src2.type() >= 8 && M_Src1.type() >= 8){

            ans.forEach<Pixel>
                    (
                      [&](Pixel &pixel, const int * position) -> void
                      {
                        pixel.x = M_Src1.at<Vec2f>(position[0],position[1])[0] * M_Src2.at<Vec2f>(0,0)[0] - M_Src1.at<Vec2f>(position[0],position[1])[1] * M_Src2.at<Vec2f>(0,0)[1];
                        pixel.y = M_Src1.at<Vec2f>(position[0],position[1])[0] * M_Src2.at<Vec2f>(0,0)[1] + M_Src1.at<Vec2f>(position[0],position[1])[1] * M_Src2.at<Vec2f>(0,0)[0];
                      }
                    );

//            mul_result.at(0) = (src1.at(0).mul(src2.at(0).at<float>(0,0))) - (src1.at(1).mul(src2.at(1).at<float>(0,0)));
//            mul_result.at(1) = (src1.at(0).mul(src2.at(1).at<float>(0,0))) + (src1.at(1).mul(src2.at(0).at<float>(0,0)));
        }
        //M_Src2 -> 1 channel , M_Src1 -> 2 channels
        else if(M_Src2.type() < 8 && M_Src1.type() >= 8){

            ans.forEach<Pixel>
                    (
                      [&](Pixel &pixel, const int * position) -> void
                      {
                        pixel.x = M_Src1.at<Vec2f>(position[0],position[1])[0] * M_Src2.at<float>(0,0);
                        pixel.y = M_Src1.at<Vec2f>(position[0],position[1])[1] * M_Src2.at<float>(0,0);
                      }
                    );

//            mul_result.at(0) = src1.at(0).mul(src2.at(0).at<float>(0,0));
//            mul_result.at(1) = src1.at(1).mul(src2.at(0).at<float>(0,0));
        }
        //M_Src2 -> 2 channels , M_Src1 -> 1 channel
        else if(M_Src2.type() >= 8 && M_Src1.type() < 8){

            ans.forEach<Pixel>
                    (
                      [&](Pixel &pixel, const int * position) -> void
                      {
                        pixel.x = M_Src1.at<float>(position[0],position[1]) * M_Src2.at<Vec2f>(0,0)[0];
                        pixel.y = M_Src1.at<float>(position[0],position[1]) * M_Src2.at<Vec2f>(0,0)[1];
                      }
                    );

//            mul_result.at(0) = src1.at(0).mul(src2.at(0).at<float>(0,0));
//            mul_result.at(1) = src1.at(0).mul(src2.at(1).at<float>(0,0));
        }
        //M_Src2 && M_Src1 -> 1 channels
        else{

            ans.forEach<Pixel>
                    (
                      [&](Pixel &pixel, const int * position) -> void
                      {
                        pixel.x = M_Src1.at<float>(position[0],position[1]) * M_Src2.at<float>(0,0);
                        pixel.y = 0;
                      }
                    );

//            mul_result.at(0) = src1.at(0).mul(src2.at(0).at<float>(0,0));
//            mul_result.at(1) = src1.at(0).mul(0);
        }


    }
    else{

        //M_Src2 && M_Src1 -> 2 channels
        if(M_Src2.type() >= 8 && M_Src1.type() >= 8){

            ans.forEach<Pixel>
                    (
                      [&](Pixel &pixel, const int * position) -> void
                      {
                        pixel.x = M_Src1.at<Vec2f>(position[0],position[1])[0] * M_Src2.at<Vec2f>(position[0],position[1])[0] - M_Src1.at<Vec2f>(position[0],position[1])[1] * M_Src2.at<Vec2f>(position[0],position[1])[1];
                        pixel.y = M_Src1.at<Vec2f>(position[0],position[1])[0] * M_Src2.at<Vec2f>(position[0],position[1])[1] + M_Src1.at<Vec2f>(position[0],position[1])[1] * M_Src2.at<Vec2f>(position[0],position[1])[0];
                      }
                    );

//            mul_result.at(0) = (src1.at(0).mul(src2.at(0))) - (src1.at(1).mul(src2.at(1)));
//            mul_result.at(1) = (src1.at(0).mul(src2.at(1))) + (src1.at(1).mul(src2.at(0)));
        }
        //M_Src2 -> 1 channel , M_Src1 -> 2 channels
        else if(M_Src2.type() < 8 && M_Src1.type() >= 8){

            ans.forEach<Pixel>
                    (
                      [&](Pixel &pixel, const int * position) -> void
                      {
                        pixel.x = M_Src1.at<Vec2f>(position[0],position[1])[0] * M_Src2.at<float>(position[0],position[1]);
                        pixel.y = M_Src1.at<Vec2f>(position[0],position[1])[1] * M_Src2.at<float>(position[0],position[1]);
                      }
                    );

//            mul_result.at(0) = src1.at(0).mul(src2.at(0));
//            mul_result.at(1) = src1.at(1).mul(src2.at(0));
        }
        //M_Src2 -> 2 channels , M_Src1 -> 1 channel
        else if(M_Src2.type() >= 8 && M_Src1.type() < 8){

            ans.forEach<Pixel>
                    (
                      [&](Pixel &pixel, const int * position) -> void
                      {
                        pixel.x = M_Src1.at<float>(position[0],position[1]) * M_Src2.at<Vec2f>(position[0],position[1])[0];
                        pixel.y = M_Src1.at<float>(position[0],position[1]) * M_Src2.at<Vec2f>(position[0],position[1])[1];
                      }
                    );

//            mul_result.at(0) = src1.at(0).mul(src2.at(0));
//            mul_result.at(1) = src1.at(0).mul(src2.at(1));
        }
        //M_Src2 && M_Src1 -> 1 channels
        else{

            ans.forEach<Pixel>
                    (
                      [&](Pixel &pixel, const int * position) -> void
                      {
                        pixel.x = M_Src1.at<float>(position[0],position[1]) * M_Src2.at<float>(position[0],position[1]);
                        pixel.y = 0;
                      }
                    );

//            mul_result.at(0) = src1.at(0).mul(src2.at(0));
//            mul_result.at(1) = src1.at(0).mul(0);
        }


    }


//    Mat result;
//    merge(mul_result,result);

//    cout<<"ans = "<<endl;
//    cout<<ans<<endl;
//    cout<<"result = "<<endl;
//    cout<<result<<endl;

    return ans;
}

//-- delete
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

//-- delete
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


void CopyMatVector(vector <Mat> &old_vec , vector <Mat> &new_vec){
    new_vec.clear();
    for(int n = 0 ; n < old_vec.size() ; ++n){
        new_vec.push_back(old_vec[n].clone());
    }
}

