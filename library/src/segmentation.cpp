#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <ostream>
#include <algorithm>
#include <random>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/shape/shape_distance.hpp>
using namespace cv;

#include "segmentation.h" 
#include "classification.h"
#include "object.h"

int segment::funct(Mat img, Mat light, bool show)
{
    // Median filter applying
    Mat img_median;
    medianBlur(img, img_median,7);
    //namednamedWindow("Median");
    if (show) imshow("Median", img_median);

    // Background substruction
    Mat img_comp;
    int comp_light = 1; // <------- kontrola
    if (comp_light == 1) img_comp = light - img_median;
    else
    {
        Mat img_median32, light32, img_comp32;
        img_median.convertTo(img_median32, CV_32F);
        light.convertTo(light32, CV_32F);
        img_comp32 = 255 * (1 - img_median32 / light32);
        img_comp32.convertTo(img_comp, CV_8U);
    }
    //namedWindow("Compensated");
    if (show) imshow("Compensated", img_comp);

    // Threshold
    Mat img_thr;
    int method_light = 1; // <------- kontrola
    if (method_light != 2) threshold(img_comp, img_thr, 24, 255, THRESH_BINARY);
    else threshold(img_comp, img_thr, 55, 255, THRESH_BINARY_INV);
    //namedWindow("Threshold");
    if (show) imshow("Threshold", img_thr);

    // Small object removal
    Mat rem_small_img;
    int remove_small = 1;
    if (remove_small == 1)
    {
        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        erode(img_thr, rem_small_img, kernel);
        //dilate(img_thr, rem_small_img, kernel);
    }
    //namedWindow("Remove Small Objects");
    if (show) imshow("Remove Small Objects", rem_small_img);

    // Odredjivanje svih piksela koji pripadaju istom objektu
    Mat labels, stats, centroids;
    auto num_objects = connectedComponentsWithStats(rem_small_img, labels, stats, centroids);
        if (num_objects < 2) 
    {
        cout << "No objects detected!" << endl;
        return -1;
    }
    else
    {
        cout << "Detected objects num: " << num_objects - 1 << endl;
    }
    
    Mat isolated_img = Mat::zeros(img.rows, img.cols, CV_8UC1);
    labels.convertTo(labels, CV_16U); // konverzija u drugi tip pixela OBAVEZNO
    centroids.convertTo(centroids, CV_16U); // konverzija u drugi tip pixela OBAVEZNO
    for (auto i = 1; i < num_objects; i++)
    {
        // ispisivanje lokacije centra mase objekta i povrsine
        cout << "Object " << i << " onto position: (" << centroids.at<short>(i,0) << ", " << centroids.at<short>(i,1) << "), with area: " << stats.at<int>(i, CC_STAT_AREA) << "." << endl;
        Mat mask = labels == i;
        Scalar color = Scalar(255);
        isolated_img.setTo(color, mask);
    }
    //namedWindow("Isolated objects");
    if (show) imshow("Isolated objects", isolated_img);
}