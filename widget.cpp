#include "widget.h"
#include "QWidget"
#include "QDebug"
Widget::Widget(vector <Mat> *tInput_im,bool *tFrameLock,bool *tIsRun):Input_im(tInput_im),FrameLock(tFrameLock),IsRun(tIsRun)
{
//    cap.open("C:/Users/Eilin/Desktop/testVideo/test2_640x480.mp4");
//    if (!cap.isOpened()) {
//        cout << "video open fail!" << endl;
//        system("pause");
//    }
//    cout << "video open success!" << endl;

//    mytimer = new QTimer(this);
//    //showTime();
//    mytimer->start(1000);                   //以1000毫秒為周期起動定時器
//    connect(mytimer,SIGNAL(timeout()),this,SLOT(showTime()));
//    //mytimer->start(1000);                   //以1000毫秒為周期起動定時器
}

//void Widget::showTime()
//{
//  qDebug()<<"fuck";
//}

//void Widget::VideoCaptureSlot(){
//cout<<"videoslot "<<endl;
//    for(int i = 0 ; i < 50; ++i){
//        if(!frameLock){
//            frameLock = true;
//            cout << "videoCaptureSlot start" <<endl;
//            cap >> read_im;
//            cout << "videoCaptureSlot end" <<endl;

//            frameLock = false;
////            if( read_im.empty()){
////                cout << "End." <<endl;
////                isRun = false;

////                return;
////            }
//            imshow("im",read_im);
//            waitKey(1);
//            cout<<"isRun = "<<isRun<<endl;
//            isRun = true;
//            break;
//        }
//    }


//}


void Widget::run(){qDebug()<<*IsRun<<endl;
    while(*IsRun){qDebug()<<*FrameLock;
        if(!*FrameLock && Input_im->size() != 0){
            *FrameLock = true;
            Mat im = Input_im->front();
            Input_im->erase(Input_im->begin());
            cout<<"wid_input_size = "<<Input_im->size()<<endl;
            imshow("im",im);
            waitKey(1);
            *FrameLock =false;
        }
    }
    qDebug()<<"end";
}

