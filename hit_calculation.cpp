#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;


pair<Point,Point> calculate_centers(Mat ball_mask, Mat frame_mask) {
  int x_center = 0, y_center = 0, x_center_int = 0, y_center_int = 0,
      area = 0, int_area = 0;
  for(int row = 0; row < frame_mask.rows; ++row) {
    uchar* frame_p = frame_mask.ptr(row);
    uchar* ball_p = ball_mask.ptr(row);
    for(int col = 0; col < frame_mask.cols; ++col) {
      if (frame_p[col] == ball_p[col]) {
        x_center_int += col;
        y_center_int += row;
        int_area++;
      }
      else if (ball_p[col] != 0) {
        x_center += col;
        y_center += row;
        area++;
      }
      *frame_p++;
      *ball_p++;
    }
  }
  return make_pair(Point(x_center/area, y_center/area),
                   Point(x_center_int/int_area, y_center_int/int_area));
}
