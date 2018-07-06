#include "get_subwindow_no_window.h"

void get_subwindow_no_window(vector <Mat> &im,int pos[],int sz[],vector <int> &yys,vector <int> &xxs){
//    %GET_SUBWINDOW Obtain sub-window from image, with replication-padding.
//    %   Returns sub-window of image IM centered at POS ([y, x] coordinates),
//    %   with size SZ ([height, width]). If any pixels are outside of the image,
//    %   they will replicate the values at the borders.
//    %
//    %   The subwindow is also normalized to range -0.5 .. 0.5, and the given
//    %   cosine window COS_WINDOW is applied (though this part could be omitted
//    %   to make the function more general).
//    %
//    %   Jo緌 F. Henriques, 2012
//    %   http://www.isr.uc.pt/~henriques/

//    if isscalar(sz),  %square sub-window
//        sz = [sz, sz];
//    end

//    xs = floor(pos(2)) + (1:sz(2)) - floor(sz(2)/2);
      vector <int> xs;
      for(int i = 1 ; i <= sz[1] ; ++i){
          xs.push_back(floor(pos[1]) + i - floor(sz[1]/2));
          //cout<<xs[i-1]<<" ";
      }//cout<<endl;

//    xxs = xs;
      xxs = xs;

//    ys = floor(pos(1)) + (1:sz(1)) - floor(sz(1)/2);
      vector <int> ys;
      for(int i = 1 ; i <= sz[0] ; ++i){
          ys.push_back(floor(pos[0]) + i - floor(sz[0]/2));
          //cout<<ys[i-1]<<" ";
      }//cout<<endl;

//    yys = ys;
      yys = ys;

//      %check for out-of-bounds coordinates, and set them to the values at
//      %the borders
//      xs(xs < 1) = 1;
      for(int i = 0 ; i < xs.size() ; ++i){
          if(xs[i] < 1){
              xs[i] = 1;
          }
      }

//      ys(ys < 1) = 1;
      for(int i = 0 ; i < ys.size() ; ++i){
          if(ys[i] < 1){
              ys[i] = 1;
          }
      }

//      xs(xs > size(im,2)) = size(im,2);
      for(int i = 0 ; i < xs.size() ; ++i){
          if(xs[i] > im[0].cols){
              xs[i] = im[0].cols;
          }
      }

//      ys(ys > size(im,1)) = size(im,1);
      for(int i = 0 ; i < ys.size() ; ++i){
          if(ys[i] > im[0].rows){
              ys[i] = im[0].rows;
          }
      }

//      %extract image
//      out = im(ys, xs, :);
      vector <Mat> out;
      for(int n = 0 ; n < im.size() ; ++n){
          Mat window(ys.size(),xs.size(),CV_32FC2);
          for(int i = 0 ; i < ys.size() ; ++i){
              for(int j = 0 ; j < xs.size() ; ++j){
                  window.at<Vec2f>(i,j)[0] = im[n].at<Vec2f>(ys[i],xs[j])[0];
                  window.at<Vec2f>(i,j)[1] = im[n].at<Vec2f>(ys[i],xs[j])[1];
              }
          }
          out.push_back(window);
      }
      //cout<<"im = "<<im[0].at<Vec2f>(2,2)[0]<<" "<<im[0].at<Vec2f>(2,2)[1]<<endl;
      //cout<<"in = "<<out[0].at<Vec2f>(2,2)[0]<<" "<<out[0].at<Vec2f>(2,2)[1]<<endl;

      CopyMatVector(out,im);


}
