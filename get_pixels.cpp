#include "get_pixels.h"
#include "mexresize.h"

Mat get_pixels(Mat &im,double pos[],vector <double> &sz,vector <double> &resize_target){

    //目標一開始
    //%square sub-window
    if(sz.size() == 1){
        sz[1] = sz[0];
    }

    //%make sure the size is not to small
    if(sz[0] < 1){
        sz[0] = 2;
    }
    if(sz[1] < 1){
        sz[1] = 2;
    }

    vector <double> xs((int)sz[1]);
    vector <double> ys((int)sz[0]);
    for(int i = 0 ; i < sz[1] ; ++i){
        xs.at(i) = floor(pos[1]) + (i + 1) - floor(sz[1]/2.0) - 1;
    }
    for(int i = 0 ; i < sz[0] ; ++i){
        ys.at(i) = floor(pos[0]) + (i + 1) - floor(sz[0]/2.0) - 1;
    }


    //%check for out-of-bounds coordinates, and set them to the values at
    //%the borders
    for(int i = 0 ; i < sz[1] ; ++i){
        if(xs.at(i) < 0)
            xs.at(i) = 0;
    }
    for(int i = 0 ; i < sz[0] ; ++i){
        if(ys.at(i) < 0)
            ys.at(i) = 0;
    }
    for(int i = 0 ; i < sz[1] ; ++i){
        if(xs.at(i) > (im.cols - 1))
            xs.at(i) = (im.cols - 1);
    }
    for(int i = 0 ; i < sz[0] ; ++i){
        if(ys.at(i) > (im.rows - 1))
            ys.at(i) = (im.rows - 1);
    }


    //%extract image
    Mat im_patch((int)sz[0],(int)sz[1],CV_8UC3,Scalar(0,0,0));
    for(int i = 0 ; i < sz[0] ; ++i){
        for(int j = 0 ; j < sz[1] ; ++j){
            im_patch.at<Vec3b>(i,j)  = im.at<Vec3b>(ys[i],xs[j]);
        }
    }



    Mat resized_patch;
    if(resize_target.size() == 0){
        resized_patch = im_patch.clone();
    }
    else{
        resized_patch = mexResize(im_patch,resize_target,"auto");
    }

//    cout<<"resized_patch = "<<endl;
//    for(int i = 0 ; i < resized_patch.rows ; ++i){
//        for(int j = 0 ; j < resized_patch.cols ; ++j){
//            cout<<(int)resized_patch.at<Vec3b>(i,j)[0]<<" ";
//        }cout<<endl;
//    }
//    imshow("get_pixels",im);
//    waitKey(0);
    return resized_patch;
}
