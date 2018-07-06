#ifndef MEXRESIZE_H
#define MEXRESIZE_H

#include "get_pixels.h"
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat mexResize(Mat &im_patch,double resize_target[],string interp);

#endif // MEXRESIZE_H
