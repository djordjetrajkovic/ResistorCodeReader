#include <iostream>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

namespace classificationnmsp
{
    void contourSearch(Mat, vector<vector<Point>>&, vector<Rect>&, bool);
}