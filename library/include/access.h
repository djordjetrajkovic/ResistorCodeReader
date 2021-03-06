#ifndef _access_h_
#define _access_h_

#include "opencv2/core/utility.hpp"
#include <string>
#include <utility.h>

#include <object.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/shape/shape_distance.hpp>
using namespace cv;

namespace opnmsp
{
    class AFind
    {
        protected:
        Mat image;
        Mat background;
        vector<objectsnmsp::AObject*> objects;
        vector<objectsnmsp::AObject*> samples;
        static int uID;
        
        public:
        void setImage(Mat img) { image = img; }
        Mat getImage() { return image; }
        void setBackground(Mat bckg) { background = bckg; }
        Mat getBackground() { return background; }
        vector<objectsnmsp::AObject*> getObjects() { return objects; }
        void setObjects(vector<objectsnmsp::AObject*> objs) { objects = objs; }
        void setSamples(vector<objectsnmsp::AObject*> smpls) { samples = smpls; }
        virtual void findObjects() = 0;
        virtual ~AFind() = 0;
        virtual int getID() = 0;
    };

    class FindByTemplate : public AFind
    {
        public:
        FindByTemplate() { id = ++uID; }
        void findObjects() override;
        ~FindByTemplate() override {}
        int getID() override { return id; }

        private:
        int id;
        Mat segment();
        vector<vector<Point>>* searchByTemplate(Mat, objectsnmsp::AObject*);
        void searchByContour(Mat&, Mat, objectsnmsp::AObject*, Rect);
        
        vector<Point> sampleContour(vector<Point>, int);
        bool isColorInRange(Mat, Scalar);
    };
}

#endif