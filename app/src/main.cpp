#include <iostream>
using namespace std;

#include "segmentation.h"
#include "access.h"
#include "input.h" 

int main()
{
    vector<Mat> images = inputnmsp::loadimages("samples/images/image5.jpg", false);
    Mat backgroung = inputnmsp::loadbackground("samples/backgrounds/background5.jpg", false);
    vector<Mat> templ = inputnmsp::loadtemplategrayscale("samples/templates/grayscale/template_grayscale.jpg", false);
    vector<Mat> templbin = inputnmsp::loadtemplatebinary("samples/templates/binary/template.jpg", false);
    for (auto img: images) segment::funct(img, backgroung, false);
    
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