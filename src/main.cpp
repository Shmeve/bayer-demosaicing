#include <opencv2/opencv.hpp>
#include <iostream>
#include "Demosaic.h"

using namespace cv;
using namespace std;

int main()
{
    vector<Demosaic> demosaics = vector<Demosaic>();
    demosaics.emplace_back(Demosaic("images/mosaic/crayons_mosaic.bmp", "images/color/crayons.jpg"));
    demosaics.emplace_back(Demosaic("images/mosaic/oldwell_mosaic.png", "images/color/oldwell.jpg"));
    demosaics.emplace_back(Demosaic("images/mosaic/pencils_mosaic.bmp", "images/color/pencils.jpg"));

    for (auto demosaic : demosaics) {
        // Part 1
        demosaic.generateRGBComponents();
        demosaic.interpolate();
        demosaic.colorize();
        demosaic.squaredDifference();
        demosaic.display();
        // Part 2
        demosaic.modifiedInterpolation();
        demosaic.colorize();
        demosaic.squaredDifference();
        demosaic.display();
    }

    return 0;
}
