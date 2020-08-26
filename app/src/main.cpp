#include <iostream>
using namespace std;

#include "segmentation.h"
#include "access.h"
#include "input.h" 

int main()
{
    
    panmsp::ACommand *starter = new panmsp::Starter();
    starter -> execute();
    cout << "OK!!!" << endl;
    // char key;
    // while (true)
    // {
    //     key = cv::waitKey('q');
	// 	if (key == 'q') break;
	// }
    // destroyAllWindows();
    return 0;
}