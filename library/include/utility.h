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

namespace opnmsp
{
    struct Color
    {
        virtual Scalar getUpColor() = 0;
        virtual Scalar getDownColor() = 0;
    };

    struct RBackground: Color
    {
        Scalar *up = new Scalar(71, 198, 126);
        Scalar *down = new Scalar(56, 103, 90);
        
        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }
    };

    struct ROrange: Color
    {
        Scalar *up = new Scalar(49,231,132);
        Scalar *down = new Scalar(45,211,130);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }
    };

        struct RRed: Color
    {
        Scalar *up = new Scalar(24,255,83);
        Scalar *down = new Scalar(10,201,74);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }
    };

        struct RBrown: Color
    {
        Scalar *up = new Scalar(25,255,40);
        Scalar *down = new Scalar(8,240,30);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }
    };

        struct RGold: Color
    {
        Scalar *up = new Scalar(64,249,70);
        Scalar *down = new Scalar(49,211,560);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }
    };


    class Utility
    {
        public:
        static Mat hsvHistogram(Mat);
        static bool isColorPresent(Color*, Mat);
        static RotatedRect findRotRect(Mat);
    };
}
#endif