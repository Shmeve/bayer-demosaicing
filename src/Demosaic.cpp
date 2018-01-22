#include "Demosaic.h"

using namespace std;
using namespace cv;

Demosaic::Demosaic(string filePath) {
    image = imread(filePath, 0);
    rows = image.rows;
    cols = image.cols;

    r = Mat(rows, cols, CV_8U);
    g = Mat(rows, cols, CV_8U);
    b = Mat(rows, cols, CV_8U);

    demosaicImage = Mat::zeros(rows, cols, CV_8UC3);
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
    imshow("Color?", demosaicImage);

    waitKey(0);
}

void Demosaic::interpolate() {
    //filter2D(ex1, ex1, -1, k1);
    float kdata1[] = {
            0., 0., 0.,
            1./2., 0., 1./2.,
            0., 0., 0.
    };

    float kdata2[] {
            0., 1./2., 0.,
            0., 0., 0.,
            0., 1./2., 0.
    };

    float kdata3[] {
            1./4., 0., 1./4.,
            0., 0., 0.,
            1./4., 0., 1./4.
    };

    float kdata4[] {
            0., 1./4., 0.,
            1./4., 0., 1./4.,
            0., 1./4., 0.
    };

    Mat k1 = Mat(3, 3, CV_32F, kdata1);
    Mat k2 = Mat(3, 3, CV_32F, kdata2);
    Mat k3 = Mat(3, 3, CV_32F, kdata3);
    Mat k4 = Mat(3, 3, CV_32F, kdata4);

    Mat r2 = Mat(rows, cols, CV_8U);
    Mat r3 = Mat(rows, cols, CV_8U);
    Mat r4 = Mat(rows, cols, CV_8U);

    Mat b2 = Mat(rows, cols, CV_8U);
    Mat b3 = Mat(rows, cols, CV_8U);
    Mat b4 = Mat(rows, cols, CV_8U);

    Mat g2 = Mat(rows, cols, CV_8U);

    filter2D(r, r2, -1, k1);
    filter2D(r, r3, -1, k2);
    filter2D(r, r4, -1, k3);
    r = r + r2 + r3 + r4;

    filter2D(b, b2, -1, k1);
    filter2D(b, b3, -1, k2);
    filter2D(b, b4, -1, k3);
    b = b + b2 + b3 + b4;

    filter2D(g, g2, -1, k4);
    g = g + g2;
}

void Demosaic::colorize() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            demosaicImage.at<Vec3b>(i, j) = Vec3b(
                    b.at<uchar>(i,j),
                    g.at<uchar>(i,j),
                    r.at<uchar>(i,j)
            );
        }
    }
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
