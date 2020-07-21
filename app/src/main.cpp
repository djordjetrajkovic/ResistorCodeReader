#include <iostream>
using namespace std;

#include "segmentation.h"

int main()
{
    segment::funct("test.png", "light.png");
    cout << "OK!!!" << endl;
    return 0;
}