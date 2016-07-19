#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <sys/time.h>

using namespace cv;
using namespace std;

int vals[1000];
int count = 0;
string ipAddr;
string cameraPath;

Mat convexHull(Mat, Mat);
void erosion (Mat, Mat,int, int, Size, Point);
void dilation(Mat, Mat, int, int, Size, Point);

//Written by Noah Golmant, from:
//https://github.com/noahgolmant/Text-Region-Identification/blob/master/ImageProcessing.cpp
static inline long getTimeMilliseconds()
 {
    timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_usec / 1000;
}

int main(int argc, char *argv[])
{
  if(argc > 1)
    {
      ipAddr = argv[1];
    }
  else
    {
      ipAddr = "10.3.39.11";
    }
  cameraPath = "http://FRC:FRC@"<<ipAddr<<"/mjpg/1/video.mjpg";
  VideoCapture vcap;
  Mat frame;
  //printf("Image size: %dx%d",frame.rows,frame.cols);
  if(!vcap.open(cameraPath))
    {
      std::cout<<"could not open video stream!"<<std::endl;
      return -1;
    }
  // while(true)
  {
    if(!vcap.read(frame))
      {
        std::cout<<"Could not read frame!"<<std::endl;
        return -1;
      }
    //long int beginTime = getTimeMilliseconds();
    imwrite("sourceImage.jpg",frame);//openCV can't write in HSV format
    cvtColor(frame,frame,CV_BGR2HSV);
    inRange(frame,Scalar(3,0,0),Scalar(20,255,255),frame);
    imwrite("ThresholdedImage.jpg",frame);
    //long int endTime = getTimeMilliseconds();
    //printf("Time to threshold: %d millis\n", endTime - beginTime);
    return 0;
    //waitKey();
    //process image
  }

}

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

