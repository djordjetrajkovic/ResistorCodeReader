#include <iostream>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

#include "object.h"

objectsnmsp::AObject::~AObject()
{
    del();
}

void objectsnmsp::AObject::copy(const AObject& obj)
{
    image = obj.image;
    roi = obj.roi;
    contour = obj.contour;
    rotrectangle = obj.rotrectangle;
    name = obj.name;
    category = obj.category;
    type = obj.type;
    
}

void objectsnmsp::AObject::mov(AObject& obj)
{
    image = obj.image;
    roi = obj.roi;
    contour = obj.contour;
    rotrectangle = obj.rotrectangle;
    name = obj.name;
    category = obj.category;
    type = obj.type;
}

void objectsnmsp::AObject::del()
{
    //for (auto &cont: contour) delete &cont;
    contour.clear();
}

objectsnmsp::Electronics::~Electronics()
{
    
}

void objectsnmsp::Resistor::recognize()
{
    // Rotira i kropuje 
    RotatedRect rr = getRotRect();
    float angle = rr.angle;
    Size rect_size = rr.size;
    if (rr.angle > -45.) 
    {
        angle += 90.0;
        swap(rect_size.width, rect_size.height);
    }
    Mat rotMatrix = getRotationMatrix2D(rr.center, angle, 1.0);
    Mat imageAffine, cropped;
    warpAffine(image, imageAffine, rotMatrix, image.size(), INTER_CUBIC);
    getRectSubPix(imageAffine, rect_size, rr.center, cropped);

    // Pronalazi boje
    vector<opnmsp::Color*> RColors = 
    { 
        new opnmsp::ROrange,
        new opnmsp::RRed,
        new opnmsp::RBrown,
        new opnmsp::RGold
    };
    opnmsp::Color *RBColor = new opnmsp::RBackground;
    list<opnmsp::Color*> detectedColors;
    int i = 0;
    while ( ++i < image.cols )
    {
        Rect roi(i, 0, 1, image.rows);
        Mat section(image(roi));
        vector<opnmsp::Color*> pColors = opnmsp::Utility::presentColors(RColors, section);
        if ( pColors.size() == 1)
        {
            detectedColors.push_back(pColors.at(0));
            continue;
        }
        if ( pColors.size() > 1)
        {
            continue;
        }
        if( opnmsp::Utility::isColorPresent(RBColor, section))
        {
            detectedColors.push_back(RBColor);
        }
    }
    detectedColors.unique();
    // prepisivanje u ringcolors
    list<opnmsp::Color*>::iterator it = detectedColors.begin(); 
    list<opnmsp::Color*>::iterator end = detectedColors.end();
    while (it != end)
    {
        if ( (*(*it)) != *RBColor ) ringcolors.push_back(*it);
        it++;
    }
    // izzvrni ako je tolerancija prva
    
}

void objectsnmsp::Resistor::getDescription(ostream& out)
{
    int numofrings = ringcolors.size();
    if (numofrings == 0) { out << "No rings detected."; return; }
    // out << "Num. of Rings: " << numofrings;
    // list<opnmsp::Color*>::iterator it = ringcolors.begin(); 
    // list<opnmsp::Color*>::iterator end = ringcolors.end();
    // while (it != -- --end)
    // {
    //    out << (*(*it)).value();
    //    it++;
    // }
    // out << (*(*(--it))).multiplier();
    // out << " T:";
    // out << (*(*(it))).tolerance();
}

objectsnmsp::Resistor::Resistor(const Resistor& resistor):Electronics(resistor)
{
    copy(resistor);
}

objectsnmsp::Resistor::Resistor(Resistor&& resistor):Electronics(resistor)
{
    mov(resistor);
}

void objectsnmsp::Resistor::copy(const Resistor& resistor)
{
 // Dovrsi
}

void objectsnmsp::Resistor::mov(Resistor& resistor)
{
 // Dovrsi
}