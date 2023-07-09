#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


#include <iostream>

using namespace cv;
using namespace std;


Mat src_gray; 
int thresh = 30; 
int max_thresh = 255; 

int main() {
    
	Mat img=imread("/home/xeri/Documents/VScodeData/c++Data/outdoor.jpg");
	Mat imgHSV, imgYUV,mask;
	int hmin = 73, smin = 32, vmin = 151;
	int hmax = 179, smax = 255, vmax = 255;

    cvtColor(img, imgHSV, COLOR_BGR2HSV);
    cvtColor(img, imgYUV, COLOR_BGR2YUV);
    Mat img2;
    img2=imgHSV;
    img2=imgYUV;
    Scalar lower(hmin, smin, vmin);
	Scalar upper(hmax, smax, vmax);
	inRange(img2, lower, upper, mask);


    Mat maskcanny;
	Canny(mask, maskcanny, 25,75);
  
    
    Mat gray=mask;
    //cvtColor(mask,gray,COLOR_BGR2GRAY);
    Mat binary;
    threshold(gray, binary, 0,255,THRESH_BINARY);


    vector<  vector<Point>> contours;
    findContours(binary,contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);

    for (int i = 0; i < contours.size(); i++)
    {
        Moments mu = moments(contours[i], false);
        Point2f center(mu.m10 / mu . m00,mu .m01 / mu. m00 );

        drawContours(img, contours, i, Scalar(0.0 , 0.0,  255),2);
        circle(img,center,3, Scalar(0 ,  255, 0), -1);
    }
        
    imshow("img",img);
    imshow("imgHSV",imgHSV);
    imshow("imgYUV",imgYUV);
    imshow("mask",mask);
    imshow("canny",maskcanny);
    waitKey(0);
    return 0;


    

}