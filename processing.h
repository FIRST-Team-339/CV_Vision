#ifndef PROCESSING_H
#define PROCESSING_H

using namespace cv;

Mat colorThreshold(Mat, int,int,int,int,int,int);
Mat convexHull(Mat);
void erosion (Mat, Mat,int, int, Size, Point);
void dilation(Mat, Mat, int, int, Size, Point);
bool isInVec(std::vector<int>& vecToCheck, int valToCheck);
void updateBlobs(Mat);
int getNumBlobs();
struct Blob
{
    std::vector<Point> boundingPoints;
    int size; //size of the blob in pixels
    int rectWidth; //width of the bounding rectangle
    int rectheight; //height of the bounding rectangle
    Point weightedCenter;
    Point rectCenter; //center of the bounding rectangle
    std::vector<Point> rectCourners;
};

#endif
