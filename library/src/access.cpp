#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <ostream>
#include "access.h"
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

Mat test(string slika)
{
    // Ucitavanje slika
    Mat color = imread(slika);

    if (!color.data)
    {
        cout << "Slika nije pronadjena!";
    }

    return color;
}

void access::locationAt(string putanja)
{
    Mat slika = test(putanja);
    imshow("Lena BGR", slika);
    int myRow = slika.cols - 1;
    int myCol = slika.rows - 1;
    Point2i myPoint(myRow, myCol);
    // Jedan nacin
    Vec3b pixel = slika.at<Vec3b>(myPoint);
    cout << "Vrednosti piksela (B, G, R): (" << (int)pixel[0] << "," << (int)pixel[1] << "," << (int)pixel[2] << ")" << endl;
    // Drugi nacin
    cout << "Vrednosti piksela (B, G, R): (" << (int)slika.at<Vec3b>(myPoint)[0] << "," << (int)slika.at<Vec3b>(myPoint)[1] << "," << (int)slika.at<Vec3b>(myPoint)[2] << ")"<< endl;
    waitKey(0);
}


void access::locationPtr(string putanja)
{
    Mat slika = test(putanja);

    int channels = slika.channels();
    int nRows = slika.rows;
    int nCols = slika.cols * channels;

    if (slika.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i,j;
    uchar* p;
    for (i=0; i<nRows; ++i)
    {
        p = slika.ptr<uchar>(i);
        for (j=0; j<nCols; ++j)
        {
            cout << (int)p[j] << endl;
        }
    }

    cout << "Vrednosti piksela (0, 0, 0): (" << (int)slika.at<Vec3b>(0,0)[0] << "," << (int)slika.at<Vec3b>(0,0)[1] << "," << (int)slika.at<Vec3b>(0,0)[2] << ")"<< endl;
    
    cout << "Prvi piksel: " << slika.ptr<Vec3b>(0,0)[0] << endl;
    cout << "Prvi piksel, R: " << (int)slika.ptr<Vec3b>(0,0)[0][2] << endl; // mora ekspl. konverzija
}