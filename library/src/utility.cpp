#include <utility.h>

Mat opnmsp::Utility::hsvHistogram(Mat image)
{
    Mat img_hsv, histogram;
    cvtColor( image, img_hsv, COLOR_BGR2HSV);
    int h_bins = 256; 
    int s_bins = 180;
    int v_bins = 256;
    int histSize[] = { h_bins, s_bins, v_bins };

    float h_ranges[] = { 0, 180 };
    float s_ranges[] = { 0, 256 };
    float v_ranges[] = { 0, 256 };

    const float* ranges[] = { h_ranges, s_ranges, v_ranges };
    int channels[] = { 0, 1, 2};
    calcHist( &img_hsv, 1, channels, Mat(), histogram, 3, histSize, ranges, true, false );
    
    return histogram;
}

bool opnmsp::Utility::isColorPresent(Color* color, Mat image)
{
    Mat imgThreshold, image_hsv;
    cvtColor(image, image_hsv, COLOR_BGR2HSV);
    inRange(image_hsv, color->getDownColor(), color->getUpColor(), imgThreshold);
    
    Scalar suma = sum(imgThreshold);
    if ( suma[0] > 0) return true;
    return false;
}

vector<opnmsp::Color*> opnmsp::Utility::presentColors(vector<opnmsp::Color*> colors, Mat image)
{
    vector<opnmsp::Color*> presentcols;
    for (auto color: colors)
    {
        if ( opnmsp::Utility::isColorPresent(color, image)) presentcols.push_back(color);
    }
    return presentcols;
}

RotatedRect opnmsp::Utility::findRotRect(Mat sample)
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

Mat opnmsp::Utility::rotate(Mat src, double angle)
{
    Mat dst;
    Point2f pt(src.cols/2., src.rows/2.);    
    Mat r = getRotationMatrix2D(pt, angle, 1.0);
    warpAffine(src, dst, r, Size(src.cols, src.rows));
    return dst;
}