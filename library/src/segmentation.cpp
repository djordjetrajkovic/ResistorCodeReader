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

#include "segmentation.h" 

int segment::funct(string slika, string pozadina)
{
    Rect r(20,20, 620, 460);
    // Glavna slika  
    Mat img(imread(slika, IMREAD_GRAYSCALE), r);
    // Pozadina 
    Mat light(imread(pozadina, IMREAD_GRAYSCALE), r);
    namedWindow("Image");
    imshow("Image", img);
    //======================================
    // uklanjanje suma median filterom zbog tipa suma
    Mat img_median;
    medianBlur(img, img_median,7);
    namedWindow("Median");
    imshow("Median", img_median);
    

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
    else threshold(img_comp, img_thr, 45, 255, THRESH_BINARY_INV);
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
        dilate(img_thr, rem_small_img, kernel);
    }
    namedWindow("Remove Small Objects");
    imshow("Remove Small Objects", rem_small_img);

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
    if (contours.size() == 0) {
        cout << "Nema objekata u slici" << endl;
        return -1;
    }
    else {
        cout << "Broj detektovanih kontura: " << contours.size() << endl;
    }
        for (auto i = 0; i < contours.size(); i++) 
    {
        Scalar color = Scalar(rand() % 255, rand() % 255, rand() % 255);
        drawContours(outputContours, contours, i, color);        
    }
    namedWindow("Result_Contours");
    imshow("Result_Contours", outputContours);
    
    int key;
    while (true)
    {
        key = cv::waitKey(20);
		if (key == 27) break;
	}
    destroyAllWindows();
    return 0;

}