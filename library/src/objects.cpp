#include <iostream>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

#include "object.h"

objectsnmsp::Object::~Object()
{
    del();
}

void objectsnmsp::Object::copy(const Object& obj)
{
    image = obj.image;
    roi = obj.roi;
    contour = obj.contour;
    rotrectangle = obj.rotrectangle;
    name = obj.name;
    category = obj.category;
    type = obj.type;
}

void objectsnmsp::Object::mov(Object& obj)
{
    image = obj.image;
    roi = obj.roi;
    contour = obj.contour;
    rotrectangle = obj.rotrectangle;
    name = obj.name;
    category = obj.category;
    type = obj.type;
}

void objectsnmsp::Object::del()
{
    delete image;
    for (auto &cont: contour) delete &cont;
    contour.clear();
}

string objectsnmsp::Resistor::getDescription()
{
    return "resistor value by colors";
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