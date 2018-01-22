#include <opencv2/opencv.hpp>
#include <iostream>
#include "Demosaic.h"

using namespace cv;
using namespace std;

int main()
{
    Demosaic crayons = Demosaic("images/mosaic/crayons_mosaic.bmp", "images/color/crayons.jpg");
    Demosaic oldwell = Demosaic("images/mosaic/oldwell_mosaic.png", "images/color/oldwell.jpg");
    Demosaic pencils = Demosaic("images/mosaic/pencils_mosaic.bmp", "images/color/pencils.jpg");

    crayons.generateRGBComponents();
    oldwell.generateRGBComponents();
    pencils.generateRGBComponents();

    crayons.interpolate();
    oldwell.interpolate();
    pencils.interpolate();

    crayons.colorize();
    oldwell.colorize();
    pencils.colorize();

    crayons.squaredDifference();
    oldwell.squaredDifference();
    pencils.squaredDifference();

    crayons.display();
    oldwell.display();
    pencils.display();

    return 0;
}
