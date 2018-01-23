#pragma once

#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class Demosaic {
private:
    cv::Mat image;
    cv::Mat r;
    cv::Mat g;
    cv::Mat b;
    int rows;
    int cols;
    cv::Mat demosaicImage;
    cv::Mat colorImage;
    cv::Mat result;

public:
    explicit Demosaic(std::string filePath, std::string color);
    void generateRGBComponents();
    void interpolate();
    void colorize();
    void squaredDifference();
    void modifiedInterpolation();
    void display();
};



