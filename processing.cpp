#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
//#include "processing.h"

using namespace cv;
using namespace std; //may not be necessary, check when you're not in an emacs window

void erosion (Mat in, Mat out,int iterations, int shape, Size kernelSize, Point anchor = Point(-1,-1))
{
  Mat structuringKernel = getStructuringElement(shape,kernelSize,anchor);
  for(int i = 0; i< iterations; i++)
    {
      erode(in,out,structuringKernel);
    }
}

void dilation(Mat in, Mat out,int iterations, int shape, Size kernelSize, Point anchor = Point(-1,-1))
{
  Mat structuringKernel = getStructuringElement(shape,kernelSize,anchor);
  for(int i = 0; i< iterations; i++)
    {
      dilate(in,out,structuringKernel);
    }
}

/**
 * Accepts a binary input image, draws a convex hull image, and writes it to <out>
*/
Mat convexHull(Mat src)
{
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    // Find contours
    findContours(src, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,
                 0));
    // Find the convex hull object for each contour
    vector<vector<Point> > hull(contours.size());
    for(int i = 0; i < contours.size(); i++)
    {
        convexHull(Mat(contours[i]), hull[i], false);
    }
    // Draw contours + hull results
    RNG rng;
    Mat out = Mat::zeros(src.size(), CV_8UC1);
    for(int i = 0; i< contours.size(); i++)
    {
        drawContours(out, hull, i, 255, CV_FILLED, 8, vector<Vec4i>(), 0, Point());
        //drawContours(out, contours, i, color1, 1, 8, vector<Vec4i>(), 0, Point());
    }
    return out;
}
//TODO change argument names so HSV also makes sense here
Mat colorThreshold(Mat in, int lowB, int highB, int lowG, int highG, int lowR, int highR)
{
    Mat out = in.clone();
    inRange(in, Scalar(lowB,lowG,lowR), Scalar(highB, highG, highR), out);
    return out;
}
