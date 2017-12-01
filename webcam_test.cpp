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

  while (true) {
    Mat cameraFrame;
    stream1.read(cameraFrame);  // read webcam frame
    cout << "M = "<< endl << " "  << cameraFrame.rows << ", "
         << cameraFrame.cols << endl << endl;  //  image size
    cout << cameraFrame.at<Vec3b>(Point(30,30)) << endl;  // RGB at x,y = 30,30
    imshow("cam", cameraFrame);  // draw camera frame
    if (waitKey(30) >= 0)  // wait for user input for 30 milliseconds and quit if received
      break;
  }
  return 0;
}
