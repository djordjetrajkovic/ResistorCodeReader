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

int segment::funct(string slika, string pozadina)
{
    Rect r(300,300, 900, 1200);
    // Glavna slika  
    Mat img(imread(slika, IMREAD_GRAYSCALE), r);
    // Pozadina 
    Mat light(imread(pozadina, IMREAD_GRAYSCALE), r);
    // namedWindow("Image");
    // imshow("Image", img);
    //======================================
    // uklanjanje suma median filterom zbog tipa suma
    Mat img_median;
    medianBlur(img, img_median,7);
    namedWindow("Median");
    imshow("Median", img_median);

    vector<vector<Point>> konture;
    vector<Rect> rectangles;
    //contourSearch(img_median, konture, rectangles, true);
    
    //======================================
    // kompenzacija neuniformnog osvetljenja
    Mat img_comp;
    int comp_light = 1;  // <------- kontrola
    if (comp_light == 1) img_comp = light - img_median;
    else
    {
        Mat img_median32, light32, img_comp32;
        img_median.convertTo(img_median32, CV_32F);
        light.convertTo(light32, CV_32F);
        img_comp32 = 255 * (1 - img_median32 / light32);
        img_comp32.convertTo(img_comp, CV_8U);
    }
    
    namedWindow("Compensated");
    imshow("Compensated", img_comp);
    
    //======================================
    // Primena praga - threshold
    Mat img_thr;
    int method_light = 1; // <------- kontrola
    if (method_light != 2) threshold(img_comp, img_thr, 24, 255, THRESH_BINARY);
    else threshold(img_comp, img_thr, 55, 255, THRESH_BINARY_INV);
    namedWindow("Threshold");
    imshow("Threshold", img_thr);

    //=====================================
    // uklanjanje malih objekata
    Mat rem_small_img;
    int remove_small = 1;
    if (remove_small == 1)
    {
        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        erode(img_thr, rem_small_img, kernel);
        //dilate(img_thr, rem_small_img, kernel);
    }
    namedWindow("Remove Small Objects");
    imshow("Remove Small Objects", rem_small_img);
    contourSearch(rem_small_img, konture, rectangles, true); // !!!!!!!!!
    Mat uzorak = imread("template.jpg", IMREAD_GRAYSCALE);
    for (auto rect: rectangles)
    {
        Mat slika = rem_small_img(rect);
        Ptr<ShapeContextDistanceExtractor> mysc = createShapeContextDistanceExtractor();
        vector<Point> c1 = sampleContour(slika);
        vector<Point> c2 = sampleContour(uzorak);
        float dis;
        if (!c1.empty() && !c2.empty()) dis = mysc ->computeDistance(c1, c2);
        cout << "Kontura: " << rect.area() << ", "<< "Shape context distance: " << dis << endl;
    }
    
    
    
    
    
    //======================================
    // Odredjivanje svih piksela koji pripadaju istom objektu
    Mat labels, stats, centroids;
    auto num_objects = connectedComponentsWithStats(rem_small_img, labels, stats, centroids);
        if (num_objects < 2) 
    {
        cout << "Nema objekata u slici" << endl;
        return -1;
    }
    else
    {
        cout << "Broj detektovanih objekata: " << num_objects - 1 << endl;
    }
    
    // slika za prikaz detektovanih izolovanih objekata u raznim bojama
    Mat outputLabels = Mat::zeros(img.rows, img.cols, CV_8UC3);
    labels.convertTo(labels, CV_16U); // konverzija u drugi tip pixela OBAVEZNO
    centroids.convertTo(centroids, CV_16U); // konverzija u drugi tip pixela OBAVEZNO
    for (auto i = 1; i < num_objects; i++)
    {
        // ispisivanje lokacije centra mase objekta i povrsine
        cout << "Objekat " << i << " na poziciji: (" << centroids.at<short>(i,0) << ", " << centroids.at<short>(i,1) << ") sa povrsinom " << stats.at<int>(i, CC_STAT_AREA) << "." << endl;

        Mat mask = labels == i;
        Scalar color = Scalar(rand()%255, rand()%255, rand()%255);
        outputLabels.setTo(color, mask);
        // ispisuje se tekst sa povrsinom za i-ti objekat 
        stringstream ss;
        ss << "Povrsina :" << stats.at<int>(i, CC_STAT_AREA);
        putText(outputLabels, ss.str(), Point2d(centroids.at<short>(i, 0)-20, centroids.at<short>(i, 1)), 
            FONT_HERSHEY_SIMPLEX, 0.5 ,Scalar(255, 255, 255));
    }
    namedWindow("Result_Labels");
    imshow("Result_Labels", outputLabels);
    
    // vektor sa koordinatama konture
    vector<vector<Point>> contours;
    findContours(rem_small_img, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    Mat outputContours = Mat::zeros(img.rows, img.cols, CV_8UC3);
    vector<Moments> mom(contours.size());
    
    if (contours.size() == 0) {
        cout << "Nema objekata u slici" << endl;
        return -1;
    }
    else 
    {
        cout << "Broj detektovanih kontura: " << contours.size() << endl;
        //drawContours(outputContours, contours, 20, Scalar(255,255,255,0));
        for (auto i = 0; i < contours.size(); i++) 
        {
            Scalar color = Scalar(rand() % 255, rand() % 255, rand() % 255);
            double matching = matchShapes(contours[20], contours[i], CONTOURS_MATCH_I3, 0);
            if (matching < 3 && matching >= 0 ) 
            {
                drawContours(outputContours, contours, i, color);
                mom[i]= moments(contours[i], false);
                //cout << "Moment konture " << i << ": " << mom[i].m00 << endl;
                //cout << "Broj konture: " << i << ", Poklapanje: " << matching ;
                //cout << ", Boja konture: " << color << ", Povrsine: " << contours[i].size() << endl;
                vector<double> hh;
                HuMoments(mom[i], hh);
               
                //for (int j=0 ; j < 7; cout << hh[j++] << endl);

                //cout << "Poklapanje konture " << i << ": " << matchShapes(contours[19], contours[i], CONTOURS_MATCH_I1, 0) << endl;
            }
        }
        
    }
        
    for(auto rect: rectangles)
    {
        Scalar color = Scalar(rand() % 255,rand() % 255,rand() % 255);
        rectangle(outputContours, rect, color, 1);
        rectangle(img, rect, color, 1);
        stringstream ss;
        ss << "Povrsina :" << rect.area();
        putText(img, ss.str(), Point2d(rect.x, rect.y), FONT_HERSHEY_SIMPLEX, 0.5 ,Scalar(255, 255, 255));
    }
    namedWindow("Result_Contours");
    imshow("Result_Contours", outputContours);
    namedWindow("Image");
    imshow("Image", img);
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
    //if (temple.data) temple = inputimage(Rect(705,513,90,70));
    //imwrite("template.jpg", temple);
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