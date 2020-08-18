#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <ostream>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

namespace segment
{
    int funct(Mat, Mat, Mat, bool);
    vector<Point> sampleContour(const Mat&, int n = 300);
}