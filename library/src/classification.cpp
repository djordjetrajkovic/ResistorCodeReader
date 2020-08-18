#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <ostream>
#include <algorithm>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/shape/shape_distance.hpp>
using namespace cv;

#include "classification.h"

void classificationnmsp::contourSearch(Mat inputimage, vector<vector<Point>>& contours, vector<Rect>& rectangles, bool show)
{
    if (show) imshow("Input image", inputimage);
    Mat temple = imread("template.jpg", IMREAD_GRAYSCALE);
    Mat ftmp[6];
    for (int i=0; i<6; ++i)
    {
        matchTemplate(inputimage,temple,ftmp[i],i);
        normalize(ftmp[i],ftmp[i],1,0,NORM_MINMAX);
    }
    //imshow( "SQDIFF", ftmp[0] );
    //imshow( "SQDIFF_NORMED", ftmp[1] );
    //imshow( "CCORR", ftmp[2] );
    //imshow( "CCORR_NORMED", ftmp[3] );
    //imshow( "CCOEFF_NORMED", ftmp[5] );
    if (show) imshow( "CCOEFF", ftmp[4] );
    
    Mat img_thrld;
    threshold(ftmp[4], img_thrld, 0.5, 1, THRESH_BINARY);
    if (show) imshow("Thresh image", img_thrld);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat rem_small_img;
    dilate(img_thrld, rem_small_img, kernel, Point(-1,-1), 1);
    //morphologyEx(img_thrld, rem_small_img, MORPH_CLOSE,kernel);
    if (show) imshow("DILATE", rem_small_img);
    rem_small_img.convertTo(rem_small_img, CV_8UC1, 255.0); 
    findContours(rem_small_img, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    Mat outputContours(rem_small_img.rows, rem_small_img.cols, rem_small_img.type());
    for (auto i = 0; i < contours.size(); i++) 
    {
        Scalar color = Scalar(rand() % 255, rand() % 255, rand() % 255);
        drawContours(outputContours, contours, i, color);
    }
    
    for(auto contour: contours)
    {
        auto rect = boundingRect(contour);
        rect.x += (int)temple.cols/2 - 1;
        rect.y += (int)temple.rows/2 - 1;
        rectangles.push_back(rect);
        Scalar color = Scalar(rand() % 255);
        rectangle(outputContours, rect, color, 1);
    }
    if (show) imshow("KONTURE", outputContours);
}