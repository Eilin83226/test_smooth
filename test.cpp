#include "test.h"

test::test(){
    qDebug()<<"Hello2";
}


void test::temp(){
    qDebug()<< "Hello world1!";
    if(!myFuncInitialize()){
        qDebug()<<"Could not initialize libmyfunc\n";
        exit(0);
    }

    if(!QTmtimesxInitialize()){
        qDebug()<<"Could not initialize libmyfunc\n";
        exit(0);
    }

    if(!QTbsxfunInitialize()){
        qDebug()<<"Could not initialize libmyfunc\n";
        exit(0);
    }


    qDebug()<< "Hello World3!";

    Mat d(2,2,CV_32FC2,Scalar(1));
    d.at<Vec2f>(0,0)[1] = 1.1;
    d.at<Vec2f>(0,1)[1] = 2.2;
    d.at<Vec2f>(1,0)[1] = 3.3;
    d.at<Vec2f>(1,1)[1] = 4.4;
    mwArray a = mat2mwArray(d);
    cout<<"a = "<<endl;
    cout<<a<<endl;
    mwArray b(2,2,mxSINGLE_CLASS,mxCOMPLEX);
    QTbsxfun(1,b,a,a);
    cout<<"b = "<<endl;
    cout<<b<<endl;
    Mat c = mwArray2mat(b);
    cout<<"c = "<<endl;
    cout<<c<<endl;

//    mwArray a(1,2,mxDOUBLE_CLASS);

//    a(1,1) = 1;
//    a(1,2) = 2;

//    mwArray c(2,1,mxSINGLE_CLASS);

//    c(1,1) = 1;
//    c(2,1) = 2;

//    mwArray b(2,2,mxDOUBLE_CLASS);

//    double d[] = {1,2,3,4,5,6,7,8,9};
//    int h = 3;
//    int w = 3;
//    mwArray e(h,w,mxDOUBLE_CLASS);
//    e.SetData(d,h*w);
//    cout<<e<<endl;

//    QTmtimesx(1,b,c,a);
//    //myFunc(1,b,a);

//    //double *num = new double;

//    //b.GetData(num,1);

//    cout<<"b="<<"\n";
//    cout<<b<<endl;
}



vector <Mat> exp_bsx(Mat &Vec_Src1 , vector <Mat> &Vec_Src2){
    if(!QTexpInitialize()){
        qDebug()<<"Could not initialize libmyfunc\n";
        exit(0);
    }

    int Num_dim = Vec_Src2.size();

    //先將double 轉 float
    if(Vec_Src1.type() == CV_64F){
        Vec_Src1.convertTo(Vec_Src1, CV_32F);
    }
    else if(Vec_Src1.type() == CV_64FC2){
        Vec_Src1.convertTo(Vec_Src1, CV_32FC2);
    }
    else if(Vec_Src1.type() == CV_64FC3){
        Vec_Src1.convertTo(Vec_Src1, CV_32FC3);
    }
    mwArray Src1 = mat2mwArray(Vec_Src1);

    vector <Mat> exp_ans;
    Mat mat_ans;
    for(int n = 0 ; n < Num_dim ; ++n){
        //先將double 轉 float
        if(Vec_Src2.at(n).type() == CV_64F){
            Vec_Src2.at(n).convertTo(Vec_Src2.at(n), CV_32F);
        }
        else if(Vec_Src2.at(n).type() == CV_64FC2){
            Vec_Src2.at(n).convertTo(Vec_Src2.at(n), CV_32FC2);
        }
        else if(Vec_Src2.at(n).type() == CV_64FC3){
            Vec_Src2.at(n).convertTo(Vec_Src2.at(n), CV_32FC3);
        }

        mwArray Src2 = mat2mwArray(Vec_Src2.at(n));
        if(Src1.IsComplex() || Src2.IsComplex()){
            mwArray mw_ans;//(h,w,mxSINGLE_CLASS,mxCOMPLEX);
            QTexp(1,mw_ans,Src1,Src2);
            //cout<<mw_ans<<endl;
            mat_ans = mwArray2mat(mw_ans).clone();
        }
        else{
            mwArray mw_ans;//(h,w,mxSINGLE_CLASS);
            QTexp(1,mw_ans,Src1,Src2);
            //cout<<mw_ans<<endl;
            mat_ans = mwArray2mat(mw_ans).clone();
        }
        exp_ans.push_back(mat_ans.clone());
    }
    return exp_ans;


}



vector <Mat> bsx_time(Mat &Vec_Src1 , vector <Mat> &Vec_Src2){
    if(!QTbsxfunInitialize()){
        qDebug()<<"Could not initialize libmyfunc\n";
        exit(0);
    }

    int Num_dim = Vec_Src2.size();

    //先將double 轉 float
    if(Vec_Src1.type() == CV_64F){
        Vec_Src1.convertTo(Vec_Src1, CV_32F);
    }
    else if(Vec_Src1.type() == CV_64FC2){
        Vec_Src1.convertTo(Vec_Src1, CV_32FC2);
    }
    else if(Vec_Src1.type() == CV_64FC3){
        Vec_Src1.convertTo(Vec_Src1, CV_32FC3);
    }
    mwArray Src1 = mat2mwArray(Vec_Src1);

    vector <Mat> bsx_ans;
    Mat mat_ans;
    for(int n = 0 ; n < Num_dim ; ++n){
        //先將double 轉 float
        if(Vec_Src2.at(n).type() == CV_64F){
            Vec_Src2.at(n).convertTo(Vec_Src2.at(n), CV_32F);
        }
        else if(Vec_Src2.at(n).type() == CV_64FC2){
            Vec_Src2.at(n).convertTo(Vec_Src2.at(n), CV_32FC2);
        }
        else if(Vec_Src2.at(n).type() == CV_64FC3){
            Vec_Src2.at(n).convertTo(Vec_Src2.at(n), CV_32FC3);
        }

        mwArray Src2 = mat2mwArray(Vec_Src2.at(n));

        if(Src1.IsComplex() || Src2.IsComplex()){
            mwArray mw_ans;//(h,w,mxSINGLE_CLASS,mxCOMPLEX);
            QTbsxfun(1,mw_ans,Src1,Src2);
            //cout<<mw_ans<<endl;
            mat_ans = mwArray2mat(mw_ans).clone();
        }
        else{
            mwArray mw_ans;//(h,w,mxSINGLE_CLASS);
            QTbsxfun(1,mw_ans,Src1,Src2);
            //cout<<mw_ans<<endl;
            mat_ans = mwArray2mat(mw_ans).clone();
        }
        bsx_ans.push_back(mat_ans.clone());
    }
    return bsx_ans;


}

vector <Mat> mulMatrix(vector <Mat> &Vec_Src1 , vector <Mat> &Vec_Src2){
    if(!QTmtimesxInitialize()){
        qDebug()<<"Could not initialize libmyfunc\n";
        exit(0);
    }

    int Num_dim = Vec_Src1.size();
    int h = Vec_Src1.at(0).rows;
    int w = Vec_Src2.at(0).cols;

    vector <Mat> mul_ans;
    Mat mat_ans;
    for(int n = 0 ; n < Num_dim ; ++n){
        //先將double 轉 float
        if(Vec_Src1.at(n).type() == CV_64F){
            Vec_Src1.at(n).convertTo(Vec_Src1.at(n), CV_32F);
        }
        else if(Vec_Src1.at(n).type() == CV_64FC2){
            Vec_Src1.at(n).convertTo(Vec_Src1.at(n), CV_32FC2);
        }
        else if(Vec_Src1.at(n).type() == CV_64FC3){
            Vec_Src1.at(n).convertTo(Vec_Src1.at(n), CV_32FC3);
        }

        if(Vec_Src2.at(n).type() == CV_64F){
            Vec_Src2.at(n).convertTo(Vec_Src2.at(n), CV_32F);
        }
        else if(Vec_Src2.at(n).type() == CV_64FC2){
            Vec_Src2.at(n).convertTo(Vec_Src2.at(n), CV_32FC2);
        }
        else if(Vec_Src2.at(n).type() == CV_64FC3){
            Vec_Src2.at(n).convertTo(Vec_Src2.at(n), CV_32FC3);
        }

        mwArray Src1 = mat2mwArray(Vec_Src1.at(n));
        mwArray Src2 = mat2mwArray(Vec_Src2.at(n));

        if(Src1.IsComplex() || Src2.IsComplex()){
            mwArray mw_ans(h,w,mxSINGLE_CLASS,mxCOMPLEX);
            QTmtimesx(1,mw_ans,Src1,Src2);
            mat_ans = mwArray2mat(mw_ans).clone();
        }
        else{
            mwArray mw_ans(h,w,mxSINGLE_CLASS);
            QTmtimesx(1,mw_ans,Src1,Src2);
            mat_ans = mwArray2mat(mw_ans).clone();
        }

        mul_ans.push_back(mat_ans.clone());
    }

    return mul_ans;

}

mwArray mat2mwArray(const Mat imgSrc){
    if(!QTmtimesxInitialize()){
        qDebug()<<"Could not initialize libmyfunc\n";
        exit(0);
    }

    Mat imgSrcs = imgSrc.clone();

    int h, w, c;
    h = imgSrcs.rows;
    w = imgSrcs.cols;
    c = imgSrcs.channels();
    if(c == 1) //gray image
    {
        mwSize dims[2] = {h,w};
        mwArray pMat(2, dims ,mxSINGLE_CLASS);

        float* x = (float*)imgSrcs.data;

        pMat.SetData(x, h*w);

        return pMat;
    }
    else if(c == 2) // 2-channel image
    {
        mwSize dims[2] = {h,w};
        mwArray pMat(2, dims, mxSINGLE_CLASS, mxCOMPLEX);

        for(int i = 0 ; i < h ; ++i){
            for(int j = 0 ; j < w ; ++j){
                pMat(i + 1 , j + 1).Real() = (float)imgSrcs.at<Vec2f>(i,j)[0];
                pMat(i + 1 , j + 1).Imag() = (float)imgSrcs.at<Vec2f>(i,j)[1];
            }
        }
        return pMat;
    }
    else if(c == 3) // 3-channel image
    {
        mwSize dims[3] = {h,w,c};
        mwArray pMat(3, dims, mxSINGLE_CLASS);

        for(int i = 0 ; i < h ; ++i){
            for(int j = 0 ; j < w ; ++j){
                pMat(i + 1 , j + 1 , 1) = (float)imgSrcs.at<Vec3f>(i,j)[2];
                pMat(i + 1 , j + 1 , 2) = (float)imgSrcs.at<Vec3f>(i,j)[1];
                pMat(i + 1 , j + 1 , 3) = (float)imgSrcs.at<Vec3f>(i,j)[0];
            }
        }

        return pMat;
    }

}


Mat mwArray2mat(const mwArray data){
//    if(!QTmtimesxInitialize()){
//        qDebug()<<"Could not initialize libmyfunc\n";
//        exit(0);
//    }

    mwArray dims = data.GetDimensions();
    //cout<<"dims = "<<dims<<endl;
    int n = data.NumberOfDimensions();
    //cout<<"n = "<<n<<endl;
    int M = dims(1);
    int N = dims(2);
    if(n == 2){
        int h = M;
        int w = N;

        if(data.IsComplex()){
            Mat image(h,w,CV_32FC2);
            for(int i = 0 ; i < h ; ++i){
                for(int j = 0 ; j < w ; ++j){
                    float real = data(i+1,j+1).Real();
                    float imag = data(i+1,j+1).Imag();

                    image.at<Vec2f>(i,j)[0] = real;
                    image.at<Vec2f>(i,j)[1] = imag;
                }
            }

            return image;
        }
        else{
            Mat image(h,w,CV_32FC2);
            for(int i = 0 ; i < h ; ++i){
                for(int j = 0 ; j < w ; ++j){
                    float index = data(i+1,j+1);
                    image.at<Vec2f>(i,j)[0] = index;
                    image.at<Vec2f>(i,j)[1] = 0;
                }
            }

            return image;
        }
    }
    else if(n == 3){
        int h = M;
        int w = N;
        int c = dims(3);

        if(c == 2) // 2-channel image
        {
            Mat image(h,w,CV_32FC2);

            for(int i = 0 ; i < h ; ++i){
                for(int j = 0 ; j < w ; ++j){
                    image.at<Vec2f>(i,j)[0] = (float)data.Get(3, i + 1, j + 1, 2);
                    image.at<Vec2f>(i,j)[1] = (float)data.Get(3, i + 1, j + 1, 1);
                }
            }

            return image;
        }
        else if(c == 3) // 3-channel image
        {
            Mat image(h,w,CV_32FC3);

            for(int i = 0 ; i < h ; ++i){
                for(int j = 0 ; j < w ; ++j){
                    image.at<Vec3f>(i,j)[0] = (float)data.Get(3, i + 1, j + 1, 3);
                    image.at<Vec3f>(i,j)[1] = (float)data.Get(3, i + 1, j + 1, 2);
                    image.at<Vec3f>(i,j)[2] = (float)data.Get(3, i + 1, j + 1, 1);
                }
            }

            return image;
        }
    }

}
