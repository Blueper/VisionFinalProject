#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

int main() {
  int ceil_ = 500;
  VideoCapture capture_(0);
  if (!capture_.isOpened()) { cout << "can't find webcam\n"; }

  Mat background;  // first frame (only background)
  Mat frame, blurred_frame;  // current frame, grayscale current frame
  Mat difference;  // difference of background and current frame

  // warm camera up and cache background
  int warmup_frames = 5;
  for (int initial_frames = 0; initial_frames < warmup_frames; initial_frames++) {
    capture_.read(frame);
    flip(frame, frame, 1);
    if (initial_frames == warmup_frames-1) {
      GaussianBlur(frame, blurred_frame, Size(21,21), 0);  // remove noise
      blurred_frame.copyTo(background);
    }
  }

  // main detection loop
  while(true) {
    capture_.read(frame);
    flip(frame, frame, 1);
    GaussianBlur(frame, blurred_frame, Size(21,21), 0);  // remove noise
    // get the difference between the background and the current frame
    absdiff(background, blurred_frame, difference);

    // make the difference image binary
    cvtColor(difference, difference, CV_BGR2GRAY);
    threshold(difference, difference, 25, 255, THRESH_BINARY);

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

    imshow("Contours", frame);
    if(waitKey(30) >= 0) break;
  }
  return 0;
}
