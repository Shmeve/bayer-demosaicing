#include "Demosaic.h"
#include <cmath>

using namespace std;
using namespace cv;

/**
 * Initialize parameters needed to colorize a bayer mosaic image
 *
 * @param filePath file path to bayer mosaic image
 * @param color file path to the original color image
 */
Demosaic::Demosaic(string filePath, string color) {
    Mat raw = imread(filePath, CV_LOAD_IMAGE_GRAYSCALE);
    raw.convertTo(image, CV_32F);

    colorImage = imread(color, CV_LOAD_IMAGE_COLOR);
    colorImage.convertTo(colorImage, CV_32F);

    rows = image.rows;
    cols = image.cols;

    r = Mat::zeros(rows, cols, CV_32F);
    g = Mat::zeros(rows, cols, CV_32F);
    b = Mat::zeros(rows, cols, CV_32F);

    demosaicImage = Mat::zeros(rows, cols, CV_32FC3);
    result = Mat::zeros(rows, cols, CV_32FC3);
}

/**
 * Split bayer (RGGB) mosaic image into separate R, G, and B matrices
 */
void Demosaic::generateRGBComponents() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 0) {
                    // R Component
                    r.at<float>(i,j) = image.at<float>(i,j);
                }
                else {
                    // G Component
                    g.at<float>(i,j) = image.at<float>(i,j);
                }
            }
            else {
                if (j % 2 == 0) {
                    // G Component
                    g.at<float>(i,j) = image.at<float>(i,j);
                } else {
                    // B Component
                    b.at<float>(i,j) = image.at<float>(i,j);
                }
            }
        }
    }
}

/**
 * Display results of the demosaicing process
 */
void Demosaic::display() {
    Mat d8u, r8u, c8u;
    demosaicImage.convertTo(d8u, CV_8UC3);
    result.convertTo(r8u, CV_8UC3);
    colorImage.convertTo(c8u, CV_8UC3);

    imshow("Demosaic", d8u);
    imshow("Squared Difference", r8u);
    imshow("Original", c8u);

    waitKey(0);
}

/**
 * Interpolate the missing information for each of the R, G, and B component matrices
 */
void Demosaic::interpolate() {
    // Kernals for R and B components
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

    // Kernal for G component
    float kdata4[] {
            0., 1./4., 0.,
            1./4., 0., 1./4.,
            0., 1./4., 0.
    };

    Mat k1 = Mat(3, 3, CV_32F, kdata1);
    Mat k2 = Mat(3, 3, CV_32F, kdata2);
    Mat k3 = Mat(3, 3, CV_32F, kdata3);
    Mat k4 = Mat(3, 3, CV_32F, kdata4);

    Mat r2 = Mat(rows, cols, CV_32F);
    Mat r3 = Mat(rows, cols, CV_32F);
    Mat r4 = Mat(rows, cols, CV_32F);

    Mat b2 = Mat(rows, cols, CV_32F);
    Mat b3 = Mat(rows, cols, CV_32F);
    Mat b4 = Mat(rows, cols, CV_32F);

    Mat g2 = Mat(rows, cols, CV_32F);

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

/**
 * Combine R, G, and B component matrices into a single three channel color image
 */
void Demosaic::colorize() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            demosaicImage.at<Vec3f>(i, j) = Vec3f(
                    b.at<float>(i,j),
                    g.at<float>(i,j),
                    r.at<float>(i,j)
            );
        }
    }
}

/**
 * Highlight the artifacts produced by the demosaicing process
 */
void Demosaic::squaredDifference() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < 3; k++) {
                result.at<Vec3f>(i, j)[k] =
                        sqrt(pow((colorImage.at<Vec3f>(i, j)[k] - demosaicImage.at<Vec3f>(i, j)[k]), 2));
            }
        }
    }
}

/**
 * Implement proposed bilinear interpolation improvement
 */
void Demosaic::modifiedInterpolation() {
    Mat r_g = Mat(rows, cols, CV_32F);
    Mat b_g = Mat(rows, cols, CV_32F);

    r_g = r - g;
    b_g = b - g;

    medianBlur(r_g, r_g, 3);
    medianBlur(b_g, b_g, 3);

    r = r_g + g;
    b = b_g + g;
}
