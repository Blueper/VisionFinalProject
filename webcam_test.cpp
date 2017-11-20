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

  //unconditional loop
  while (true) {
  Mat cameraFrame;
  stream1.read(cameraFrame);
  cout << "M = "<< endl << " "  << cameraFrame.rows << ", " << cameraFrame.cols << endl << endl;
  cout << cameraFrame.at<Vec3b>(Point(30,30)) << endl;
  imshow("cam", cameraFrame);
  if (waitKey(30) >= 0)
    break;
  }
  return 0;
}
