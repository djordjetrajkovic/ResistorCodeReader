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
    RotatedRect rr = object->getRotRect();
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
    

}

void objectsnmsp::Resistor::getDescription(ostream& out)
{
    out << "Resistor value by colors";
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
    resistorColor = resistor.resistorColor;
    rone = resistor.rone;
    rtwo = resistor.rtwo;
    rthree = resistor.rthree;
    rfour = resistor.rfour;
    rfive = resistor.rfive;
}

void objectsnmsp::Resistor::mov(Resistor& resistor)
{
    resistorColor = resistor.resistorColor;
    rone = resistor.rone;
    rtwo = resistor.rtwo;
    rthree = resistor.rthree;
    rfour = resistor.rfour;
    rfive = resistor.rfive;
}