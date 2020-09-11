#include <iostream>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

#include "object.h"

int objectsnmsp::AObject::oID = 0;

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
    cout << "ID: " << getID() << " ANGLE: " << angle << endl;
    if (angle > 90.) 
    {   
        angle -= 90.0;
        cout << "ANGLE + 90: " << angle << endl;
        // if (rect_size.width > rect_size.height)
        // {
        //     rect_size.height = rect_size.width;
        // }
        // else
        // {
        //     rect_size.width = rect_size.height;
        // }
        swap(rect_size.width, rect_size.height);
    }
    Mat rotMatrix = getRotationMatrix2D(rr.center, angle, 1.0);
    Mat imageAffine, cropped, rotated;
    warpAffine(image, imageAffine, rotMatrix, image.size(), INTER_CUBIC);
    //rect_size.height = (rect_size.width > rect_size.height)? rect_size.width:rect_size.height;
    getRectSubPix(imageAffine, rect_size, rr.center, cropped);
    //rotated = opnmsp::Utility::rotate(cropped, 90);
    
    int randoms = rand()*1000;
    stringstream ss, pp, qq; 
    ss << "RANDOM___"   << randoms;
    pp << "RANDOM+1___" << randoms; 
    qq << "RANDOM+2___" << randoms;
    namedWindow(ss.str(),WINDOW_NORMAL); imshow(ss.str(), imageAffine);
    namedWindow(pp.str(),WINDOW_NORMAL); imshow(pp.str(), cropped);
    namedWindow(qq.str(),WINDOW_NORMAL); imshow(qq.str(), image);
    // Pronalazi boje
    vector<opnmsp::Color*> RColors = 
    { 
        new opnmsp::ROrange,
        new opnmsp::RRed,
        new opnmsp::RBrown,
        new opnmsp::RGold,
        new opnmsp::RBlue,
        new opnmsp::RGrey,
        new opnmsp::RBlack,
        new opnmsp::RViolet,
        new opnmsp::RGreen
    };
    opnmsp::Color *RBColor = new opnmsp::RBackground;
    int i = 0;
    while ( ++i < cropped.cols )
    {
        Rect roi(i, 0, 1, cropped.rows);
        Mat section(cropped(roi));
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
    // izvrni ako je tolerancija prva
    opnmsp::Color *RGold = new opnmsp::RGold;
    if ( !ringcolors.empty() && *ringcolors.at(0) == *RGold )
    {
        deque<opnmsp::Color*> ringcolors_copy(ringcolors);
        deque<opnmsp::Color*>::reverse_iterator rit = ringcolors_copy.rbegin(); 
        deque<opnmsp::Color*>::reverse_iterator rend = ringcolors_copy.rend();
        ringcolors.clear();
        while ( rit != rend)
        {
            ringcolors.push_back(*rit);
            rit++;
        }
    } 
}

void objectsnmsp::Resistor::getDescription(ostream& out)
{
    int numofrings = ringcolors.size();
    //out << "Num. of Rings: " << numofrings;
    if (numofrings == 0) { out << "No rings detected."; return; }
    switch (numofrings)
    {
        case 3:
            out << "(3B)";
            for (int i = 0; i < numofrings - 1; i++ )
            {
                out << ringcolors.at(i)->value();
            }
            out << ringcolors.at(numofrings - 1)->multiplier();
            break;
        case 4:
            out << "(4B)";
            for (int i = 0; i < numofrings - 2; i++ )
            {
                out << ringcolors.at(i)->value();
            }
            out << ringcolors.at(numofrings - 2)->multiplier();
            out << " To:";
            out << ringcolors.at(numofrings - 1)->tolerance();
            break;
        case 5:
            out << "(5B)";
            for (int i = 0; i < numofrings - 2; i++ )
            {
                out << ringcolors.at(i)->value();
            }
            out << ringcolors.at(numofrings - 2)->multiplier();
            out << " To:";
            out << ringcolors.at(numofrings - 1)->tolerance();
            break;
        default:
            out << "No colors detected." << endl;
            break;
    }
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
    id = ++oID;
    auto it = resistor.ringcolors.begin();
    auto end = resistor.ringcolors.end();
    while ( it != end)
    {
        ringcolors.push_back(*it);
        it++;
    }
}

void objectsnmsp::Resistor::mov(Resistor& resistor)
{
    id = ++oID;
    ringcolors = resistor.ringcolors;
}

objectsnmsp::Resistor::~Resistor()
{
    for (auto& ringcolor: ringcolors)
    {
       // delete ringcolor;
    }
    ringcolors.clear();
    detectedColors.clear();
}