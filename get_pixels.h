#ifndef GET_PIXELS_H
#define GET_PIXELS_H

#include <cmath>
#include <opencv2/opencv.hpp>
#include "bacf_optimized.h"

using namespace cv;
using namespace std;

Mat get_pixels(Mat &im,double pos[],double sz[],double resize_target[]);
#endif // GET_PIXELS_H
