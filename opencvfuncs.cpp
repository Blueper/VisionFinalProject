#include "opencvfuncs.h"

cv::Mat getForegroundMask(const Mat& background, const Mat& frame) {
  Mat blurred_frame, difference;

  // remove noise
  GaussianBlur(frame, blurred_frame, Size(21, 21), 0);

  absdiff(background, blurred_frame, difference);

  // make the difference image grayscale then binary
  cvtColor(difference, difference, CV_BGR2GRAY);
  threshold(difference, difference, 25, 255, THRESH_BINARY);

  return difference;
}
