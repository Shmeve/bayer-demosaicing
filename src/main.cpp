#include <opencv2/opencv.hpp>
#include <iostream>
#include "Demosaic.h"

using namespace cv;
using namespace std;

int main()
{
    Demosaic crayons = Demosaic("images/mosaic/crayons_mosaic.bmp");
    Demosaic oldwell = Demosaic("images/mosaic/oldwell_mosaic.png");
    Demosaic pencils = Demosaic("images/mosaic/pencils_mosaic.bmp");

    crayons.generateRGBComponents();
    oldwell.generateRGBComponents();
    pencils.generateRGBComponents();

    crayons.interpolate();
    oldwell.interpolate();
    pencils.interpolate();

    crayons.colorize();
    oldwell.colorize();
    pencils.colorize();

    crayons.display();
    oldwell.display();
    pencils.display();

    return 0;
}
