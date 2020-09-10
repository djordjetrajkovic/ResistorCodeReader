#ifndef _input_h_
#define _input_h_

// STD Libs includes
#include <iostream>
#include <sstream>
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

        virtual ~ACommand() = 0;
    };

    class ALoadImage: public ACommand
    {
        public:
        virtual ~ALoadImage() = 0;
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
        ~File() override { }
        void execute() override;
    };

    class Folder: public ALoadImage
    {
        private:
        Rect roi;
        Mat fullimage;
        void openBckgFile();
        string backgroundgpath;
        opnmsp::AFind* operation;
        
        public:
        Folder(opnmsp::AFind* op, Rect ri, Mat img, string bpath): operation(op), roi(ri), fullimage(img), backgroundgpath(bpath) {}
        ~Folder() override {}
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
        ~LoadSamples() override { }
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
        ~FindObjects() override { }
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
        ~DisplayResult() override { }
        void execute() override;
    };

    class DisplayImage: public ACommand
    {
        private:
        opnmsp::AFind* operation;
        void show();

        public:
        DisplayImage(opnmsp::AFind* op): operation(op) {}
        DisplayImage(const DisplayImage&) = delete;
        ~DisplayImage() override { }
        void execute() override;       
    };

    class DisplayObjects: public ACommand
    {
        private:
        opnmsp::AFind* operation;
        void show();

        public:
        DisplayObjects(opnmsp::AFind* op): operation(op) {}
        DisplayObjects(const DisplayObjects&) = delete;
        ~DisplayObjects() override { }
        void execute() override;  
    };

    class Starter: public ACommand
    {
        private:
        virtual void start();

        public:
        Starter() = default;
        Starter(const Starter&) = delete;
        void execute() override;
        virtual ~Starter() = 0;
    };

    class SingleImage: public Starter
    {
        private:
        string imagepath, backgroundpath;
        void start() override;

        public:
        SingleImage(string ipath, string bpath): imagepath(ipath), backgroundpath(bpath) {}
        SingleImage(const SingleImage&) = delete;
        ~SingleImage(){}
    };

    class MultipleImages: public Starter
    {
        private:
        string folderpath, backgroundpath;
        void start() override;

        public:
        MultipleImages(string fpath, string bpath): folderpath(fpath), backgroundpath(bpath) {}
        MultipleImages(const MultipleImages&) = delete;
        ~MultipleImages() {}
    };

    class Composite: public ACommand
    {
        private:
        deque<ACommand*> operations;
        
        public:
        Composite() {}
        Composite(const Composite&) = delete;
        ~Composite() override;
        void add(ACommand *command) { operations.push_back(command); }
        void removelast() { operations.pop_back(); }
        void execute() override;
    };
}

#endif