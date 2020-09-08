#ifndef _utility_h_
#define _utility_h_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;


namespace opnmsp
{
    struct Color
    {
        virtual Scalar getUpColor() = 0;
        virtual Scalar getDownColor() = 0;

        virtual string value() const = 0;
        virtual string multiplier() const = 0;
        virtual string tolerance() const = 0;

        bool operator==( const Color& clr2 )
        {
            string color1 = this->value();
            string color2 = clr2.value();
            if ( color1.compare(color2) == 0 ) return true;
            return false;
        }
        bool operator!=( const Color& clr2 )
        {
            string color1 = this->value();
            string color2 = clr2.value();
            if ( color1.compare(color2) == 0 ) return false;
            return true;
        }
    };

    struct RBackground: Color
    {
        Scalar *up = new Scalar(71, 198, 126);
        Scalar *down = new Scalar(56, 103, 90);
        
        

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }

        string value() const override { return "N"; }
        string multiplier() const override { return "N"; }
        string tolerance() const override { return "N"; }
    };

    struct ROrange: Color
    {
        Scalar *up = new Scalar(49,231,132);
        Scalar *down = new Scalar(45,211,130);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }

        string value() const override { return "3"; }
        string multiplier() const override { return "x1000"; }
        string tolerance() const override { return "+/-3%"; }
    };

    struct RRed: Color
    {
        Scalar *up = new Scalar(24,255,83);
        Scalar *down = new Scalar(10,201,74);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }

        string value() const override { return "2"; }
        string multiplier() const override { return "x100"; }
        string tolerance() const override { return "+/-2%"; }
    };

    struct RBrown: Color
    {
        Scalar *up = new Scalar(25,255,40);
        Scalar *down = new Scalar(8,240,30);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }

        string value() const override { return "1"; }
        string multiplier() const override { return "x10"; }
        string tolerance() const override { return "+/-1%"; }
    };

    struct RGold: Color
    {
        Scalar *up = new Scalar(64,249,70);
        Scalar *down = new Scalar(49,211,560);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }

        string value() const override { return ""; }
        string multiplier() const override { return "x0.1"; }
        string tolerance() const override { return "+/-5%"; }
    };


    class Utility
    {
        public:
        static Mat hsvHistogram(Mat);
        static bool isColorPresent(Color*, Mat);
        static vector<Color*> presentColors(vector<Color*>, Mat);
        static RotatedRect findRotRect(Mat);
    };
}

#endif