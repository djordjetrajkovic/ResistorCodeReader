#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

#include <input.h>

panmsp::ACommand::~ACommand(){}

panmsp::ALoadImage::~ALoadImage(){}

void panmsp::File::openImageFile()
{
    Mat image(imread(imagepath), roi);
    operation->setImage(image);
}

void panmsp::File::openBckgFile()
{
    Mat background(imread(backgroundgpath), roi);
    operation->setBackground(background);
}

void panmsp::File::execute()
{
    openImageFile();
    openBckgFile();
}

void panmsp::Folder::openBckgFile()
{
    Mat background(imread(backgroundgpath), roi);
    operation->setBackground(background);
}

void panmsp::Folder::execute()
{
    Mat image(fullimage, roi);
    operation->setImage(image);
    openBckgFile();
}


void panmsp::LoadSamples::prepObjectsTemplates()
{
    // Load template grayscale
    Mat templategrayscale = imread(templgraypath, IMREAD_GRAYSCALE);

    // Load template binary
    Mat templatebinary = imread(templbinpath, IMREAD_GRAYSCALE);
    threshold(templatebinary, templatebinary, 120, 255, cv::THRESH_BINARY);

    objectsnmsp::AObject *resistorsample = new objectsnmsp::Resistor();
    resistorsample->setImagePatternGrayscale(templategrayscale);
    resistorsample->setImagePatternBinary(templatebinary);

    vector<objectsnmsp::AObject*> samples;
    samples.push_back(resistorsample);
    operation->setSamples(samples);
}

void panmsp::LoadSamples::execute()
{
    prepObjectsTemplates();
}

void panmsp::FindObjects::find()
{
    operation->findObjects();
}

void panmsp::FindObjects::execute()
{
    find();
}

void panmsp::DisplayResult::show()
{
    for (auto object: operation->getObjects()) 
    {
        Mat image = (object -> getImage()).clone();
        int broj = (int)(rand() % 10000);
        stringstream ss; ss << broj ;
        
        
        Point2f vertices[4];
        object->getRotRect().points(vertices);
        for (int i = 0; i < 4; i++) line(image, vertices[i], vertices[(i+1)%4], Scalar(0,0,0), 1);
        //Rect brect = object->getRotRect().boundingRect();
        //rectangle(image, brect, Scalar(0,0,255), 1);
        
        //namedWindow(ss.str(), WINDOW_NORMAL); imshow(ss.str(), image);
        
        
        if (object != nullptr) cout << *object << endl;

        /// PROBA
        // RotatedRect rr = object->getRotRect();
        // float angle = rr.angle;
        // Size rect_size = rr.size;
        // if (rr.angle > -45.) {
        //     angle += 90.0;
        //     swap(rect_size.width, rect_size.height);
        // }
        // Mat rotMatrix = getRotationMatrix2D(rr.center, angle, 1.0);
        // Mat imageAffine, cropped;
        // warpAffine(image, imageAffine, rotMatrix, image.size(), INTER_CUBIC);
        // getRectSubPix(imageAffine, rect_size, rr.center, cropped);
        // cout << "Angle: " << rr.angle << endl;
        // ss << "_affine";
        // namedWindow(ss.str(), WINDOW_NORMAL); imshow(ss.str(), cropped);
        ////
    }
}

void panmsp::DisplayResult::execute()
{
    show();
}

void panmsp::SingleImage::start()
{
    string resistorgrayscalepattern = "samples/templates/grayscale/template_grayscale.jpg";
    string resistorbinarypattern = "samples/templates/binary/template.jpg";

    Rect r (300, 300, 900, 1200);

    opnmsp::AFind    *operation = new opnmsp::FindByTemplate();
    panmsp::ACommand *fromfile = new panmsp::File(operation, r, imagepath, backgroundpath);
    panmsp::ACommand *loadsamples = new panmsp::LoadSamples(operation, resistorgrayscalepattern, resistorbinarypattern);
    panmsp::ACommand *findobjects = new panmsp::FindObjects(operation);
    panmsp::ACommand *displayresults = new panmsp::DisplayResult(operation);

    panmsp::Composite *composite = new panmsp::Composite();
    composite -> add(fromfile);
    composite -> add(loadsamples);
    composite -> add(findobjects);
    composite -> add(displayresults);

    // start from here
    composite -> execute();
    delete operation;
    delete composite;
}

void panmsp::MultipleImages::start()
{
    string resistorgrayscalepattern = "samples/templates/grayscale/template_grayscale.jpg";
    string resistorbinarypattern = "samples/templates/binary/template.jpg";

    Rect r (300, 300, 900, 1200);

    VideoCapture images;
    if (images.open(folderpath) == false)
    {
        cout << "Folder path unavailable.";
        throw new Exception();
    }
    Mat frame;
    opnmsp::AFind *operation;
    panmsp::Composite *composite;
    while(images.read(frame))
    {
        operation = new opnmsp::FindByTemplate();
        panmsp::ACommand *fromfolder = new panmsp::Folder(operation, r, frame, backgroundpath);
        panmsp::ACommand *loadsamples = new panmsp::LoadSamples(operation, resistorgrayscalepattern, resistorbinarypattern);
        panmsp::ACommand *findobjects = new panmsp::FindObjects(operation);
        panmsp::ACommand *displayresults = new panmsp::DisplayResult(operation);

        composite = new panmsp::Composite();
        composite -> add(fromfolder);
        composite -> add(loadsamples);
        composite -> add(findobjects);
        composite -> add(displayresults);
    }
        // start from here
        composite -> execute();
        delete operation;
        delete composite;
    
}

void panmsp::Starter::execute()
{
    start();
}

void panmsp::Starter::start()
{

}

panmsp::Starter::~Starter() {}

void panmsp::Composite::execute()
{
    for (auto op: operations) op -> execute();
}


panmsp::Composite::~Composite()
{
    for (auto& operation: operations) delete operation;
}