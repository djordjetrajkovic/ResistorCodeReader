#include <iostream>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

#include <object.h>

namespace classificationnmsp
{
    //vector<objectsnmsp::Object*> findObjects(Mat, vector<Mat> , bool);
    vector<objectsnmsp::Object*> searchbyTemplate(Mat, Mat, bool);
    void searchbyContour(vector<objectsnmsp::Object*>, Mat, vector<Mat>, vector<Mat>);
    RotatedRect findRotRect(Mat);
    vector<Point> sampleContour(const Mat&, int, int);
}