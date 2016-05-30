#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char *argv[])
{
  VideoCapture vcap(1);//TODO temporary for raspberry pi camera at home, network camera will be implemented later
  Mat frame;
  //while(true)
  {
    if(!vcap.read(frame))
      {
            waitKey();
      }
    cvtColor(frame,frame,CV_RGB2HSV);
    imwrite("sourceImage.jpg",frame);
    inRange(frame,Scalar(3,0,0),Scalar(20,255,255),frame);
    imwrite("ThresholdedImage.jpg",frame);
    waitKey();
    // process image
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
