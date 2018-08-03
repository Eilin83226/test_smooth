#include "resizedft2.h"
#include "func.h"

void resizeDFT2(vector <Mat> &inputdft,int desiredSize[],vector <Mat> &resizeddft){
//    [imh, imw, n1, n2] = size(inputdft);
    int imh,imw,n1,n2;
    imh = inputdft[0].rows;
    imw = inputdft[0].cols;
    n1 = inputdft.size();
    n2 = 1;

//    imsz = [imh, imw];
    int imsz[2];
    imsz[0] = imh;
    imsz[1] = imw;


    if(desiredSize[0] != imsz[0] || desiredSize[1] != imsz[1]){
//        minsz = min(imsz, desiredSize);
        int minsz[2];
        minsz[0] = min(imsz[0],desiredSize[0]);
        minsz[1] = min(imsz[1],desiredSize[1]);


//        scaling = prod(desiredSize)/prod(imsz);
        double scaling = (desiredSize[0] * desiredSize[1]) / (imsz[0] * imsz[1]);


//        resizeddft = complex(zeros([desiredSize n1 n2], 'single'));
        Mat zero = Mat::zeros(desiredSize[0],desiredSize[1],CV_32FC2);
        for(int i = 0 ; i < n1 ; ++i){
            resizeddft.push_back(zero.clone());
        }


//        mids = ceil(minsz/2);
        int mids[2];
        mids[0] = ceil(minsz[0]/2);
        mids[1] = ceil(minsz[1]/2);

//        mide = floor((minsz-1)/2) - 1;
        int mide[2];
        mide[0] = floor((minsz[0] - 1 ) / 2) - 1;
        mide[1] = floor((minsz[1] - 1 ) / 2) - 1;


        /*for(int n = 0 ; n < n1 ; ++n){

            //        resizeddft(1:mids(1), 1:mids(2), :, :) = scaling * inputdft(1:mids(1), 1:mids(2), :, :);
            Rect roi1(0,0,mids[1],mids[0]);
            Mat temp1 = inputdft.at(n)(roi1).mul(scaling);
            addWeighted(resizeddft.at(n)(roi1),0,temp1,1,0,resizeddft.at(n)(roi1));

            //        resizeddft(1:mids(1), end - mide(2):end, :, :) = scaling * inputdft(1:mids(1), end - mide(2):end, :, :);
            Rect roi2(imw - mide[1] - 1,0,mide[1] + 1,mids[0]);
            Mat temp2 = inputdft.at(n)(roi2).mul(scaling);
            addWeighted(resizeddft.at(n)(roi2),0,temp2,1,0,resizeddft.at(n)(roi2));

            //        resizeddft(end - mide(1):end, 1:mids(2), :, :) = scaling * inputdft(end - mide(1):end, 1:mids(2), :, :);
            Rect roi3(0,imh - mide[0] - 1,mids[1],mide[0] + 1);
            Mat temp3 = inputdft.at(n)(roi3).mul(scaling);
            addWeighted(resizeddft.at(n)(roi3),0,temp3,1,0,resizeddft.at(n)(roi3));

            //        resizeddft(end - mide(1):end, end - mide(2):end, :, :) = scaling * inputdft(end - mide(1):end, end - mide(2):end, :, :);
            Rect roi4(imw - mide[1] - 1,imh - mide[0] - 1,mide[1] + 1,mide[0] + 1);
            Mat temp4 = inputdft.at(n)(roi4).mul(scaling);
            addWeighted(resizeddft.at(n)(roi4),0,temp4,1,0,resizeddft.at(n)(roi4));
        }*/




//        resizeddft(1:mids(1), 1:mids(2), :, :) = scaling * inputdft(1:mids(1), 1:mids(2), :, :);
        for(int n = 0 ; n < n1 ; ++n){
            //resizeddft.at(n) = inputdft.at(n).mul(scaling);
            for(int i = 0 ; i < mids[0] ; ++i){
                for(int j = 0 ; j < mids[1] ; ++j){
                    resizeddft.at(n).at<Vec2f>(i,j)[0] = scaling * inputdft.at(n).at<Vec2f>(i,j)[0];
                    resizeddft.at(n).at<Vec2f>(i,j)[1] = scaling * inputdft.at(n).at<Vec2f>(i,j)[1];
                }
            }
        }

//        resizeddft(1:mids(1), end - mide(2):end, :, :) = scaling * inputdft(1:mids(1), end - mide(2):end, :, :);
        for(int n = 0 ; n < n1 ; ++n){
            for(int i = 0 ; i < mids[0] ; ++i){
                for(int j = imw - mide[1] - 1 ; j < imw ; ++j){
                    resizeddft.at(n).at<Vec2f>(i,j)[0] = scaling * inputdft.at(n).at<Vec2f>(i,j)[0];
                    resizeddft.at(n).at<Vec2f>(i,j)[1] = scaling * inputdft.at(n).at<Vec2f>(i,j)[1];
                }
            }
        }

//        resizeddft(end - mide(1):end, 1:mids(2), :, :) = scaling * inputdft(end - mide(1):end, 1:mids(2), :, :);
        for(int n = 0 ; n < n1 ; ++n){
            for(int i = imh - mide[0] - 1 ; i < imh ; ++i){
                for(int j = 0 ; j < mids[1] ; ++j){
                    resizeddft.at(n).at<Vec2f>(i,j)[0] = scaling * inputdft.at(n).at<Vec2f>(i,j)[0];
                    resizeddft.at(n).at<Vec2f>(i,j)[1] = scaling * inputdft.at(n).at<Vec2f>(i,j)[1];
                }
            }
        }

//        resizeddft(end - mide(1):end, end - mide(2):end, :, :) = scaling * inputdft(end - mide(1):end, end - mide(2):end, :, :);
        for(int n = 0 ; n < n1 ; ++n){
            for(int i = imh - mide[0] - 1 ; i < imh ; ++i){
                for(int j = imw - mide[1] - 1 ; j < imw ; ++j){
                    resizeddft.at(n).at<Vec2f>(i,j)[0] = scaling * inputdft.at(n).at<Vec2f>(i,j)[0];
                    resizeddft.at(n).at<Vec2f>(i,j)[1] = scaling * inputdft.at(n).at<Vec2f>(i,j)[1];
                }
            }
        }
    }
    else{
//        resizeddft = inputdft;
        CopyMatVector(inputdft,resizeddft);
    }
}
