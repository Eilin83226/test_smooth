#ifndef GET_FHOG_H
#define GET_FHOG_H

#include "get_features.h"

void get_fhog(vector <Mat> im,pair<string,hog_parameters> fparam,struct cell gparam,int num_images,vector <vector <Mat>> &feature_image);


#endif // GET_FHOG_H
