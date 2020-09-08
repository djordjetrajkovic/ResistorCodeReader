#ifndef _object_h_
#define _object_h_

#include <iostream>
#include <deque>
#include <list>
#include <vector>
#include <utility>
#include <ostream>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

#include <utility.h>

namespace objectsnmsp
{
    class AObject {
    private:
        void copy(const AObject&);
        void mov(AObject&);
        void del();
        
    protected:
        Mat image;
        Mat imagepatterngrayscale;
        Mat imagepatternbinary;
        Rect roi;
        vector<Point> contour;
        RotatedRect rotrectangle;
        string name;
        string category;
        string type;
    public:
        // konstruktori
        AObject() = default;
        AObject(const AObject& obj)
        {
            copy(obj);
        }
        AObject(AObject&& obj)
        {
            mov(obj);
        }
        virtual void recognize() = 0;
        // polimorfno kopiranje objekata
        virtual AObject* clone() const& = 0;
        virtual AObject* clone() && = 0;

        // destruktor
        virtual ~AObject() = 0;

        // metode
        void setImage(Mat img)
        {
            image = img;
        }
        Mat getImage()
        {
            return image;
        }
        
        Mat getImagePatternGrayscale()
        {
            return imagepatterngrayscale;
        }

        void setImagePatternGrayscale(Mat image)
        {
            imagepatterngrayscale = image;
        }

        Mat getImagePatternBinary()
        {
            return imagepatternbinary;
        }

        void setImagePatternBinary(Mat image)
        {
            imagepatternbinary = image;
        }

        void setRoi(Rect roi)
        {
            this->roi = roi;
        }
        Rect getRoi()
        {
            return roi;
        }

        vector<Point> getConture() 
        {
            return contour;
        }
        void setConture(vector<Point> con)
        {
            contour = con;
        }

        RotatedRect getRotRect()
        {
            return rotrectangle;
        }
        void setRotRect(RotatedRect rrect)
        {
            rotrectangle = rrect;
        }

        // virtual methods
        virtual const string getCategory() const = 0;
        virtual const string getType() const = 0;
        virtual void getDescription(ostream&) = 0;

        friend ostream & operator << (ostream &out, AObject &aobject) { aobject.getDescription(out); }
    };

    class Unknown: public AObject 
    {
        public:
        Unknown() = default;
        Unknown(const Unknown& unknwn): AObject(unknwn){}
        Unknown(Unknown&& unknwn): AObject(unknwn){}

        ~Unknown() {}
        virtual void recognize() {}
        Unknown* clone() const& override
        {
            return new Unknown(*this);
        }
        Unknown* clone() && override
        {
            return new Unknown(move(*this));
        }
        const string getCategory() const override { return "Unknown"; }
        const string getType() const override { return "Unknown"; }
        void getDescription(ostream& out) override { out << "Unknown"; }
    };

    class Electronics: public AObject
    {
        public:
        Electronics() = default;
        Electronics(const Electronics& electronics): AObject(electronics) {}
        Electronics(Electronics&& electronics): AObject(electronics) {}
        virtual ~Electronics() = 0;
        virtual Electronics* clone() const& = 0;
        virtual Electronics* clone() && = 0;
        const string getCategory() const = 0;
        virtual const string getType() const = 0;
        virtual void getDescription(ostream&) = 0;  
        virtual void recognize() = 0;      
    };

    class Resistor: public Electronics
    {
        private:
        deque<opnmsp::Color*>ringcolors;
        void copy(const Resistor&);
        void mov(Resistor&);
        
        public:
        Resistor() = default;
        Resistor (const Resistor& resistor);
        Resistor (Resistor&& resistor);
        ~Resistor() override {}
        Resistor* clone() const& override
        {
            return new Resistor(*this);
        }
        Resistor* clone() && override
        {
            return new Resistor(move(*this));
        }
        const string getCategory() const override { return "Electronics"; }
        const string getType() const override { return "Resistor"; }
        void getDescription(ostream& out) override;
        void recognize() override;
    };
}

#endif