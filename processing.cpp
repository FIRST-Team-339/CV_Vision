#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "processing.h"

using namespace cv;
using namespace std;//vector

vector<Blob> imageBlobs;

int getNumBlobs()
{
    return imageBlobs.size();
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

void updateBlobs(Mat blobImage)
{
    if(blobImage.channels() > 1)//If the image is color
        return;//quit without doing anything
    else
    {
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        vector<int> excludeIndexList;
        excludeIndexList.resize(10);
        // Find contours
        findContours(blobImage, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,
                 0));
        for(int i = 0; i < hierarchy.size();i++)
        {
            if(hierarchy[i][2] >= 0)//if the contour has a child contour
                {
                    excludeIndexList.push_back(hierarchy[i][2]);//exclude the child
                }
            else if(hierarchy[i][3])//if the contour has a parent contour
                {
                    excludeIndexList.push_back(i);//exclude the contour
                }
        }
        Blob tempBlob;
        for(int i = 0; i < contours.size(); i++)
          {
            printf("Got into blob check for\n");
            if(!isInVec(excludeIndexList,i))//if we haven't excluded this contour
            {
            printf("Got into if\n");
                tempBlob.boundingPoints = contours[i];
                printf("Got past tempBlob\n");
                imageBlobs[i] = tempBlob;//put it in our blob list
            }
        }
    }
}

bool isInVec(vector<int>& vecToCheck, int valToCheck)
{
    for(int i = 0; i < vecToCheck.size(); i++)
    {
        if (vecToCheck[i] == valToCheck)
            return true;
    }
    return false;
}


