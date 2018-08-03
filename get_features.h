#ifndef GET_FEATURES_H
#define GET_FEATURES_H

//#include "bacf_optimized.h"
#include "thread_bacf_tracking.h"

void get_features(vector <Mat> image,struct para_features_struct features,struct cell gparams,int num_images,vector <vector <Mat>> &feature_pixels,double support_sz[]);

#endif // GET_FEATURES_H
