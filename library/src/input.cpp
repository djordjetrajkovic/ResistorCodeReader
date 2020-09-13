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

//////////////////////////////////////////////////////
// DisplayResult
//////////////////////////////////////////////////////
void panmsp::DisplayResult::show()
{
    auto objects = operation->getObjects();
    for (auto object: objects) 
    {
        if (object != nullptr) 
        {
            cout << "(ID:" << object->getID() << ")" <<object->getCategory() << ":" <<object->getType() << ":" << *object << endl;
        }
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

    Rect r (x, y, width, height);

    opnmsp::AFind    *operation = new opnmsp::FindByTemplate();
    panmsp::ACommand *fromfile = new panmsp::File(operation, r, imagepath, backgroundpath);
    panmsp::ACommand *loadsamples = new panmsp::LoadSamples(operation, resistorgrayscalepattern, resistorbinarypattern);
    panmsp::ACommand *findobjects = new panmsp::FindObjects(operation);
    panmsp::ACommand *displayresults = new panmsp::DisplayResult(operation);
    panmsp::ACommand *displayimage = new panmsp::DisplayImage(operation);
    panmsp::ACommand *displayobjects = new panmsp::DisplayObjects(operation);

    panmsp::Composite *composite = new panmsp::Composite();
    composite -> add(fromfile);
    composite -> add(loadsamples);
    composite -> add(findobjects);
    composite -> add(displayresults);
    //composite -> add(displayobjects);
    composite -> add(displayimage);

    // start from here
    composite -> execute();
    delete operation;
    delete composite;
}

void panmsp::MultipleImages::start()
{
    string resistorgrayscalepattern = "samples/templates/grayscale/template_grayscale.jpg";
    string resistorbinarypattern = "samples/templates/binary/template.jpg";

    Rect r (x, y, width, height);

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
        panmsp::ACommand *displayimage = new panmsp::DisplayImage(operation);

        composite = new panmsp::Composite();
        composite -> add(fromfolder);
        composite -> add(loadsamples);
        composite -> add(findobjects);
        composite -> add(displayresults);
        composite -> add(displayimage);
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

//////////////////////////////////////////////////////
// DisplayImage
//////////////////////////////////////////////////////
void panmsp::DisplayImage::execute()
{
    show();
}

void panmsp::DisplayImage::show()
{
    auto objects = operation->getObjects();
    Mat singleobject = (operation->getImage()).clone();
    for (auto object: objects) 
    {   
        stringstream text, id;
        // Crveni pravougaonik
        Rect rec = object->getRoi();
        rectangle(singleobject, rec, Scalar(0,0,255), 1);

        // Crni prav.
        Point2f vertices[4];
        object->getRotRect().points(vertices);
        for (int i = 0; i<4; i++) { vertices[i].x += rec.x; vertices[i].y += rec.y;}
        for (int i = 0; i < 4; i++) line(singleobject, vertices[i], vertices[(i+1)%4], Scalar(0,0,0), 1);
        id << object->getID();
        putText(singleobject, id.str(), vertices[0], FONT_HERSHEY_SIMPLEX,0.4, Scalar(0,0,0));
    }
    int recognizedobjs = objects.size();
    stringstream ss; ss << "Recognized_objects No." << recognizedobjs;
    string headline = ss.str(); 
    namedWindow(headline, WINDOW_NORMAL); imshow(headline, singleobject);
}

//////////////////////////////////////////////////////
// Display Objects
//////////////////////////////////////////////////////
void panmsp::DisplayObjects::execute()
{
    show();
}

void panmsp::DisplayObjects::show()
{
    auto objects = operation -> getObjects();
    for (auto object: objects) 
    {   
        Mat singleobject = (object -> getImage()).clone();
        Point2f vertices[4];
        object->getRotRect().points(vertices);
        for (int i = 0; i < 4; i++) line(singleobject, vertices[i], vertices[(i+1)%4], Scalar(0,0,0), 1);
        stringstream ss; ss << "ID_" << object -> getID() ;
        namedWindow(ss.str(), WINDOW_NORMAL); imshow(ss.str(), singleobject);
    }
}