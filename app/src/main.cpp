#include <iostream>
using namespace std;

#include "segmentation.h"
#include "access.h"

int main()
{
    segment::funct("image5.jpg", "background5.jpg", false);
    cout << "OK!!!" << endl;
    //access::locationAt("lena.jpg");
    //access::locationPtr("lena.jpg");
    //access::iterator("lena.jpg");
    //access::naryiterator("lena.jpg");
    //access::naryiterator();
    //access::iterator2();
    return 0;
}