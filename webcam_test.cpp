#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <time.h>

#include "ball.h"

using namespace cv;
using namespace std;

// Estimate FPS of video stream based on 120 frame capture
double measureFPS(VideoCapture& vid_stream);

int main(int argc, char** argv) {
  VideoCapture cam_stream(0);
  if (!cam_stream.isOpened()) { //check if video device has been initialised
    cout << "cannot open camera";
  }
  int width = cam_stream.get(CV_CAP_PROP_FRAME_WIDTH);
  int height = cam_stream.get(CV_CAP_PROP_FRAME_HEIGHT);
  if (argc > 1 && !strcmp(argv[1], "fps"))
    cout << measureFPS(cam_stream) << endl;

  //Mat edges;
  namedWindow("Pong", 1);

  // Create ball at position 0,0
  int radius = 25;  // 50px ball radius
  Vec2f velocity{20,20};  // initial ball velocity
  Scalar color{255,255,255};  // white ball color
  Ball ball{width, height, radius, velocity, color};
  Vec3b ballCenter;

  Mat cameraFrame;
  while (true) {
    cam_stream.read(cameraFrame);  // read webcam frame
    ball.Update();
    ball.Draw(&cameraFrame);

    //CODE TO CANNY EDGE DETECTOR
    //cvtColor(cameraFrame, edges, CV_BGR2GRAY);
    //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
    //Canny(edges, edges, 0, 100, 3);

    //CODE TO ACCESS PIXELS
//     uchar r, g, b;
//     for(int i = 0; i < cameraFrame.rows; ++i){
//       Vec3b* pixel = cameraFrame.ptr<Vec3b>(i);
//       for(int j = 0; j < cameraFrame.cols; ++j){
//         pixel[j][0] = pixel[j][2];
//         pixel[j][2] = pixel[j][0];
//       }
//     }

    imshow("cameraFrame", cameraFrame);
    if(waitKey(30) >= 0) break;
  }
  return 0;
}

double measureFPS(VideoCapture& vid_stream) {
  cout << "Measuring FPS (this may take up to 10 seconds)" << endl;
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
  cout << "Time taken : " << seconds << " seconds" << endl;

  // Calculate frames per second
  double fps = num_frames/seconds;
  return fps;
}
