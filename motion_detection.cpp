// porting to cpp from:
//www.pyimagesearch.com/2015/05/25/basic-motion-detection-and-tracking-with-python-and-opencv
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ball.h"
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

int main() {
  int ceil_ = 500;
  VideoCapture capture_(0);
  if (!capture_.isOpened()) { cout << "can't find webcam\n"; }

  Mat background;  // first frame (only background)
  Mat frame, grey_frame;  // current frame, grayscale current frame
  Mat difference;  // difference of background and current frame
  int threshold_value = 5; //threshold to use when creating the binary image

  // Create ball at position 0,0
  int width = capture_.get(CV_CAP_PROP_FRAME_WIDTH);
  int height = capture_.get(CV_CAP_PROP_FRAME_HEIGHT);
  int radius = 25;  // 50px ball radius
  Vec2f velocity{20,20};  // initial ball velocity
  Scalar color{255,255,255};  // white ball color
  Ball ball{width-30, height-30, radius, velocity, color};

  while(true) {
    capture_.read(frame);
    cvtColor(frame, grey_frame, CV_BGR2GRAY);  // convert to grayscale
    GaussianBlur(grey_frame, grey_frame, Size(9,9), 0);  // remove noise

//    ball.Update();
    ball.SetPosition(100,100);
    ball.Draw(&frame);

    // For the first time, store the background
    if (background.empty()) {
      grey_frame.copyTo(background);
      continue;
    }

    // get the difference between the background and the current frame
    absdiff(background, grey_frame, difference);
    imshow("Target",difference);

    // make the difference image binary
    threshold(difference, difference, threshold_value, 255, THRESH_BINARY_INV);

    // expand the white parts of the image
//    dilate(difference, difference, Mat(), Point(-1, -1), 100);

    // Find contours
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    // find contours of objects in difference image, only returning the
    // extreme outer ones and do simple chaining of the contours
    findContours(difference, contours, hierarchy, CV_RETR_EXTERNAL,
                 CV_CHAIN_APPROX_SIMPLE);

    // Draw the contours on the image
    Scalar color = Scalar(0, 255, 255);
    for (int i = 0; i < contours.size(); i++) {
      drawContours(frame, contours, i, color, 2, CV_FILLED, hierarchy, 1);
    }

    //get the grey frame for the next image
    grey_frame.copyTo(background);


//    imshow("Target", difference);
//    imshow("Target", grey_frame);
//    imshow("Target", frame);
    if(waitKey(30) >= 0) break;
  }
  return 0;
}
