// STD Libs includes
#include <iostream>
#include <vector>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

#include <access.h>
namespace inputnmsp
{
    vector<Mat> loadtemplatebinary(string, bool);
    vector<Mat> loadtemplategrayscale(string, bool);
}

namespace panmsp
{
    class ACommand 
    {
        public:
        virtual void execute() = 0;
    };

    class ALoadImage: public ACommand
    {
        public:
        virtual void execute() = 0;
    };

    class File: public ALoadImage
    {
        private:
        Rect roi;
        void openImageFile();
        void openBckgFile();
        string imagepath;
        string backgroundgpath;
        opnmsp::AFind* operation;
        
        public:
        File(opnmsp::AFind* op, Rect ri, string ipath, string bpath): operation(op), roi(ri), imagepath(ipath), backgroundgpath(bpath) {}
        void execute() override;
    };

}