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
        virtual string getColor() const = 0;
        virtual string value() const = 0;
        virtual string multiplier() const = 0;
        virtual string tolerance() const = 0;

        bool operator==( const Color& clr2 )
        {
            string color1 = this->getColor();
            string color2 = clr2.getColor();
            if ( color1.compare(color2) == 0 ) return true;
            return false;
        }
        bool operator!=( const Color& clr2 )
        {
            string color1 = this->getColor();
            string color2 = clr2.getColor();
            if ( color1.compare(color2) == 0 ) return false;
            return true;
        }
    };

    struct RBackground: Color
    {
        Scalar *up = new Scalar(18, 130, 255);
        Scalar *down = new Scalar(13, 70, 169);
        
        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }
        string getColor() const override { return colorname; }
        string value() const override { return "N"; }
        string multiplier() const override { return "N"; }
        string tolerance() const override { return "N"; }

        ~RBackground() { delete up, delete down;}
        private:
        string colorname = "Pozadina";
    };

    struct ROrange: Color
    {
        Scalar *up = new Scalar(12,240,191);
        Scalar *down = new Scalar(12,179,170);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }
        string getColor() const override { return colorname; }
        string value() const override { return "3"; }
        string multiplier() const override { return "x1000"; }
        string tolerance() const override { return "+/-3%"; }

        ~ROrange() { delete up, delete down;}
        private:
        string colorname = "Narandzasta";
    };

    struct RRed: Color
    {
        Scalar *up = new Scalar(4,230,255);
        Scalar *down = new Scalar(1,160,123);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }
        string getColor() const override { return colorname; }
        string value() const override { return "2"; }
        string multiplier() const override { return "x100"; }
        string tolerance() const override { return "+/-2%"; }

        ~RRed() { delete up, delete down;}
        private:
        string colorname = "Crvena";
    };

    struct RBrown: Color
    {
        Scalar *up = new Scalar(13,255,226);
        Scalar *down = new Scalar(7,64,71);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }
        string getColor() const override { return colorname; }
        string value() const override { return "1"; }
        string multiplier() const override { return "x10"; }
        string tolerance() const override { return "+/-1%"; }

        ~RBrown() { delete up, delete down;}
        private:
        string colorname = "Braon";
    };

    struct RGold: Color
    {
        Scalar *up = new Scalar(18,220,168);
        Scalar *down = new Scalar(13,146,96);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }
        string getColor() const override { return colorname; }
        string value() const override { return ""; }
        string multiplier() const override { return "x0.1"; }
        string tolerance() const override { return "+/-5%"; }

        ~RGold() { delete up, delete down;}
        private:
        string colorname = "Zlatna";
    };

    struct RBlack: Color
    {
        Scalar *up = new Scalar(13,255,55);
        Scalar *down = new Scalar(7,143,0);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }
        string getColor() const override { return colorname; }
        string value() const override { return "0"; }
        string multiplier() const override { return "x1"; }
        string tolerance() const override { return ""; }

        ~RBlack() { delete up, delete down;}
        private:
        string colorname = "Crna";
    };

    struct RYellow: Color
    {
        Scalar *up = new Scalar(23,181,220);
        Scalar *down = new Scalar(20,143,190);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }
        string getColor() const override { return colorname; }
        string value() const override { return "4"; }
        string multiplier() const override { return "x10^4"; }
        string tolerance() const override { return "+/-4%"; }

        ~RYellow() { delete up, delete down;}
        private:
        string colorname = "Zuta";
    };

    struct RGreen: Color
    {
        Scalar *up = new Scalar(66,159,195);
        Scalar *down = new Scalar(41,41,59);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }
        string getColor() const override { return colorname; }
        string value() const override { return "5"; }
        string multiplier() const override { return "x10^5"; }
        string tolerance() const override { return "+/-0.5%"; }

        ~RGreen() { delete up, delete down;}
        private:
        string colorname = "Zelena";
    };

    struct RBlue: Color
    {
        Scalar *up = new Scalar(124,180,110);
        Scalar *down = new Scalar(107,32,60);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }
        string getColor() const override { return colorname; }
        string value() const override { return "6"; }
        string multiplier() const override { return "x10^6"; }
        string tolerance() const override { return "+/-0.25%"; }

        ~RBlue() { delete up, delete down;}
        private:
        string colorname = "Plava";
    };

    struct RViolet: Color
    {
        Scalar *up = new Scalar(172,96,114);
        Scalar *down = new Scalar(143,64,85);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }
        string getColor() const override { return colorname; }
        string value() const override { return "7"; }
        string multiplier() const override { return "x10^7"; }
        string tolerance() const override { return "+/-0.1%"; }

        ~RViolet() { delete up, delete down;}
        private:
        string colorname = "Ljubicasta";
    };

    struct RGrey: Color
    {
        Scalar *up = new Scalar(14,70,122);
        Scalar *down = new Scalar(12,19,80);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }
        string getColor() const override { return colorname; }
        string value() const override { return "8"; }
        string multiplier() const override { return "x10^8"; }
        string tolerance() const override { return "+/-0.05%"; }

        ~RGrey() { delete up, delete down;}
        private:
        string colorname = "Gravo";
    };

    struct RWhite: Color
    {
        Scalar *up = new Scalar(25,75,255);
        Scalar *down = new Scalar(19,50,225);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }
        string getColor() const override { return colorname; }
        string value() const override { return "9"; }
        string multiplier() const override { return "x10^9"; }
        string tolerance() const override { return ""; }

        ~RWhite() { delete up, delete down;}
        private:
        string colorname = "Bela";
    };

    struct RSilver: Color
    {
        Scalar *up = new Scalar(15,250,80);
        Scalar *down = new Scalar(13,206,53);

        Scalar getUpColor() override { return *up; }
        Scalar getDownColor() override {return *down; }
        string getColor() const override { return colorname; }
        string value() const override { return ""; }
        string multiplier() const override { return "x0.01"; }
        string tolerance() const override { return "+/-10%"; }

        ~RSilver() { delete up, delete down;}
        private:
        string colorname = "Srebrna";
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