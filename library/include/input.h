// STD Libs includes
#include <iostream>
#include <vector>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

namespace inputnmsp
{
    vector<Mat> loadimages(string, bool);
    Mat loadbackground(string, bool);
    vector<Mat> loadtemplatebinary(string, bool);
    vector<Mat> loadtemplategrayscale(string, bool);
}