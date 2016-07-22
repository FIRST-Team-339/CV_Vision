#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <sys/time.h>
#include <string>
#include "processing.h"

using namespace cv;
using namespace std;

int vals[1000];
int count = 0;
string ipAddr;
string cameraPath;


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
    cameraPath =  "http://FRC:FRC@" + ipAddr + "/mjpg/1/video.mjpg";
    VideoCapture vcap;
    Mat frame;
    Mat thresholdedFrame;
    Mat frameConvexHull;
    //printf("Image size: %dx%d",frame.rows,frame.cols);
    if(!vcap.open(cameraPath))
    {
        std::cout<<"could not open video stream!"<<std::endl;
        return -1;
    }
    //while(true)
    {
        if(!vcap.read(frame))
        {
            std::cout<<"Could not read frame!"<<std::endl;
        }
        else
        {
            //long int beginTime = getTimeMilliseconds();
            //imwrite("sourceImage.jpg",frame);//openCV can't write in HSV format
            //cvtColor(frame,frame,CV_BGR2HSV);
            thresholdedFrame = colorThreshold(frame, 65,105,70,115,180,225);
            updateBlobs(thresholdedFrame);
            cout<<"Num Blobs: " << getNumBlobs()<<endl;
            imwrite("BlobbedImage.jpg", drawBlobsOnImage(thresholdedFrame,false));
            //frameConvexHull = convexHull(thresholdedFrame);
            //long int endTime = getTimeMilliseconds();
            //printf("Time to Process: %d millis\n", endTime - beginTime);
            //process image
        }
    }
    return 0;
}



