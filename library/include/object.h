#include <iostream>
#include <vector>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

namespace objectsnmsp
{
    class Object {
    protected:
        vector<Point> contour;
        RotatedRect rotrectangle;
        Rect rectangle;
        string name;
        string category;
        string type;
    public:
        Object(){}
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

        Rect getRect()
        {
            return rectangle;
        }
        void setRect(Rect rect)
        {
            rectangle = rect;
        }

        // virtual methods
        virtual string getCategory() = 0;
        virtual string getType() = 0;
        virtual string getDescription() = 0;

    };

    class Unknown: public Object 
    {
        public:
        string getCategory() override { return "Unknown"; }
        string getType() override { return "Unknown"; }
        string getDescription() override { return "Unknown"; }
    };

    class Electronics: public Object
    {
        public:
        Electronics(){}
        string getCategory() override { return "Electronics"; }
        virtual string getType() = 0;
        virtual string getDescription() = 0;        
    };

    class Resistor: public Electronics
    {
        private:
        Scalar resistorColor;
        Scalar ringone;
        Scalar ringtwo;
        Scalar ringthree;
        Scalar ringfour;
        Scalar ringfive;
        public:
        Resistor(){}
        string getType() override { return "Resistor"; }
        string getDescription() override;
    };
}