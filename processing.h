#ifndef PROCESSING_H
#define PROCESSING_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

Mat colorThreshold(Mat, int,int,int,int,int,int);
Mat convexHull(Mat, Mat);
void erosion (Mat, Mat,int, int, Size, Point);
void dilation(Mat, Mat, int, int, Size, Point);

#endif
