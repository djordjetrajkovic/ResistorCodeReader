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
#include "classification.h"
#include "object.h"

int segment::funct(Mat img, Mat light, Mat templ, bool show)
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

    // contour search algorithm
    vector<vector<Point>> konture;
    vector<Rect> rectangles;
    classificationnmsp::contourSearch(isolated_img, konture, rectangles, show);
    for (auto kontura: konture) cout << "Kontura: "     << kontura.size() << endl;
    for (auto rect: rectangles) cout << "Pravougaonik: "<< rect.size() << endl;

    // Shape Context Distance Extractor
    for (auto rect: rectangles)
    {
        Mat picture = img(rect);
        Ptr<ShapeContextDistanceExtractor> mysc = createShapeContextDistanceExtractor();
        vector<Point> c1 = sampleContour(picture);
        vector<Point> c2 = sampleContour(templ);
        float dis;
        if (!c1.empty() && !c2.empty()) dis = mysc -> computeDistance(c1, c2);
        cout << "Kontura: " << rect.area() << ", "<< "Shape context distance: " << dis << endl;
        
        if (dis < 1) 
        {
            rectangle(img, rect, Scalar(0), 1);
            objectsnmsp::Resistor *res = new objectsnmsp::Resistor();
            res -> setRect(rect);
            delete res;
        }
        else rectangle(img, rect, Scalar(255), 1);

        stringstream ss;
        ss << "Povrsina :" << rect.area();
        putText(img, ss.str(), Point2d(rect.x, rect.y), FONT_HERSHEY_SIMPLEX, 0.5 , Scalar(255));
        
    }
    drawContours(img, konture, -1, Scalar(125));
    imshow("Image", img);
    
    return 0;
}

vector<Point> segment::sampleContour(const Mat& image, int n)
{
    vector<vector<Point>> _contours;
    vector<Point>all_points;
    findContours(image, _contours, RETR_LIST, CHAIN_APPROX_NONE);
    if (_contours.empty()) return all_points;
    for (int i=0; i<_contours.size();i++)
    {
        for (int j=0;j<_contours[i].size();j++)
        {
            all_points.push_back(_contours[i][j]);
        }
    }

    int dummy = 0;
    for (int add=(int)all_points.size();add<n;add++)
    {
        all_points.push_back(all_points[dummy++]);
    }

    random_shuffle(all_points.begin(),all_points.end());
    vector<Point> sampled;
    for (int i=0;i<n;i++) sampled.push_back(all_points[i]);

    return sampled;
}