#ifndef _LOAD_VIDEO_INFO_H
#define _LOAD_VIDEO_INFO_H

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include "mainwindow.h"

using namespace std;
class MainWindow;

void load_video_info(string video_path,image_info *seq,vector <vector <double> > *ground_truth);
int getdir(string dir, vector<string> &files);

#endif // LOAD_VIDEO_INFO_H






