#ifndef WIDGET_H
#define WIDGET_H

#include <QTimer>
#include <QTime>
#include <QLCDNumber>
#include <QObject>
#include <QThread>
#include "thread_bacf_tracking.h"
class Widget : public QThread
{
    Q_OBJECT
/*
public:
    Widget();
private:
    QTimer *myTimer;
//    QLCDNumber *myLCDNumber;

protected:
    void run();

private slots:
    void showTime();  //顯示時間的函式
*/
public:
    Widget();


protected:
    void run();

//signals:
private slots:
    void VideoCaptureSlot();
    void showTime();


private:
    //調整追蹤大小
    const double width = 240;
    const double height = 135;
    const double img_w = 853;
    const double img_h = 480;
    const double show_w = 640;
    const double show_h = 480;

    bool frameLoce = false;

    //初始化的參數
    double learning_rate;
    int nScales;
    int interpolate_response;
    //QTimer *timer;


    VideoCapture cap;
    QTimer *mytimer;
    bool isFirstFrame = true;
    bool isRun = false;
    bool frameLock;
    Mat read_im;

};



#endif // WIDGET_H
