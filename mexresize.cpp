#include "mexresize.h"


Mat mexResize(Mat &im_patch,vector <double> &resize_target,string interp){

    Mat img = im_patch;
    Mat imgr;
    Size s((int)resize_target[0],(int)resize_target[1]);
    Size newSize = Size(s.width,s.height);
    Size oldSize = img.size();

    //interpolation method
    int interpolation = INTER_LINEAR;

    //if interpolation method provided set it
    if(interp.compare("antialias") == 0){
        interpolation = INTER_AREA;
    }else if(interp.compare("linear") == 0){
        interpolation = INTER_LINEAR;
    }else if(interp.compare("auto") == 0){ //if we are zooming, use linear else use area interpolation
      //old array has width and height swapped, newArray does not
        if(newSize.width > oldSize.height){
            interpolation = INTER_LINEAR;
        }else{
            interpolation = INTER_AREA;
        }
    }

    //use opencv resize function
    resize(img,imgr,newSize,0,0,interpolation);
    //convert back to matlab representation
    return imgr;
}
