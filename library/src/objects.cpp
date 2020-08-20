#include <iostream>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

#include "object.h"

string objectsnmsp::Resistor::getDescription()
{
    return "resistor value by colors";
}