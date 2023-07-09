#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


#include <iostream>

using namespace cv;
using namespace std;


Mat src; 
Mat src_gray; 
int thresh = 30; 
int max_thresh = 255; 

int main() {

	Mat img=imread("/home/xeri/Documents/VScodeData/c++Data/outdoor.jpg");
	Mat imgHSV, mask;
	int hmin = 40, smin = 34, vmin = 176;
	int hmax = 87, smax = 93, vmax = 255;

    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    imgHSV=img;//use BGR 

    Scalar lower(hmin, smin, vmin);
	Scalar upper(hmax, smax, vmax);
	inRange(imgHSV, lower, upper, mask);


  
    
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
    imshow("mask",mask);
    waitKey(0);
    return 0;


    

}