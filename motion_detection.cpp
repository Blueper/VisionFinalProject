#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

#include "opencvfuncs.h"

using namespace cv;
using namespace std;

int main() {
  int ceil_ = 500;
  VideoCapture capture_(0);
  if (!capture_.isOpened()) { cout << "can't find webcam\n"; }

  Mat background;  // first frame (only background)
  Mat frame, blurred_frame;  // current frame, grayscale current frame

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

    Mat fgmask = getForegroundMask(background, frame);

    imshow("Foreground Mask", fgmask);
    if(waitKey(30) >= 0) break;
  }
  return 0;
}
