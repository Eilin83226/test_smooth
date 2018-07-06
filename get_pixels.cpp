#include "get_pixels.h"
#include "mexresize.h"

Mat get_pixels(Mat &im,double pos[],double sz[],double resize_target[]){

    //目標一開始
    //%square sub-window
    /*if(sz.size() == 1){
        sz[1] = sz[0];
    }*/

    //%make sure the size is not to small
    if(sz[0] < 1){
        sz[0] = 2;
    }
    if(sz[1] < 1){
        sz[1] = 2;
    }

    vector <double> xs((int)sz[1]);
    vector <double> ys((int)sz[0]);
    //--xs = floor(pos(2)) + (1:sz(2)) - floor(sz(2)/2);
    for(int i = 0 ; i < sz[1] ; ++i){
        xs.at(i) = floor(pos[1]) + (i + 1) - floor(sz[1]/2.0);
        //cout<<"xs["<<i<<"] = "<<xs[i]<<endl;
    }
    //--ys = floor(pos(1)) + (1:sz(1)) - floor(sz(1)/2);
    for(int i = 0 ; i < sz[0] ; ++i){
        ys.at(i) = floor(pos[0]) + (i + 1) - floor(sz[0]/2.0);
        //cout<<"ys["<<i<<"] = "<<ys[i]<<endl;
    }

    //%check for out-of-bounds coordinates, and set them to the values at
    //%the borders
    //--xs(xs < 1) = 1;
    for(int i = 0 ; i < sz[1] ; ++i){
        if(xs.at(i) < 0)
            xs.at(i) = 0;
    }
    //--ys(ys < 1) = 1;
    for(int i = 0 ; i < sz[0] ; ++i){
        if(ys.at(i) < 0)
            ys.at(i) = 0;
    }
    //--xs(xs > size(im,2)) = size(im,2);
    for(int i = 0 ; i < sz[1] ; ++i){
        if(xs.at(i) > (im.cols - 1))
            xs.at(i) = (im.cols - 1);
    }
    //--ys(ys > size(im,1)) = size(im,1);
    for(int i = 0 ; i < sz[0] ; ++i){
        if(ys.at(i) > (im.rows - 1))
            ys.at(i) = (im.rows - 1);
    }

    //%extract image
    //--im_patch = im(ys, xs, :);
    Mat im_patch((int)sz[0],(int)sz[1],CV_8UC3,Scalar(0,0,0));
    for(int i = 0 ; i < sz[0] ; ++i){
        for(int j = 0 ; j < sz[1] ; ++j){
            //cout<<"i = "<<i<<",j = "<<j<<"   ys["<<i<<"] = "<<ys[i]<<",xs["<<j<<"] = "<<xs[j]<<endl;
            im_patch.at<Vec3b>(i,j)  = im.at<Vec3b>(ys[i],xs[j]);
            //im_patch.at<Vec3b>(i,j)[0]  = im.at<Vec3b>(ys[i],xs[j])[0];
            //im_patch.at<Vec3b>(i,j)[1]  = im.at<Vec3b>(ys[i],xs[j])[1];
            //im_patch.at<Vec3b>(i,j)[2]  = im.at<Vec3b>(ys[i],xs[j])[2];
        }
    }

    Mat resized_patch;
    //--if isempty(resize_target)
    if(sizeof(resize_target) == 0){
        resized_patch = im_patch.clone();
    }
    //--else
    else{
        //--resized_patch = mexResize(im_patch,resize_target,'auto');
        resized_patch = mexResize(im_patch,resize_target,"auto");
//        imshow("im_patch",im_patch);
//        imshow("resized_patch",resized_patch);
//        cout<<im_patch.size()<<","<<resized_patch.size()<<endl;
//        waitKey(0);
    //--end
    }
    return resized_patch;
}
