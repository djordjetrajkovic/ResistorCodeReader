#include <iostream>
using namespace std;

#include <begin.h>

int main()
{
    rtnmsp::Begin* begin = rtnmsp::Begin::createBegin();
    begin->findObjectsFile("samples/images/slika1_novo.jpg", "samples/backgrounds/pozadina1_novo.jpg", 300, 200, 900, 1200);
    //begin->findObjectsFile("samples/images/slika2_novo.jpg", "samples/backgrounds/pozadina1_novo.jpg");
    //begin->findObjectsFile("samples/images/slika3_novo.jpg", "samples/backgrounds/pozadina1_novo.jpg");
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