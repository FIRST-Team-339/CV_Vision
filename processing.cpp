#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

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

Mat convexHull(Mat src, Mat out)
{
 Mat src_copy = src.clone();
 Mat src_gray;
 cvtColor(src_copy, src_gray, CV_BGR2GRAY);
 Mat threshold_output;
 vector<vector<Point> > contours;
 vector<Vec4i> hierarchy;
 // Find contours
 //threshold(src_gray, threshold_output, 200, 255, THRESH_BINARY);
 
 findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
 
 // Find the convex hull object for each contour
 vector<vector<Point> > hull(contours.size());
 for(int i = 0; i < contours.size(); i++)
 {
   convexHull(Mat(contours[i]), hull[i], false);
 }
 
 // Draw contours + hull results
 RNG rng;
 Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
 for(int i = 0; i< contours.size(); i++)
 {
  Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
  drawContours(out, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
  drawContours(out, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
 }
}
