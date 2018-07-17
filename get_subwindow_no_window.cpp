#include "get_subwindow_no_window.h"

void get_subwindow_no_window(vector <Mat> &im,vector <int> &pos,vector <int> &sz,vector <int> &yys,vector <int> &xxs){
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



      if(sz.size() == 1){
          sz.at(1) = sz.at(0);
      }

//    xs = floor(pos(2)) + (1:sz(2)) - floor(sz(2)/2);
      vector <int> xs;
      for(int i = 1 ; i <= sz[1] ; ++i){
          xs.push_back(floor(pos[1]) + i - floor(sz[1]/2) - 1);
      }

//    xxs = xs;
      xxs = xs;

//    ys = floor(pos(1)) + (1:sz(1)) - floor(sz(1)/2);
      vector <int> ys;
      for(int i = 1 ; i <= sz[0] ; ++i){
          ys.push_back(floor(pos[0]) + i - floor(sz[0]/2) - 1);
      }

//    yys = ys;
      yys = ys;

//      %check for out-of-bounds coordinates, and set them to the values at
//      %the borders
//      xs(xs < 1) = 1;
      for(int i = 0 ; i < xs.size() ; ++i){
          if(xs[i] < 0){
              xs[i] = 0;
          }
      }

//      ys(ys < 1) = 1;
      for(int i = 0 ; i < ys.size() ; ++i){
          if(ys[i] < 0){
              ys[i] = 0;
          }
      }

//      xs(xs > size(im,2)) = size(im,2);
      for(int i = 0 ; i < xs.size() ; ++i){
          if(xs[i] > im[0].cols - 1){
              xs[i] = im[0].cols - 1;
          }
      }

//      ys(ys > size(im,1)) = size(im,1);
      for(int i = 0 ; i < ys.size() ; ++i){
          if(ys[i] > im[0].rows - 1){
              ys[i] = im[0].rows - 1;
          }
      }


//      %extract image
//      out = im(ys, xs, :);
      vector <Mat> out;
      Rect roi(xs[0],ys[0],xs.size(),ys.size());
      for(int n = 0 ; n < im.size() ; ++n){
          Mat window;
          im.at(n)(roi).copyTo(window);
          out.push_back(window);
      }

      CopyMatVector(out,im);


}
