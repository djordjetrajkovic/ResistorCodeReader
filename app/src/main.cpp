#include <iostream>
using namespace std;

#include "segmentation.h"

int main()
{
    string slika = "/home/djordje/Pictures/test_noise.png";
    string pozadina = "/home/djordje/Pictures/light.png";
    segment::funct(slika, pozadina);
    cout << "OK!" << endl;
    return 0;
}