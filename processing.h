#ifndef PROCESSING_H
#define PROCESSING_H

Mat convexHull(Mat, Mat);
void erosion (Mat, Mat,int, int, Size, Point);
void dilation(Mat, Mat, int, int, Size, Point);

#endif
