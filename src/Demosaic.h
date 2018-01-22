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

public:
    explicit Demosaic(std::string filePath);
    void generateRGBComponents();
    void interpolate();
    void colorize();
    void display();
    const cv::Mat &getR() const;
    void setR(const cv::Mat &r);
    const cv::Mat &getG() const;
    void setG(const cv::Mat &g);
    const cv::Mat &getB() const;
    void setB(const cv::Mat &b);
    int getRows() const;
    void setRows(int rows);
    int getCols() const;
    void setCols(int cols);
};



