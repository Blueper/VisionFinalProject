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

int ballInGoal(const Ball& ball, int cam_width){
  Point curr_position = ball.GetPosition(); //storing the current position of the ball
  int radius = ball.GetRadius();
  if(curr_position.x - radius <= 0){
    return 1; //right goal
  }
  else if(curr_position.x + radius >= cam_width){
    return -1; //left goal
  }
  else{
    return 0; //not in goal
  }
}
