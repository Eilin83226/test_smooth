#include "get_features.h"
#include "get_fhog.h"

void get_features(vector <Mat> image,struct para_features_struct features,struct cell gparams,int num_images,vector <vector <Mat>> &feature_pixels,double support_sz[]){

    int im_height,im_width,num_im_chan;
    im_height = image[0].rows;
    im_width = image[0].cols;
    num_im_chan = image[0].channels();

    //--colorImage = num_im_chan == 3;
    bool colorImage = false;
    if(num_im_chan == 3){
        colorImage = true;
    }


    //%compute total dimension of all features
    //--tot_feature_dim = 0;
    int tot_feature_dim = 0;

    for(int n = 0 ; n < 1; ++n){
        if(features.fparams.second.useForColor.first != "useForColor"){
            //--features{n}.fparams.useForColor = true;
            features.fparams.second.useForColor.first = "useForColor";
            features.fparams.second.useForColor.second = true;
        }

        if(features.fparams.second.useForGray.first != "useForGray"){
            //--features{n}.fparams.useForGray = true;
            features.fparams.second.useForGray.first = "useForGray";
            features.fparams.second.useForGray.second = true;
        }

        if((features.fparams.second.useForColor.second && colorImage) || (features.fparams.second.useForGray.second && !colorImage)){
            //--tot_feature_dim = tot_feature_dim + features{n}.fparams.nDim;
            tot_feature_dim += features.fparams.second.nDim.second;
        }
    }


    //如果是多圖的話，Size最多4個
    double fg_size[4];
    if(gparams.cell_size.second == -1){
            //--fg_size = size(features{1}.getFeature(image,features{1}.fparams,gparams));
        fg_size[0] = floor((float)im_height/gparams.cell_size.second);
        fg_size[1] = floor((float)im_width/gparams.cell_size.second);
        fg_size[2] = tot_feature_dim;
        fg_size[3] = num_images;
    }
    else{
            //--fg_size = [floor(im_height/gparams.cell_size), floor(im_width/gparams.cell_size)];
        fg_size[0] = floor((float)im_height/gparams.cell_size.second);
        fg_size[1] = floor((float)im_width/gparams.cell_size.second);
    }



    //% temporary hack for fixing deep features
    //--if gparams.cell_size == -1
    if(gparams.cell_size.second == -1){

        //--cf = features{1};
        struct para_features_struct cf = features;

        if((cf.fparams.second.useForColor.second && colorImage) || (cf.fparams.second.useForGray.second && !colorImage)){
            //--[feature_pixels, support_sz] = cf.getFeature(image,cf.fparams,gparams);
            //*****太多輸出不能跑*****//
            ;//要用到get_fhog
        }
    }
    else{
        //%compute the feature set
        //--feature_pixels = zeros(fg_size(1),fg_size(2),tot_feature_dim, num_images, 'single');
        //****Mat feature_pixels[num_images];
        /*Mat zero = Mat::zeros(fg_size[0],fg_size[1],CV_32F);
        for(int i = 0 ; i < num_images ; ++i){
            for(int j = 0 ; j < tot_feature_dim ; ++j){
                feature_pixels[i].push_back(zero.clone());
            }
        }*/

        //--currDim = 1;
        double currDim = 1;


        for(int n = 0 ; n < 1 ; ++n){
            //--cf = features{n};
            struct para_features_struct cf = features;

            if((cf.fparams.second.useForColor.second && colorImage) || (cf.fparams.second.useForGray.second && !colorImage)){

                //--feature_pixels(:,:,currDim:(currDim+cf.fparams.nDim-1),:) = cf.getFeature(image,cf.fparams,gparams);
                get_fhog(image,cf.fparams,gparams,num_images,feature_pixels);

                //--currDim = currDim + cf.fparams.nDim;
                currDim += cf.fparams.second.nDim.second;
            }
        }

//        cout<<"feature_pixels = "<<endl;
//        cout<<feature_pixels[0].at(0)<<endl;
//        imshow("image",image[0]);
//        waitKey(0);

        support_sz[0] = im_height;
        support_sz[1] = im_width;
    }

}
