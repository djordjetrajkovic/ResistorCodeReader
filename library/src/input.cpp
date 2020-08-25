#include <iostream>
#include <vector>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

#include "input.h"


// Template grayscale
vector<Mat> inputnmsp::loadtemplategrayscale(string path, bool show)
{
    Mat temple = imread(path, IMREAD_GRAYSCALE);
    vector<Mat> templates;
    templates.push_back(temple);
    return templates;
}

// Template binary
vector<Mat> inputnmsp::loadtemplatebinary(string path, bool show)
{
    Mat temple = imread(path, IMREAD_GRAYSCALE);
    threshold(temple, temple, 120, 255, cv::THRESH_BINARY);
    if (show) { namedWindow("Binary", WINDOW_NORMAL); imshow("Binary", temple); }
    vector<Mat> templates;
    templates.push_back(temple);
    return templates;
}

void panmsp::File::openImageFile()
{
    Mat img(imread(imagepath), roi);
    operation->setImage(img);
}

void panmsp::File::openBckgFile()
{
    Mat light(imread(backgroundgpath), roi);
}