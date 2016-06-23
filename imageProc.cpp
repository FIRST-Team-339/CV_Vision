#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <sys/time.h>

using namespace cv;

struct timeval system_time;

int vals[1000];
int count = 0;

int main(int argc, char *argv[])
{
  VideoCapture vcap(0);//TODO temporary for raspberry pi camera at home, network camera will be implemented later
  Mat frame;
  printf("Image size: %dx%d",frame.rows,frame.cols);
  while(true)
  {
    if(!vcap.read(frame))
      {
        std::cout<<"Could not read frame!"<<std::endl;
        return -1;
      }
    gettimeofday(&system_time,NULL);
    long int beginTime = system_time.tv_sec * 1000 + system_time.tv_usec/1000;
    cvtColor(frame,frame,CV_BGR2RGB);//No idea what the int constant should be for rpicam
    //imwrite("sourceImage.jpg",frame);
    inRange(frame,Scalar(3,0,0),Scalar(20,255,255),frame);
    //imwrite("ThresholdedImage.jpg",frame);
    gettimeofday(&system_time,NULL);
    long int endTime = system_time.tv_sec * 1000 + system_time.tv_usec/1000;
    printf("Time to process: %d millis\n", endTime - beginTime);
    if(count <1000)
      {
	vals[count]= endTime-beginTime;
	count++;
      }
    else
      {
	double average = 0;
	for(int i = 0; i < count; i++)
	  {
	    average += vals[i];
	  }
	average /= count + 1;
	printf("Average processing time: %f millis \n", average);
	return 0;
      }
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

// Convex Hull implementation
 Mat src_copy = src.clone();
 Mat threshold_output;
 vector<vector<Point> > contours;
 vector<Vec4i> hierarchy;
 
 // Find contours
 threshold( src_gray, threshold_output, 200, 255, THRESH_BINARY );
 findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
 
 // Find the convex hull object for each contour
 vector<vector<Point> >hull( contours.size() );
 for( int i = 0; i < contours.size(); i++ )
 {  convexHull( Mat(contours[i]), hull[i], false ); }
 
 // Draw contours + hull results
 RNG rng;
 Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
 for( int i = 0; i< contours.size(); i++ )
 {
  Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
  drawContours( drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
  drawContours( drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
 }
