#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include<iostream>
#include <opencv2/calib3d.hpp>

using namespace cv;
using namespace std;
const int length=10;
const int fx=100,fy=150,cx=0,cy=0;

vector<Point3f> light3d
{
    Point3f(0,0,0),
    Point3f(length,0,0),
    Point3f(length,length,0),
    Point3f(0,length,0),
};

Mat camera = (Mat_<double>(3,3)<<fx,0,cx,0,fy,cy,0,0,1); 
// I don't know how to set the parameter of camera intrinsic matrix
Mat dist;
// I don't know how to set the parameter of distortion coefficients too
int main()
{
    vector<Point2f> light2d
    {
        Point2f(100,150),
        Point2f(300,150),
        Point2f(300,300),
        Point2f(100,300),
    };

    Mat rVec = Mat::zeros(3,1,CV_64FC1);
    Mat tVec = Mat::zeros(3,1,CV_64FC1);
    solvePnP(light3d,light2d,camera,dist,rVec,tVec,false,SOLVEPNP_IPPE );
    cout<<rVec<<endl;
    cout<<tVec<<endl;
    return 0;
}