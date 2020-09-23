#include <iostream>
using namespace std;

#include <begin.h>

int main()
{
    rtnmsp::Begin* begin = rtnmsp::Begin::createBegin();
    begin->findObjectsFile("/home/djordje/Project/ResistorColorCode/samples/images/resistors1.jpg", "/home/djordje/Project/ResistorColorCode/samples/backgrounds/bckg_flash.jpg", 300, 200, 900, 1200);
    begin->findObjectsFile("/home/djordje/Project/ResistorColorCode/samples/images/resistors2.jpg", "/home/djordje/Project/ResistorColorCode/samples/backgrounds/bckg_flash.jpg", 300, 200, 900, 1200);
    begin->findObjectsFile("/home/djordje/Project/ResistorColorCode/samples/images/resistors3.jpg", "/home/djordje/Project/ResistorColorCode/samples/backgrounds/bckg_flash.jpg", 300, 200, 900, 1200);
    begin->findObjectsFile("/home/djordje/Project/ResistorColorCode/samples/images/resistors4.jpg", "/home/djordje/Project/ResistorColorCode/samples/backgrounds/bckg_flash.jpg", 300, 200, 900, 1200);
    cout << "Waiting for 'q'... " << endl;
    char key;
    while (true)
    {
        key = cv::waitKey('q');
		if (key == 'q') break;
	}
    destroyAllWindows();
    delete begin;
    cout << "OK!!!" << endl;
    return 0;
}