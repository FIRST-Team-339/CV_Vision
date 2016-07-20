#ifndef PROCESSING_H
#define PROCESSING_H

using namespace cv;

Mat colorThreshold(Mat, int,int,int,int,int,int);
Mat convexHull(Mat);
void erosion (Mat, Mat,int, int, Size, Point);
void dilation(Mat, Mat, int, int, Size, Point);

#endif
