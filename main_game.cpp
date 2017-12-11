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
  int threshold_value = 20;
  int hitBuffer = 0;
  int power = 0;

  Mat background;  // first frame (only background)
  Mat frame, blurred_frame;  // current frame, grayscale current frame
  Mat difference; // "motion detection" frame and ball mask
  Mat previous;
  Mat grey_frame;

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
  Vec2f velocity{0,0};  // initial ball velocity
  Scalar color{255,255,255};  // white ball color
  Ball ball{width, height, radius, 100, 100, velocity, color};

  int left_score = 0; //int to keep track of left score
  int right_score = 0; //int to keep track of right score

  Mat mirrorFrame;
  Mat cameraFrame;
  while (true) {
    cam_stream.read(mirrorFrame);  // read webcam frame
    flip(mirrorFrame, cameraFrame, 1);
    Mat fgmask = getForegroundMask(background, frame);

    cvtColor(cameraFrame, grey_frame, CV_BGR2GRAY); // convert to grayscale
    GaussianBlur(grey_frame, grey_frame, Size(21,21), 0); // remove noise   
    if(previous.empty()) grey_frame.copyTo(previous);
    absdiff(previous, grey_frame, difference);
    threshold(difference, difference, threshold_value, 255, THRESH_BINARY);

    //hitBuffer logic
    if(hitBuffer >= 10) hitBuffer = 0;
    if(hitBuffer > 0) hitBuffer++;   

    //detect ball hit
    int down = 0;
    int right = 0;
    if(hitBuffer == 0){
//	cout << "HIT CENTER" << endl;
	for(int i = -1*radius; i < radius; ++i){
	    for(int j = -1*radius; j < radius; ++j){
		if(difference.at<uchar>(Point(ball.GetPosition().x+i,ball.GetPosition().y+j)) > threshold_value){
		    if(i < 0 && j > 0){ //q3++;
			down--;
			right++;
		    }
		    if(i < 0 && j < 0){ //q2++;
			down++;
			right++;
		    }
		    if(i > 0 && j < 0){ //q1++;
			down++;
			right--;
		    }
		    if(i > 0 && j > 0){ //q4++;
			down--;
			right--;
		    }
		    power++;
		}
	    }
	}

	if(power > 100 && hitBuffer == 0 && ball.GetOutOfBounds() == false){
            ball.SetVelocity(right/20, down/20);
            hitBuffer++;
	}
	power = 0;
    }    
 
    ball.Update();
    int goal_status = ballInGoal(ball, width);
    if(goal_status!=0){

      if(goal_status==-1){
        left_score++;
        ball.Reset(2);
      }
      else if(goal_status==1){
        right_score++;
        ball.Reset(0);
      }
    }
    
    ball.Draw(&cameraFrame);

    drawText(cameraFrame, 0, 50, appendNumToText("SCORE: ", left_score));
    drawText(cameraFrame, width-300, 50, appendNumToText("SCORE: ", right_score));

//    difference.copyTo(cameraFrame);
   
    grey_frame.copyTo(previous);

    imshow("Pong", cameraFrame);
//    imshow("Pong", ball_mask);
//    imshow("Pong", fgmask);
//    imshow("Pong", difference);
    if(waitKey(30) >= 0) break;
  }
  return 0;
}

