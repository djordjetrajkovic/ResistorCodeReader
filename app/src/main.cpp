#include <iostream>
using namespace std;

#include "segmentation.h"
#include "access.h"

int main()
{
    //segment::funct("test.png", "light.png");
    cout << "OK!!!" << endl;
    access::locationAt("lena.jpg");
    access::locationPtr("lena.jpg");
    return 0;
}