#include <iostream>
#include <vector>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

#include "input.h"

vector<Mat> inputnmsp::loadimages(string slika, bool show)
{
    vector<Mat> inputimages;
    // Load images
    Rect r(300,300, 900, 1200);
    // Main image 
    Mat img(imread(slika, IMREAD_GRAYSCALE), r);
    inputimages.push_back(img);
    
    //namedWindow("Image");
    if (show) imshow("Image", img);
    
    return inputimages;
}

// Background
Mat inputnmsp::loadbackground(string path, bool show)
{
    Rect r(300,300, 900, 1200);
    Mat light(imread(path, IMREAD_GRAYSCALE), r);
    return light;
}

// Template grayscale
vector<Mat> inputnmsp::loadtemplategrayscale(string path, bool show)
{
    Mat temple = imread("template_grayscale.jpg", IMREAD_GRAYSCALE);
    vector<Mat> templates;
    templates.push_back(temple);
    return templates;
}

// Template binary
vector<Mat> inputnmsp::loadtemplatebinary(string path, bool show)
{
    Mat temple = imread("template.jpg", IMREAD_GRAYSCALE);
    vector<Mat> templates;
    templates.push_back(temple);
    return templates;
}