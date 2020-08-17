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

#include "segmentation.h" 

int segment::funct(string slika, string pozadina, bool show)
{
    // Load images
    Rect r(300,300, 900, 1200);
    // Main image 
    Mat img(imread(slika, IMREAD_GRAYSCALE), r);
    // Background 
    Mat light(imread(pozadina, IMREAD_GRAYSCALE), r);
    //namedWindow("Image");
    if (show) imshow("Image", img);

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

    // contour search algorithm
    vector<vector<Point>> konture;
    vector<Rect> rectangles;
    contourSearch(isolated_img, konture, rectangles, false);

    // Drawing
    for(auto rect: rectangles)
    {
        Scalar color = Scalar(0);
        rectangle(img, rect, color, 1);
        stringstream ss;
        ss << "Povrsina :" << rect.area();
        putText(img, ss.str(), Point2d(rect.x, rect.y), FONT_HERSHEY_SIMPLEX, 0.5 , Scalar(255));
    }
    //namedWindow("Image");
    imshow("Image", img);
    
    // End of execution
    char key;
    while (true)
    {
        key = cv::waitKey('q');
		if (key == 'q') break;
	}
    destroyAllWindows();
    return 0;
}

void segment::contourSearch(Mat inputimage, vector<vector<Point>> contours, vector<Rect>& rectangles, bool show)
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