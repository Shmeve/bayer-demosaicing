#include "Demosaic.h"

using namespace std;
using namespace cv;

Demosaic::Demosaic(string filePath) {
    image = imread(filePath, 0);
    rows = image.rows;
    cols = image.cols;

    r = Mat::zeros(rows, cols, CV_8U);
    g = Mat::zeros(rows, cols, CV_8U);
    b = Mat::zeros(rows, cols, CV_8U);
}

void Demosaic::generateRGBComponents() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 0) {
                    // R Component
                    r.at<uchar>(i,j) = image.at<uchar>(i,j);
                }
                else {
                    // G Component
                    g.at<uchar>(i,j) = image.at<uchar>(i,j);
                }
            }
            else {
                if (j % 2 == 0) {
                    // G Component
                    g.at<uchar>(i,j) = image.at<uchar>(i,j);
                } else {
                    // B Component
                    b.at<uchar>(i,j) = image.at<uchar>(i,j);
                }
            }
        }
    }
}

void Demosaic::display() {
    imshow("Original", image);
    imshow("R Components", r);
    imshow("G Components", g);
    imshow("B Components", b);

    waitKey(0);
}

const Mat &Demosaic::getR() const {
    return r;
}

void Demosaic::setR(const Mat &r) {
    Demosaic::r = r;
}

const Mat &Demosaic::getG() const {
    return g;
}

void Demosaic::setG(const Mat &g) {
    Demosaic::g = g;
}

const Mat &Demosaic::getB() const {
    return b;
}

void Demosaic::setB(const Mat &b) {
    Demosaic::b = b;
}

int Demosaic::getRows() const {
    return rows;
}

void Demosaic::setRows(int rows) {
    Demosaic::rows = rows;
}

int Demosaic::getCols() const {
    return cols;
}

void Demosaic::setCols(int cols) {
    Demosaic::cols = cols;
}
