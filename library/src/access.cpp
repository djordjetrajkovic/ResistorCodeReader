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
#include <opencv2/shape/shape_distance.hpp>
using namespace cv;

// Mat test(string slika)
// {
//     // Ucitavanje slika
//     Mat color = imread(slika);

//     if (!color.data)
//     {
//         cout << "Slika nije pronadjena!";
//     }

//     return color;
// }

// void access::locationAt(string putanja)
// {
//     Mat slika = test(putanja);
//     imshow("Lena BGR", slika);
//     int myRow = slika.cols - 1;
//     int myCol = slika.rows - 1;
//     Point2i myPoint(myRow, myCol);
//     // Jedan nacin
//     Vec3b pixel = slika.at<Vec3b>(myPoint);
//     cout << "Vrednosti piksela (B, G, R): (" << (int)pixel[0] << "," << (int)pixel[1] << "," << (int)pixel[2] << ")" << endl;
//     // Drugi nacin
//     cout << "Vrednosti piksela (B, G, R): (" << (int)slika.at<Vec3b>(myPoint)[0] << "," << (int)slika.at<Vec3b>(myPoint)[1] << "," << (int)slika.at<Vec3b>(myPoint)[2] << ")"<< endl;
//     waitKey(0);
// }


// void access::locationPtr(string putanja)
// {
//     Mat slika = test(putanja);

//     int channels = slika.channels();
//     int nRows = slika.rows;
//     int nCols = slika.cols * channels;

//     if (slika.isContinuous())
//     {
//         nCols *= nRows;
//         nRows = 1;
//     }

//     int i,j;
//     uchar* p;
//     for (i=0; i<nRows; ++i)
//     {
//         p = slika.ptr<uchar>(i);
//         for (j=0; j<nCols; ++j)
//         {
//             cout << (int)p[j] << endl;
//         }
//     }

//     cout << "Vrednosti piksela (0, 0, 0): (" << (int)slika.at<Vec3b>(0,0)[0] << "," << (int)slika.at<Vec3b>(0,0)[1] << "," << (int)slika.at<Vec3b>(0,0)[2] << ")"<< endl;
    
//     cout << "Prvi piksel: " << slika.ptr<Vec3b>(0,0)[0] << endl;
//     cout << "Prvi piksel: " << *slika.ptr<Vec3b>(0,0) << endl;
//     cout << "Prvi piksel, R: " << (int)slika.ptr<Vec3b>(0,0)[0][2] << endl; // mora ekspl. konverzija
// }

// void access::iterator(string putanja)
// {
//     Mat slika = test(putanja);
//     Mat grayLena, grayLena2;
//     cvtColor(slika, grayLena, COLOR_BGR2GRAY);
//     cvtColor(slika, grayLena2, COLOR_BGR2GRAY);
//     imshow("Gray", grayLena);

//     // Iterator
//     MatIterator_<uchar> it, end;
//     for (it = grayLena.begin<uchar>(), end=grayLena.end<uchar>(); it != end; ++it)
//     {
//         *it = 212;
//     }
//     imshow("212", grayLena);
    
//     // Const Iterator
//     MatConstIterator_<Vec3b> itt = slika.begin<Vec3b>(), endd = slika.end<Vec3b>();
//     int sum = 0;
//     while ( itt != endd)
//     {
//         // cout << *itt << endl;
//         sum += (int)(*itt)[0] + (int)(*itt)[1] + (int)(*itt)[2];
//         itt++;
//     }
//     cout << "Suma: " << sum << endl;

//     waitKey(0);
// }

// void access::iterator2()
// {
//     const int n_mat_size = 3;
//     const int n_mat_sz[] = { n_mat_size , n_mat_size, n_mat_size };
//     cv::Mat m1(3, n_mat_sz, CV_8UC3);

//     cv::MatIterator_<Vec3b> it = m1.begin<Vec3b>();
//     cv::MatIterator_<Vec3b> end = m1.end<Vec3b>();
//     for (uchar i = 0; it != end; ++it, ++i)
//     {
//         (*it)[0] = i;
//         (*it)[1] = i * 10;
//         (*it)[2] = i * 100;
//     }

//     cv::InputArray arr(m1);
//     std::vector<cv::Mat> planes;
//     arr.getMatVector(planes);
//     for (size_t i = 0; i < planes.size(); ++i)
//     {
//         std::cout << "-------" << std::endl << planes[i] << std::endl << "******" << std::endl;
//         vector<Mat> bgr;
//         split(planes[i], bgr);
//         for (size_t j=0; j<bgr.size(); ++j)
//         {
//             std::cout << "++++++++" << endl << bgr.at(j) << endl << "^^^^^^^^" << endl;
//         }
//     }

//     cout << "planes.size: " << planes.size() << endl;
// }

// void access::naryiterator(string putanja)
// {
//     // const int n_mat_size = 3;
//     // const int n_mat_sz[] = { n_mat_size, n_mat_size, n_mat_size };
//     // Mat n_mat( 3, n_mat_sz, CV_32FC1 );

//     // RNG rng;
//     // rng.fill( n_mat, RNG::UNIFORM, 0.f, 1.f );

//     // First, we need a C-style array containing pointers to all of the cv::Mats 
//     // we wish to iterate over (in this example, there is just one). This array 
//     // must always be terminated with a 0 or NULL
    
//     Mat n_mat = test(putanja);
//     const Mat* arrays[] = { &n_mat, 0 };
//     // Next, we need another C-style array of cv::Mats that can be used to refer
//     // to the individual planes as we iterate over them (in this case, there is also just one)
//     Mat my_planes[1];
//     NAryMatIterator it( arrays, my_planes );

//     // On each iteration, it.planes[i] will be the current plane of the
//     // i-th array from 'arrays'.
    
//     int s = 0, ss = 0, sss = 0;          // Total sum over all planes
//     int   n = 0;                                 // Total number of planes
//     for (int p = 0; p < it.nplanes; p++, ++it) 
//     {
//         s   += sum(it.planes[0])[0];
//         ss  += sum(it.planes[0])[1];
//         sss += sum(it.planes[0])[2];
//         n++;
//     }
//     cout << "Suma 1: "       << s   << endl;
//     cout << "Suma 2: "       << ss  << endl;
//     cout << "Suma 3: "       << sss << endl;
//     cout << "Broj ravni: "   << n   << endl;
// }

// void access::naryiterator()
// {
//     const int n_mat_size = 5;
//     const int n_mat_sz[] = { n_mat_size, n_mat_size };
//     cv::Mat n_mat0( 2, n_mat_sz, CV_32FC3 );
//     cv::Mat n_mat1( 2, n_mat_sz, CV_32FC3 );

//     cv::RNG rng;
//     rng.fill( n_mat0, cv::RNG::UNIFORM, 0.f, 1.f );
//     rng.fill( n_mat1, cv::RNG::UNIFORM, 0.f, 1.f );

//     const cv::Mat* arrays[] = { &n_mat0, &n_mat1, 0 };
//     cv::Mat my_planes[2];
//     cv::NAryMatIterator it( arrays, my_planes );
//     cout << "it size: "    << it.size    << endl;
//     cout << "it.nplanes: " << it.nplanes << endl;

//     float s = 0.f;                    // Total sum over all planes in both arrays
//     int   n = 0;                      // Total number of planes
//     for(int p = 0; p < it.nplanes; p++, ++it) 
//     {
//         //cout << "Plane: " << it.planes[0] << endl;
//         cout << sum(it.planes[0]) << endl;
//         cout << sum(it.planes[1]) << endl;
//         s += cv::sum(it.planes[0])[0];
//         s += cv::sum(it.planes[1])[0];
//         n++;
//     }
//     cout << "Number of iterations: " << n << endl;
//     cout << "Sum: " << s << endl;
// }

void opnmsp::FindByTemplate::findObjects()
{
    Mat img_isolated;
    segment(img_isolated);
    searchByTemplate(img_isolated);
}

void opnmsp::FindByTemplate::segment(Mat& img_isolated)
{
    bool show = false;
    if (show) { namedWindow("Original Image"); imshow("Original Image", image); }
    // convert to grayscale
    Mat image_grayscale, bckg_grayscale;
    cvtColor(image, image_grayscale, COLOR_BGR2GRAY);
    cvtColor(background, bckg_grayscale, COLOR_BGR2GRAY);
    
    // Median filter applying
    Mat img_median;
    medianBlur(image_grayscale, img_median, 7);
    if (show) { namedWindow("Median"); imshow("Median", img_median); }

    // Background substruction
    Mat img_comp;
    img_comp = bckg_grayscale - img_median;
    if (show) { namedWindow("Compensated"); imshow("Compensated", img_comp);}

    // Threshold
    Mat img_thr;
    threshold(img_comp, img_thr, 24, 255, THRESH_BINARY);
    if (show) { namedWindow("Threshold"); imshow("Threshold", img_thr); }

    // Small object removal
    Mat img_rem_small;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    erode(img_thr, img_rem_small, kernel);
    //dilate(img_thr, rem_small_img, kernel);
    if (show) { namedWindow("Remove Small Objects"); imshow("Remove Small Objects", img_rem_small); }

    // Odredjivanje svih piksela koji pripadaju istom objektu
    Mat labels, stats, centroids;
    auto num_objects = connectedComponentsWithStats(img_rem_small, labels, stats, centroids);
    if (num_objects < 2) 
    {
        cout << "No objects detected!" << endl;
        return;
    }
    else
    {
        cout << "Detected objects num: " << num_objects - 1 << endl;
    }
    
    img_isolated = Mat::zeros(image.rows, image.cols, CV_8UC1);
    labels.convertTo(labels, CV_16U);
    centroids.convertTo(centroids, CV_16U);
    for (auto i = 1; i < num_objects; i++)
    {
        // ispisivanje lokacije centra mase objekta i povrsine
        cout << "Object " << i << " onto position: (" << centroids.at<short>(i,0) << ", " << centroids.at<short>(i,1) << "), with area: " << stats.at<int>(i, CC_STAT_AREA) << "." << endl;
        Mat mask = labels == i;
        Scalar color = Scalar(255);
        img_isolated.setTo(color, mask);
    }
    if (show) { namedWindow("Isolated objects"); imshow("Isolated objects", img_isolated); }
}

void opnmsp::FindByTemplate::searchByTemplate(Mat img_isolated)
{
    bool show = true;
    for (auto sample: samples)
    {
        Mat ftmp[6];
        for (int i=0; i<6; ++i)
        {
            matchTemplate(img_isolated, sample->getImagePatternGrayscale(), ftmp[i], i);
            normalize(ftmp[i], ftmp[i], 1, 0, NORM_MINMAX);
        }
        if (show) { namedWindow("SQDIFF"); imshow( "SQDIFF", ftmp[0] ); }
        if (show) { namedWindow("SQDIFF_NORMED"); imshow( "SQDIFF_NORMED", ftmp[1] ); }
        if (show) { namedWindow("CCORR"); imshow( "CCORR", ftmp[2] ); }
        if (show) { namedWindow("CCORR_NORMED"); imshow( "CCORR_NORMED", ftmp[3] ); }
        if (show) { namedWindow("CCOEFF"); imshow( "CCOEFF", ftmp[4] ); }
        if (show) { namedWindow("CCOEFF_NORMED"); imshow( "CCOEFF_NORMED", ftmp[5] ); }
        
        Mat img_thrld;
        threshold(ftmp[4], img_thrld, 0.5, 1, THRESH_BINARY);
        if (show) { namedWindow("Thresh image"); imshow("Thresh image", img_thrld); }

        Mat img_rem_small;
        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        dilate(img_thrld, img_rem_small, kernel, Point(-1,-1), 1);
        //morphologyEx(img_thrld, rem_small_img, MORPH_CLOSE,kernel);
        if (show) { namedWindow("DILATE"); imshow("DILATE", img_rem_small); }

        img_rem_small.convertTo(img_rem_small, CV_8UC1, 255.0);
        vector<vector<Point>> contours;
        findContours(img_rem_small, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        Mat outputContours(img_rem_small.rows, img_rem_small.cols, img_rem_small.type());
        for(auto contour: contours)
        {
            auto rect = boundingRect(contour);
            rect.x += (int)(sample->getImagePatternGrayscale().cols/2 - 1);
            rect.y += (int)(sample->getImagePatternGrayscale().rows/2 - 1);
            Mat image_of_interest = image(rect);
            //searchByContour(image_of_interest, sample->getImagePatternBinary(), sample);
            
            // drawing
            Scalar color = Scalar(rand() % 255);
            rectangle(outputContours, rect, color, 1);
        }
        drawContours(outputContours, contours, -1, Scalar(125));
        if (show) { namedWindow("KONTURE"); imshow("KONTURE", outputContours); } 
    }
}

void opnmsp::FindByTemplate::searchByContour(Mat& image_local, Mat temple, objectsnmsp::AObject* sample)
{

    vector<Point> c2 = sampleContour(temple, 300);
    float dis = 0;
    vector<vector<Point>> templateBinaryContours;
    findContours(temple, templateBinaryContours, RETR_EXTERNAL, CHAIN_APPROX_NONE); // kontura binarne slike
    
    // Shape Context Distance Extractor
    Ptr<ShapeContextDistanceExtractor> mysc = createShapeContextDistanceExtractor();
    vector<Point> c1 = sampleContour(image_local, 300);
    if (!c1.empty() && !c2.empty()) dis = mysc -> computeDistance(c1, c2);
    //cout << "Kontura: " << rect.area() << ", "<< "Shape context distance: " << dis << endl;
    if (dis < 1)
    {
        //rectangle(img, rect, Scalar(0), 1);
        //RotatedRect rr  = findRotRect(isolated_img(rect));
        objectsnmsp::AObject *newobject = sample->clone(); // Proveri dal treba izvan petlje
        newobject->setImage(image_local);
        newobject->setConture(c1);
        //newobject->setRotRect(rr);
        objects.push_back(newobject);
    }
    //stringstream ss;
    //ss << "Povrsina :" << rect.area();
    //putText(img, ss.str(), Point2d(rect.x, rect.y), FONT_HERSHEY_SIMPLEX, 0.5 , Scalar(255));
    
    //drawContours(image, konture, -1, Scalar(125));
    //imshow("Image", img);
}

vector<Point> opnmsp::FindByTemplate::sampleContour(Mat img_local, int npoints)
{
    vector<vector<Point>> _contours;
    vector<Point>all_points;
    findContours(img_local, _contours, RETR_LIST, CHAIN_APPROX_NONE);
    if (_contours.empty()) return all_points;
    for (int i=0; i<_contours.size();i++)
    {
        for (int j=0;j<_contours[i].size();j++)
        {
            all_points.push_back(_contours[i][j]);
        }
    }

    int dummy = 0;
    for (int add=(int)all_points.size();add<npoints;add++)
    {
        all_points.push_back(all_points[dummy++]);
    }

    random_shuffle(all_points.begin(),all_points.end());
    vector<Point> sampled;
    for (int i=0;i<npoints;i++) sampled.push_back(all_points[i]);

    return sampled;
}

RotatedRect opnmsp::FindByTemplate::findRotRect(Mat sample)
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

opnmsp::AFind::~AFind()
{
    for(auto object: objects) delete object;
    for(auto sample: samples) delete sample;
}