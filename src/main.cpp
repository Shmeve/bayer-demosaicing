#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat sourceImage = imread("/home/steve/Development/comp498/comp498-a1-demosaicing/opencv-logo-small.png");

    // Check if image was successfully read
    if(sourceImage.empty())
    {
        cerr << "Could not read image" << endl;
        return 1;
    }

    // Display source image
    namedWindow("Source", WINDOW_AUTOSIZE);
    imshow("Source", sourceImage);

    // Convert to grayscale
    Mat grayImage;
    cvtColor(sourceImage, grayImage, COLOR_BGR2GRAY);

    // Display gray image
    namedWindow("Grayscale", WINDOW_AUTOSIZE);
    imshow("Grayscale", grayImage);

    //Wait until any key is pressed
    waitKey(0);

    cout << "Closing ..." << endl;

    return 0;
}
