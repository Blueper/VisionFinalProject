// porting to cpp from:
//www.pyimagesearch.com/2015/05/25/basic-motion-detection-and-tracking-with-python-and-opencv
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
  Mat frame, grey_frame;  // current frame, grayscale current frame
  Mat difference;  // difference of background and current frame

  // warm camera up and cache background
  int warmup_frames = 5;
  for (int initial_frames = 0; initial_frames < warmup_frames; initial_frames++) {
    capture_.read(frame);
    cvtColor(frame, grey_frame, CV_BGR2GRAY);  // convert to grayscale
    GaussianBlur(grey_frame, grey_frame, Size(21,21), 0);  // remove noise
    if (initial_frames == warmup_frames-1) {
      grey_frame.copyTo(background);
    }
  }

  // main detection loop
  while(true) {
    capture_.read(frame);
    cvtColor(frame, grey_frame, CV_BGR2GRAY);  // convert to grayscale
    GaussianBlur(grey_frame, grey_frame, Size(21,21), 0);  // remove noise

    // get the difference between the background and the current frame
    absdiff(background, grey_frame, difference);

    imshow("BG", background);
    imshow("Gray", grey_frame);
    imshow("Diff", difference);
    // make the difference image binary
    threshold(difference, difference, 25, 255, THRESH_BINARY);

    // expand the white parts of the image
    dilate(difference, difference, Mat(), Point(-1, -1), 2);

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

    imshow("Binary", difference);
    imshow("Target", frame);
    if(waitKey(30) >= 0) break;
  }
  return 0;
}
