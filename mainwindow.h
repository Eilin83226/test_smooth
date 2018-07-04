#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QProcess>
#include <QPixmap>
#include <QScreen>
#include <vector>
#include <QImage>
#include <QtSql/QSqlDatabase>
#include <QDesktopWidget>
#include <QMutex>
#include <QMainWindow>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <complex>
#include "mclmcrrt.h"
#include "mclcppclass.h"
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//extern struct image_info seq;
//extern vector <vector <double> > ground_truth;

class image_info{
public:
    int len=0;
    double init_rect[4];
    vector <string> s_frame;
    string VidName;
    int st_frame;
    int en_frame;
};

class track_result{
public:
    string type;
    vector <Rect> res;
    double fps;
};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    double learning_rate; //you can use different learning rate for different benchmarks.
    image_info seq;
    track_result results;
    vector <vector <double> > ground_truth;



private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
