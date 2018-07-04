#include <opencv2/opencv.hpp>
#include "FHOG.hpp"
using namespace cv;
int main (){

    // Read image example
    cv::Mat image = cv::imread("./datasets/cameraman.jpg", CV_LOAD_IMAGE_COLOR);

    // Cell size
    int cellSize = 4;

    // Scale applied
    int scale = 1;

    // Create object
    HogFeature FHOG(cellSize, scale);
imshow("a",image);
waitKey(0);
    // Extract FHOG features
    cv::Mat features = FHOG.getFeature(image);

    return 0;
}

