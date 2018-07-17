#include <iostream>
#include <fstream>
#include "load_video_info.h"

//讀groundtruth_rect.txt取得BundingBox
void load_video_info(string video_path,image_info *seq,vector <vector <double> > *ground_truth){
    ifstream fin;
    //--ground_truth = dlmread([video_path '/groundtruth_rect.txt']);
    string ground_truth_path = video_path+"/groundtruth_rect.txt";
    fin.open(ground_truth_path.c_str());
    char temp[30];
    vector <double> rect;
    while(fin.getline(temp,30)){
        //--seq.len = size(ground_truth, 1);

        (*seq).len++;
        const char *delim = ",";
        char *pch;
        pch = strtok(temp,delim);
        while(pch != NULL){
            double num = atoi(pch);
            rect.push_back(num);
            pch = strtok(NULL, delim);
        }
        (*ground_truth).push_back(rect);
        rect.clear();
    }
    fin.close();

    //--seq.init_rect = ground_truth(1,:);
    for(int i = 0 ; i < 4 ; ++i){
        (*seq).init_rect[i] = (*ground_truth)[0][i];
    }

    //--img_path = [video_path '/img/'];
    string img_path;
    //img_path = video_path+"/img/";

    //--img_files = dir(fullfile(img_path, '*.jpg'));
    //--img_files = {img_files.name};
    img_path = "C://Users//Eilin//Documents//MATLAB//BACF//BACF_toUpload//seq//test//test2_853x480//";
    getdir(img_path, (*seq).s_frame);
}

//取得資料夾內所有檔案
int getdir(string dir, vector<string> &files){
    DIR *dp;//創立資料夾指標
    struct dirent *dirp;
    if((dp = opendir(dir.c_str())) == NULL){
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    int ignore=2;
    while((dirp = readdir(dp)) != NULL){//如果dirent指標非空
        if(ignore==0){
            files.push_back(string(dirp->d_name));//將資料夾和檔案名放入vector
        }
        else{//忽略.&..
            ignore--;
        }
    }
    closedir(dp);//關閉資料夾指標
    return 0;
}
