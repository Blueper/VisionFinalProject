#include "opencvfuncs.h"

double measureFPS(VideoCapture& vid_stream) {
  std::cout << "Measuring FPS (this may take up to 10 seconds)" << std::endl;
  // Number of frames to capture
  int num_frames = 120;

  // Start and end times
  time_t start, end;

  // Variable for storing video frames
  Mat frame;

  // Start time
  time(&start);
  // Grab a few frames
  for(int i = 0; i < num_frames; i++) {
      vid_stream >> frame;
  }
  // End Time
  time(&end);

  // Time elapsed
  double seconds = difftime(end, start);
  std::cout << "Time taken : " << seconds << " seconds" << std::endl;

  // Calculate frames per second
  double fps = num_frames/seconds;
  return fps;
}

void drawText(Mat& image, int x, int y, const std::string& text){
  putText(image, text, Point(x,y), FONT_HERSHEY_DUPLEX, 2, cvScalar(255,255,255), 1, CV_AA);
}

std::string appendNumToText(std::string text, int num){
  std::ostringstream oss;
  oss << num;
  text+= oss.str();
  return text;
}

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

std::pair<Point,Point> calculate_centers(Mat ball_mask, Mat frame_mask) {
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
  return std::make_pair(Point(x_center/area, y_center/area),
                        Point(x_center_int/int_area, y_center_int/int_area));
}
