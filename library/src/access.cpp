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

Mat access::test(string slika1, string slika2)
{
    // Ucitavanje slika
    Mat color = imread("lena.jpg");

    if (!color.data)
    {
        cout << "Slika nije pronadjena!";
        return;
    }

    return color;
}

void access::locationAt(Mat slika)
{
    
}