#include <iostream>
using namespace std;

#include <begin.h>

int main()
{
    rtnmsp::Begin* begin = rtnmsp::Begin::createBegin();
    //begin->findObjectsFile("samples/images/image4.jpg", "samples/backgrounds/background4.jpg");
    begin->findObjectsFile("samples/images/image5.jpg", "samples/backgrounds/background5.jpg");
    //begin->findObjectsFolder("samples/images/image%01d.jpg", "samples/backgrounds/background5.jpg");
    cout << "OK!!!" << endl;
    char key;
    while (true)
    {
        key = cv::waitKey('q');
		if (key == 'q') break;
	}
    destroyAllWindows();
    return 0;
}