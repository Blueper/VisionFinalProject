#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <time.h>

#include "opencvfuncs.h"
#include "ball.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
  VideoCapture cam_stream(0);
  if (!cam_stream.isOpened()) { cout << "cannot open webcam\n"; }
  int width = cam_stream.get(CV_CAP_PROP_FRAME_WIDTH);
  int height = cam_stream.get(CV_CAP_PROP_FRAME_HEIGHT);

  Mat background;  // first frame (only background)
  Mat frame, blurred_frame;  // current frame, grayscale current frame

  if (argc > 1 && !strcmp(argv[1], "fps"))
    cout << measureFPS(cam_stream) << endl;

  // warm camera up and cache background
  int warmup_frames = 5;
  for (int initial_frames = 0; initial_frames < warmup_frames; initial_frames++) {
    cam_stream.read(frame);
    flip(frame, frame, 1);
    if (initial_frames == warmup_frames-1) {
      GaussianBlur(frame, blurred_frame, Size(21,21), 0);  // remove noise
      blurred_frame.copyTo(background);
    }
  }

  // Create ball at position 0,0
  int radius = 25;  // 50px ball radius
  Vec2f velocity{20,20};  // initial ball velocity
  Scalar color{255,255,255};  // white ball color
  Ball ball{width, height, radius, velocity, color};

  Mat cameraFrame;
  while (true) {
    cam_stream.read(cameraFrame);  // read webcam frame
    Mat fgmask = getForegroundMask(background, frame);

    ball.Update();
    ball.Draw(&cameraFrame);

    imshow("Pong", cameraFrame);
    if(waitKey(30) >= 0) break;
  }
  return 0;
}

