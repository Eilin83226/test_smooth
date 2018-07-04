#ifndef MEXRESIZE2_H
#define MEXRESIZE2_H

#include <math.h>
#include <assert.h>
#include <string.h>
#include "mex.h"
#include "MxArray.hpp"
#include "mexopencv.hpp"
#include "mainwindow.h"
#include <vector>


#include <opencv2/opencv.hpp>

void Resize(mxArray *im_patch, mxArray *resize_target ,string interp ,mxArray *resized_patch);

#endif // MEXRESIZE2_H
