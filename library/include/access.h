#include "opencv2/core/utility.hpp"
#include <string>

#include <object.h>
namespace access
{
    void locationAt(std::string);
    void locationPtr(std::string);
    void iterator(std::string);
    void iterator2();
    void naryiterator(std::string);
    void naryiterator();
}

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
        virtual vector<objectsnmsp::AObject> findObjects() = 0;
    };

    class FindByTemplate : public AFind
    {
        public:
        vector<objectsnmsp::AObject> findObjects() override;
        
        private:
        void segment();
        void searchForTemplate();
        void searchForContour();
        RotatedRect searchForRotatedRect();
        vector<Point> sampleContour(int);
    };
}