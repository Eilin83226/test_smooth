#include <opencv2/opencv.hpp>
#include "get_fhog.h"
#include "piotr_fhog/fhog.hpp"
//#include "FHOG-master/pdollar/fhog.h"

void get_fhog(vector <Mat> im,pair<string,hog_parameters> fparam,struct cell gparam,int num_images,vector <vector <Mat>> &feature_image){
    //%extract fhog features using piotrs toolbox. Currently takes no parameters
    //%except hog-cell-size
    //--if ~isfield(fparam, 'nOrients')
    if(!(fparam.second.nOrients.first != "nOrients")){
        //--fparam.nOrients = 9;
        fparam.second.nOrients.first = "nOrients";
        fparam.second.nOrients.second = 9;
    }

    int im_height,im_width,num_im_chan;
    //--[im_height, im_width, num_im_chan, num_images] = size(im);
    im_height = im[0].rows;
    im_width = im[0].cols;
    num_im_chan = im[0].channels();
    //cout<<im_height<<","<<im_width<<","<<num_im_chan<<","<<num_images<<endl;
    //imshow("fhog",im[0]);
    //waitKey(0);
    //--feature_image = zeros(floor(im_height/gparam.cell_size), floor(im_width/gparam.cell_size), fparam.nDim, num_images, 'single');
    //--for k = 1:num_images
    for(int k = 0 ; k < num_images ; ++k){
        //--hog_image = fhog(single(im(:,:,:,k)), gparam.cell_size, fparam.nOrients);
        //Mat image = imread("E:/test_smooth/FHOG-master/pdollar/lena512.bmp",0);
        //color轉gray //*****可能需要改善fhog的方法*****//
        Mat im_temp;
        cvtColor(im[k],im_temp,CV_BGR2GRAY);
        im_temp.convertTo(im_temp,CV_32F);
        // get hog features
        vector <Mat> hog_image = FHoG::extract(im_temp, 2, gparam.cell_size.second, 9);

        /*cout<<"im_type = "<<im_temp.type()<<endl;
        Mat fhog_feature = fhog(im_temp);
        vector<Mat> hog_image;
        split(fhog_feature, hog_image);
        cout<<"im_type = "<<hog_image[0].type()<<endl;
        imshow("fhog",hog_image.at(0));
        waitKey(0);*/

        //%the last dimension is all 0 so we can discard it
        //--feature_image(:,:,:,k) = hog_image(:,:,1:end-1);
        for(int i = 0 ; i < hog_image.size(); ++i){
            feature_image[k].at(i) = hog_image.at(i).clone();
        }
    }
}
