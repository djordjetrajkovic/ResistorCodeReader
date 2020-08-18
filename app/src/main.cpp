#include <iostream>
using namespace std;

#include "segmentation.h"
#include "access.h"
#include "input.h" 

int main()
{
    vector<Mat> images = inputnmsp::loadimages("image5.jpg", false);
    Mat backgroung = inputnmsp::loadbackground("background5.jpg", false);
    vector<Mat> templ = inputnmsp::loadtemplategrayscale("template_grayscale.jpg", false);
    for (auto img: images) segment::funct(img, backgroung, templ.at(0), true);
    
    cout << "OK!!!" << endl;
    //access::locationAt("lena.jpg");
    //access::locationPtr("lena.jpg");
    //access::iterator("lena.jpg");
    //access::naryiterator("lena.jpg");
    //access::naryiterator();
    //access::iterator2();
    char key;
    while (true)
    {
        key = cv::waitKey('q');
		if (key == 'q') break;
	}
    destroyAllWindows();
    return 0;
}