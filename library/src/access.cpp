#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <ostream>
#include <access.h>
using namespace std;

int opnmsp::AFind::uID = 0;

void opnmsp::FindByTemplate::findObjects()
{
    Mat img_isolated = segment();
    for (auto sample: samples)
    {
        vector<vector<Point>>* contours = searchByTemplate(img_isolated, sample);
        for(auto contour: *contours)
        {
            auto rect = boundingRect(contour);
            rect.x += (int)(sample->getImagePatternGrayscale().cols/2);
            rect.y += (int)(sample->getImagePatternGrayscale().rows/2);
            rect.width *= 1.2;
            rect.height *= 1.2;
            //Mat image_grayscale;
            //cvtColor(image, image_grayscale, COLOR_BGR2GRAY);
            Mat image_of_interest = img_isolated(rect);
            searchByContour(image_of_interest, sample->getImagePatternBinary(), sample, rect);
        }
    }
    
}

Mat opnmsp::FindByTemplate::segment()
{
    bool show = false;
    if (show) { namedWindow("Original Image"); imshow("Original Image", image); }
    // convert to grayscale
    Mat image_grayscale, bckg_grayscale;
    cvtColor(image, image_grayscale, COLOR_BGR2GRAY);
    cvtColor(background, bckg_grayscale, COLOR_BGR2GRAY);
    
    // Median filter applying
    Mat img_median, bck_median;
    medianBlur(image_grayscale, img_median, 7);
    medianBlur(bckg_grayscale, bck_median, 7);
    if (show) { namedWindow("Median"); imshow("Median", img_median); }

    // Background subst
    Mat img_comp;
    img_comp = bck_median - img_median;
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
    }
    else
    {
        cout << "Detected objects num: " << num_objects - 1 << endl;
    }
    
    Mat img_isolated = Mat::zeros(image.rows, image.cols, CV_8UC1);
    labels.convertTo(labels, CV_16U);
    centroids.convertTo(centroids, CV_16U);
    for (auto i = 1; i < num_objects; i++)
    {
        // ispisivanje lokacije centra mase objekta i povrsine
        //cout << "Object " << i << " onto position: (" << centroids.at<short>(i,0) << ", " << centroids.at<short>(i,1) << "), with area: " << stats.at<int>(i, CC_STAT_AREA) << "." << endl;
        Mat mask = labels == i;
        Scalar color = Scalar(255);
        img_isolated.setTo(color, mask);
    }
    if (show) { namedWindow("Isolated objects"); imshow("Isolated objects", img_isolated); }
    return img_isolated;
}

vector<vector<Point>>* opnmsp::FindByTemplate::searchByTemplate(Mat img_isolated, objectsnmsp::AObject* sample)
{
    bool show = false;

    Mat ftmp[6];
    //if (show) { namedWindow("PATTERN"); imshow("PATTERN", sample->getImagePatternBinary()); }
    // for (int i=0; i<6; ++i)
    // {
    //     matchTemplate(img_isolated, sample->getImagePatternBinary(), ftmp[i], i);
    //     normalize(ftmp[i], ftmp[i], 1, 0, NORM_MINMAX);
    // }
    matchTemplate(img_isolated, sample->getImagePatternBinary(), ftmp[4], 4);
    normalize(ftmp[4], ftmp[4], 1, 0, NORM_MINMAX);
    //if (show) { namedWindow("SQDIFF"); imshow( "SQDIFF", ftmp[0] ); }
    //if (show) { namedWindow("SQDIFF_NORMED"); imshow( "SQDIFF_NORMED", ftmp[1] ); }
    //if (show) { namedWindow("CCORR"); imshow( "CCORR", ftmp[2] ); }
    //if (show) { namedWindow("CCORR_NORMED"); imshow( "CCORR_NORMED", ftmp[3] ); }
    if (show) { namedWindow("CCOEFF"); imshow( "CCOEFF", ftmp[4] ); }
    //if (show) { namedWindow("CCOEFF_NORMED"); imshow( "CCOEFF_NORMED", ftmp[5] ); }
    
    Mat img_thrld;
    threshold(ftmp[4], img_thrld, 0.5, 1, THRESH_BINARY);
    if (show) { namedWindow("Thresh image"); imshow("Thresh image", img_thrld); }

    Mat img_rem_small;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(img_thrld, img_rem_small, kernel, Point(-1,-1), 1);
    //morphologyEx(img_thrld, rem_small_img, MORPH_CLOSE,kernel);
    if (show) { namedWindow("DILATE"); imshow("DILATE", img_rem_small); }

    img_rem_small.convertTo(img_rem_small, CV_8UC1, 255.0);
    vector<vector<Point>>* contours = new vector<vector<Point>>();
    findContours(img_rem_small, *contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    Mat outputContours(img_rem_small.rows, img_rem_small.cols, img_rem_small.type());
    
    drawContours(outputContours, *contours, -1, Scalar(125));
    if (show) { namedWindow("KONTURE", WINDOW_NORMAL); imshow("KONTURE", outputContours); }
    return contours;
}

void opnmsp::FindByTemplate::searchByContour(Mat& image_contour, Mat temple, objectsnmsp::AObject* sample, Rect rect)
{
    //int broj = (int)(rand() % 100);
    //stringstream ss; ss << broj ;
    //namedWindow(ss.str()); imshow(ss.str(), image_contour);

    vector<vector<Point>> templateBinaryContours;
    findContours(temple, templateBinaryContours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    vector<Point> c2 = templateBinaryContours.at(0);
    
    // Shape Context Distance Extractor
    float dis = 0;
    Ptr<ShapeContextDistanceExtractor> mysc = createShapeContextDistanceExtractor();
    vector<vector<Point>> imagecontours;
    findContours(image_contour, imagecontours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    for (auto contour: imagecontours)
    {
        vector<Point> cc = sampleContour(contour, 150);
        if (!contour.empty() && contour.size()>60) 
        {
            dis = mysc -> computeDistance(c2, cc);
            //cout << "Kontura, Shape context distance: " << dis << endl;
            if (dis < 1700  && opnmsp::Utility::isColorPresent(new RBackground(), image(rect)) ) //  && opnmsp::Utility::isColorPresent(new RBackground(), image(rect))
            {
                RotatedRect rr = fitEllipse(cc);
                objectsnmsp::AObject *newobject = sample -> clone(); // Proveri dal treba izvan petlje
                newobject->setImage(image(rect));
                newobject->setRoi(rect);
                newobject->setConture(cc);
                newobject->setRotRect(rr);
                newobject->recognize();
                objects.push_back(newobject);
            }
        }
    }
}

vector<Point> opnmsp::FindByTemplate::sampleContour(vector<Point> contour, int npoints)
{
    vector<Point>all_points;
    if (contour.empty()) return all_points;
    for (int i=0; i<contour.size(); i++)
    {
        all_points.push_back(contour[i]);
        
    }

    int dummy = 0;
    for (int add=(int)all_points.size(); add<npoints; add++)
    {
        all_points.push_back(all_points[dummy++]);
    }

    random_shuffle(all_points.begin(),all_points.end());
    vector<Point> sampled;
    for (int i=0;i<npoints;i++) sampled.push_back(all_points[i]);

    return sampled;
}

opnmsp::AFind::~AFind()
{
    for(auto object: objects) delete object;
    for(auto sample: samples) delete sample;
}

