
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;


pair<Point,Point> calculate_centers(Mat ball_mask, Mat frame_mask) {
  for(int row = 0; row < frame_mask.rows; ++row) {
    uchar* p = frame_mask.ptr(row);
    for(int col = 0; col < frame_mask.cols; ++col) {
      cout << **ptr << endl;
      *p++;
    }
  }
}
