#ifndef OPENCVFUNCS_H
#define OPENCVFUNCS_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ball.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace cv;

// Draws text with bottom left corner at (x,y)
void drawText(Mat& image, int x, int y, const std::string& text);

// Appends num to a string
std::string appendNumToText(std::string text, int num);

// Estimate FPS of video stream based on 120 frame capture
double measureFPS(VideoCapture& vid_stream);

// Given Background mask and a current frame, outputs foreground mask
Mat getForegroundMask(const Mat& background, const Mat& frame);

// Calculate centers of interrsection of ball and fg mask
// Return center of intersection and ball_mask - intersection
std::pair<Point,Point> calculate_centers(Mat ball_mask, Mat frame_mask);

// Function that returns -1 if ball is in left goal, 1 if ball is in right goal, and 0 if ball is not in any
int ballInGoal(const Ball& ball, int cam_width);

#endif
