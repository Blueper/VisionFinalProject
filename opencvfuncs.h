#ifndef OPENCVFUNCS_H
#define OPENCVFUNCS_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

// Estimate FPS of video stream based on 120 frame capture
double measureFPS(VideoCapture& vid_stream);

// Given Background mask and a current frame, outputs foreground mask
Mat getForegroundMask(const Mat& background, const Mat& frame);

// Calculate centers of interrsection of ball and fg mask
// Return center of intersection and ball_mask - intersection
std::pair<Point,Point> calculate_centers(Mat ball_mask, Mat frame_mask);
#endif
