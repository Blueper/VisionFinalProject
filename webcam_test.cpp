#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
  VideoCapture stream1(0);

  if (!stream1.isOpened()) { //check if video device has been initialised
    cout << "cannot open camera";
  }

  Mat edges;
  namedWindow("edges", 1);
  int x = 0;
  int y = 0;
  while (true) {
    Mat cameraFrame;
    stream1.read(cameraFrame);  // read webcam frame

    // cout << "M = "<< endl << " "  << cameraFrame.rows << ", "
    //      << cameraFrame.cols << endl << endl;  //  image size
    // cout << cameraFrame.at<Vec3b>(Point(30,30)) << endl;  // RGB at x,y = 30,30

    //CODE TO CANNY EDGE DETECTOR
    // cvtColor(cameraFrame, edges, CV_BGR2GRAY);
    // GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
    // Canny(edges, edges, 0, 100, 3);

    //CODE TO ACCESS PIXELS
    // uchar r, g, b;
    // for(int i = 0; i < cameraFrame.rows; ++i){
    //   Vec3b* pixel = cameraFrame.ptr<Vec3b>(i);
    //   for(int j = 0; j < cameraFrame.cols; ++j){
    //     pixel[j][0] = pixel[j][2];
    //     pixel[j][2] = pixel[j][0];
    //   }
    // }

    //CODE TO DRAW A CIRCLE
    // circle(cameraFrame, Point(x,y), 100, Scalar(255, 255, 255), -1);
    // x+=20;
    // y+=20;

    imshow("cameraFrame", cameraFrame);
    if(waitKey(30) >= 0) break;
  }
  return 0;
}
