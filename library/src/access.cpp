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
    cout << "Prvi piksel: " << *slika.ptr<Vec3b>(0,0) << endl;
    cout << "Prvi piksel, R: " << (int)slika.ptr<Vec3b>(0,0)[0][2] << endl; // mora ekspl. konverzija
}

void access::iterator(string putanja)
{
    Mat slika = test(putanja);
    Mat grayLena, grayLena2;
    cvtColor(slika, grayLena, COLOR_BGR2GRAY);
    cvtColor(slika, grayLena2, COLOR_BGR2GRAY);
    imshow("Gray", grayLena);

    // Iterator
    MatIterator_<uchar> it, end;
    for (it = grayLena.begin<uchar>(), end=grayLena.end<uchar>(); it != end; ++it)
    {
        *it = 212;
    }
    imshow("212", grayLena);
    
    // Const Iterator
    MatConstIterator_<Vec3b> itt = slika.begin<Vec3b>(), endd = slika.end<Vec3b>();
    int sum = 0;
    while ( itt != endd)
    {
        // cout << *itt << endl;
        sum += (int)(*itt)[0] + (int)(*itt)[1] + (int)(*itt)[2];
        itt++;
    }
    cout << "Suma: " << sum << endl;

    waitKey(0);
}

void access::iterator2()
{
    const int n_mat_size = 3;
    const int n_mat_sz[] = { n_mat_size , n_mat_size, n_mat_size };
    cv::Mat m1(3, n_mat_sz, CV_8UC3);

    cv::MatIterator_<Vec3b> it = m1.begin<Vec3b>();
    cv::MatIterator_<Vec3b> end = m1.end<Vec3b>();
    for (uchar i = 0; it != end; ++it, ++i)
    {
        (*it)[0] = i;
        (*it)[1] = i * 10;
        (*it)[2] = i * 100;
    }

    cv::InputArray arr(m1);
    std::vector<cv::Mat> planes;
    arr.getMatVector(planes);
    for (size_t i = 0; i < planes.size(); ++i)
    {
        std::cout << "-------" << std::endl << planes[i] << std::endl << "******" << std::endl;
        vector<Mat> bgr;
        split(planes[i], bgr);
        for (size_t j=0; j<bgr.size(); ++j)
        {
            std::cout << "++++++++" << endl << bgr.at(j) << endl << "^^^^^^^^" << endl;
        }
    }

    cout << "planes.size: " << planes.size() << endl;
}

void access::naryiterator(string putanja)
{
    // const int n_mat_size = 3;
    // const int n_mat_sz[] = { n_mat_size, n_mat_size, n_mat_size };
    // Mat n_mat( 3, n_mat_sz, CV_32FC1 );

    // RNG rng;
    // rng.fill( n_mat, RNG::UNIFORM, 0.f, 1.f );

    // First, we need a C-style array containing pointers to all of the cv::Mats 
    // we wish to iterate over (in this example, there is just one). This array 
    // must always be terminated with a 0 or NULL
    
    Mat n_mat = test(putanja);
    const Mat* arrays[] = { &n_mat, 0 };
    // Next, we need another C-style array of cv::Mats that can be used to refer
    // to the individual planes as we iterate over them (in this case, there is also just one)
    Mat my_planes[1];
    NAryMatIterator it( arrays, my_planes );

    // On each iteration, it.planes[i] will be the current plane of the
    // i-th array from 'arrays'.
    
    int s = 0, ss = 0, sss = 0;          // Total sum over all planes
    int   n = 0;                                 // Total number of planes
    for (int p = 0; p < it.nplanes; p++, ++it) 
    {
        s   += sum(it.planes[0])[0];
        ss  += sum(it.planes[0])[1];
        sss += sum(it.planes[0])[2];
        n++;
    }
    cout << "Suma 1: "       << s   << endl;
    cout << "Suma 2: "       << ss  << endl;
    cout << "Suma 3: "       << sss << endl;
    cout << "Broj ravni: "   << n   << endl;
}

void access::naryiterator()
{
    const int n_mat_size = 5;
    const int n_mat_sz[] = { n_mat_size, n_mat_size };
    cv::Mat n_mat0( 2, n_mat_sz, CV_32FC3 );
    cv::Mat n_mat1( 2, n_mat_sz, CV_32FC3 );

    cv::RNG rng;
    rng.fill( n_mat0, cv::RNG::UNIFORM, 0.f, 1.f );
    rng.fill( n_mat1, cv::RNG::UNIFORM, 0.f, 1.f );

    const cv::Mat* arrays[] = { &n_mat0, &n_mat1, 0 };
    cv::Mat my_planes[2];
    cv::NAryMatIterator it( arrays, my_planes );
    cout << "it size: "    << it.size    << endl;
    cout << "it.nplanes: " << it.nplanes << endl;

    float s = 0.f;                    // Total sum over all planes in both arrays
    int   n = 0;                      // Total number of planes
    for(int p = 0; p < it.nplanes; p++, ++it) 
    {
        //cout << "Plane: " << it.planes[0] << endl;
        cout << sum(it.planes[0]) << endl;
        cout << sum(it.planes[1]) << endl;
        s += cv::sum(it.planes[0])[0];
        s += cv::sum(it.planes[1])[0];
        n++;
    }
    cout << "Number of iterations: " << n << endl;
    cout << "Sum: " << s << endl;
}