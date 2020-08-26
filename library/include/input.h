// STD Libs includes
#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

#include <access.h>
#include <object.h>

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
        File(const File&) = delete;
        void execute() override;
    };

    class LoadSamples: public ACommand
    {
        private:
        string templgraypath;
        string templbinpath;
        opnmsp::AFind* operation;
        void prepObjectsTemplates();

        public:
        LoadSamples(opnmsp::AFind* op, string tmplgpath, string tmplbinpath): operation(op), templgraypath(tmplgpath), templbinpath(tmplbinpath) {}
        LoadSamples(const LoadSamples&) = delete;
        void execute() override;
    };

    class FindObjects: public ACommand
    {
        private:
        opnmsp::AFind* operation;
        void find();

        public:
        FindObjects(opnmsp::AFind* op): operation(op) {}
        FindObjects(const FindObjects&) = delete;
        void execute() override;
    };

    class DisplayResult: public ACommand
    {
        private:
        opnmsp::AFind* operation;
        void show();

        public:
        DisplayResult(opnmsp::AFind* op): operation(op) {}
        DisplayResult(const DisplayResult&) = delete;
        void execute() override;
    };

    class Starter: public ACommand
    {
        private:
        void start();

        public:
        Starter() {}
        Starter(const Starter&) = delete;
        void execute() override;
    };

    class Composite: public ACommand
    {
        private:
        deque<ACommand*> operations;
        
        public:
        Composite() {}
        Composite(const Composite&) = delete;
        void add(ACommand *command) { operations.push_back(command); }
        void removelast() { operations.pop_back(); }
        void execute() override;
    };
}