#ifndef OPENCVFUNCS_H
#define OPENCVFUNCS_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

// Given Background mask and a current frame, outputs foreground mask
Mat getForegroundMask(const Mat& background, const Mat& frame);

#endif
