#include "mexresize2.h"
#include <opencvmex.hpp>
#include "engine.h"

using namespace std;
using namespace cv;

/*
 *	Use opencv function to resample image quickly
 */

// matlab entry point
// dst = resize(src, scale)
// image should be color with double values
void Resize(mxArray *im_patch[], mxArray *resize_target ,string interp ,mxArray *resized_patch) {


  vector<MxArray> rhs(im_patch,im_patch+1);
  //rhs.push_back(*im_patch);
  //rhs.push_back(resize_target);

  //convert input data to opencv matrix
  Mat img = rhs[0].toMat();
  /*
  
  
  
  Mat imgr;
  Size s = rhs[1].toSize();
  Size newSize = Size(s.height,s.width);
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
    }else{
      mexErrMsgTxt("Invalid interpolation provided, valid is linear (default), antialias, auto");
    }


  //use opencv resize function
  resize(img,imgr,newSize,0,0,interpolation);*/
  //convert back to matlab representation
  //resized_patch = ocvMxArrayFromImage_double(imgr);
}



