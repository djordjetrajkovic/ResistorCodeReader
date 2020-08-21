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
#include "object.h"

vector<objectsnmsp::Object*> findObjects(Mat isolated_img, vector<Mat> templ, bool show)
{
    vector<objectsnmsp::Object*> objects;
    for(auto tem: templ) objects = classificationnmsp::searchbyTemplate(isolated_img, tem, show);
    return objects;
}

vector<objectsnmsp::Object*> classificationnmsp::searchbyTemplate(Mat inputimage, Mat temple, bool show)
{
    if (show) imshow("Input image", inputimage);
    Mat ftmp[6];
    for (int i=0; i<6; ++i)
    {
        matchTemplate(inputimage, temple, ftmp[i], i);
        normalize(ftmp[i], ftmp[i], 1, 0, NORM_MINMAX);
    }
    //if (show) imshow( "SQDIFF", ftmp[0] );
    //if (show) imshow( "SQDIFF_NORMED", ftmp[1] );
    //if (show) imshow( "CCORR", ftmp[2] );
    //if (show) imshow( "CCORR_NORMED", ftmp[3] );
    //if (show) imshow( "CCOEFF_NORMED", ftmp[5] );
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
    vector<vector<Point>> contours;
    findContours(rem_small_img, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    Mat outputContours(rem_small_img.rows, rem_small_img.cols, rem_small_img.type());
    vector<objectsnmsp::Object*> objects;
    objectsnmsp::Object *object = new objectsnmsp::Unknown();
    for(auto contour: contours)
    {
        auto rect = boundingRect(contour);
        rect.x += (int)temple.cols/2 - 1;
        rect.y += (int)temple.rows/2 - 1;
        object->setRoi(rect);
        object->setImage(&inputimage);
        objects.push_back(object);
        // drawing
        Scalar color = Scalar(rand() % 255);
        rectangle(outputContours, rect, color, 1);
    }
    
    drawContours(outputContours, contours, -1, Scalar(125));
    if (show) imshow("KONTURE", outputContours);

    return objects;
}

void classificationnmsp::searchbyContour(vector<Object*> objects, Mat isolated_img, vector<Mat> templ, vector<Mat> templebin)
{
    for (int i=0; i < templ.size() && i < templebin.size() ; ++i)
    {
        vector<Point> c2 = sampleContour(templ.at(i), RETR_LIST);
        float dis = 0;
        vector<vector<Point>> templateBinaryContours;
        findContours(templbin.at(i), templateBinaryContours, RETR_EXTERNAL, CHAIN_APPROX_NONE); // kontura binarne slike
        // Shape Context Distance Extractor
        for (auto object: objects)
        {
            Mat picture = (object->getImage())->(object->getRoi());
            Ptr<ShapeContextDistanceExtractor> mysc = createShapeContextDistanceExtractor();
            vector<Point> c1 = sampleContour(picture, RETR_LIST);
            if (!c1.empty() && !c2.empty()) dis = mysc -> computeDistance(c1, c2);
            //cout << "Kontura: " << rect.area() << ", "<< "Shape context distance: " << dis << endl;
            if (dis < 1)
            {
                //rectangle(img, rect, Scalar(0), 1);
                RotatedRect rr  = findRotRect(isolated_img(rect));
                objectsnmsp::Object resistor = new objectsnmsp::Resistor(*object);
                
            }
            //else rectangle(img, rect, Scalar(255), 1);
            
            //stringstream ss;
            //ss << "Povrsina :" << rect.area();
            //putText(img, ss.str(), Point2d(rect.x, rect.y), FONT_HERSHEY_SIMPLEX, 0.5 , Scalar(255));
        }
    }
    drawContours(img, konture, -1, Scalar(125));
    imshow("Image", img);
}

RotatedRect classificationnmsp::findRotRect(Mat sample)
{
    vector<vector<Point>> contours;
    findContours(sample, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    RotatedRect r;
    for(int i = 0; i < contours.size(); ++i)
    {
        Mat obrazac(sample.rows, sample.cols, sample.depth(),Scalar(255));
        drawContours(obrazac, contours, i, Scalar(125));
        stringstream ime; ime << "sample " << rand(); 
        r = fitEllipse(contours[i]);

        Point2f vertices[4];
        r.points(vertices);
        for (int i = 0; i < 4; i++) line(obrazac, vertices[i], vertices[(i+1)%4], Scalar(0), 1);
        Rect brect = r.boundingRect();
        rectangle(obrazac, brect, Scalar(180), 1);

        namedWindow(ime.str(),WINDOW_NORMAL);
        imshow(ime.str(), obrazac);
    }
    return r;
}

vector<Point> classificationnmsp::sampleContour(const Mat& image, int method, int n)
{
    vector<vector<Point>> _contours;
    vector<Point>all_points;
    findContours(image, _contours, method, CHAIN_APPROX_NONE);
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