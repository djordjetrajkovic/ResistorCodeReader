#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

namespace objectsnmsp
{
    class Object {
    private:
        void copy(const Object&);
        void mov(Object&);
        void del();
    protected:
        Mat* image;
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
        Object() = default;
        Object(const Object& obj)
        {
            copy(obj);
        }
        Object(Object&& obj)
        {
            mov(obj);
        }

        // polimorfno kopiranje objekata
        virtual Object* clone() const& = 0;
        virtual Object* clone() && = 0;

        // destruktor
        virtual ~Object() = 0;

        // metode
        void setImage(Mat* img)
        {
            image = img;
        }
        Mat* getImage()
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
        virtual string getDescription() = 0;
    };

    class Unknown: public Object 
    {
        public:
        Unknown() = default;
        Unknown(const Unknown& unknwn): Object(unknwn){}
        Unknown(Unknown&& unknwn): Object(unknwn){}
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
        string getDescription() override { return "Unknown"; }
    };

    class Electronics: public Object
    {
        public:
        Electronics() = default;
        Electronics(const Electronics& electronics): Object(electronics){}
        Electronics(Electronics&& electronics): Object(electronics){}

        virtual Electronics* clone() const& = 0;
        virtual Electronics* clone() && = 0;
        const string getCategory() const override { return "Electronics"; }
        virtual const string getType() const = 0;
        virtual string getDescription() = 0;        
    };

    class Resistor: public Electronics
    {
        private:
        Scalar resistorColor;
        Scalar rone;
        Scalar rtwo;
        Scalar rthree;
        Scalar rfour;
        Scalar rfive;
        void copy(const Resistor&);
        void mov(Resistor&);

        public:
        Resistor() = default;
        Resistor (const Resistor& resistor);
        Resistor (Resistor&& resistor);
        
        Resistor* clone() const& override
        {
            return new Resistor(*this);
        }
        Resistor* clone() && override
        {
            return new Resistor(move(*this));
        }

        const string getType() const override { return "Resistor"; }
        string getDescription() override;
    };
}