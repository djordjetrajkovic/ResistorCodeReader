#ifndef _access_h_
#define _access_h_

#include "opencv2/core/utility.hpp"
#include <string>

#include <object.h>

namespace opnmsp
{
    class AFind
    {
        protected:
        Mat image;
        Mat background;
        vector<objectsnmsp::AObject*> objects;
        vector<objectsnmsp::AObject*> samples;
        
        public:
        void setImage(Mat img) { image = img; }
        Mat getImage() { return image; }
        void setBackground(Mat bckg) { background = bckg; }
        Mat getBackground() { return background; }
        vector<objectsnmsp::AObject*> getObjects() { return objects; }
        void setObjects(vector<objectsnmsp::AObject*> objs) { objects = objs; }
        void setSamples(vector<objectsnmsp::AObject*> smpls) { samples = smpls; }
        virtual void findObjects() = 0;
    };

    class FindByTemplate : public AFind
    {
        public:
        void findObjects() override;
        
        private:
        void segment(Mat);
        void searchByTemplate(Mat);
        void searchByContour(Mat, Mat, objectsnmsp::AObject*);
        RotatedRect findRotRect(Mat);
        vector<Point> sampleContour(Mat, int);
    };
}

#endif