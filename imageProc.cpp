#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char *argv[])
{
  VideoCapture cam(0);//TODO temporary for raspberry pi camera at home, network camera will be implemented later
  Mat frame;
  while(true)
    {
      if(!vcap.read(frame))
	{
	  waitKey();
	}
      // process image
    }   
      
}
