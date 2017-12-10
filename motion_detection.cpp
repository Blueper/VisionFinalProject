// porting to cpp from:
//www.pyimagesearch.com/2015/05/25/basic-motion-detection-and-tracking-with-python-and-opencv
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ball.h"
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

//next: add all pixels to array and check all for whiteness

int main() {
  int ceil_ = 500;
  VideoCapture capture_(0);
  if (!capture_.isOpened()) { cout << "can't find webcam\n"; }

  Mat background;  // first frame (only background)
  Mat frame, grey_frame;  // current frame, grayscale current frame
  Mat difference;  // difference of background and current frame
  int threshold_value = 20; //threshold to use when creating the binary image

  // Create ball at position 0,0
  int width = capture_.get(CV_CAP_PROP_FRAME_WIDTH);
  int height = capture_.get(CV_CAP_PROP_FRAME_HEIGHT);
  int radius = 25;  // 50px ball radius
  int power = 0;
  Vec2f velocity{0,0};  // initial ball velocity
  Scalar color{255,255,255};  // white ball color
  Ball ball{width, height,100, 100, radius, velocity, color};
  Vec3b ballCenter;
  int hitBuffer = 0;
//  Mat hitPixels;

  while(true) {
    capture_.read(frame);
    cvtColor(frame, grey_frame, CV_BGR2GRAY);  // convert to grayscale
    GaussianBlur(grey_frame, grey_frame, Size(9,9), 0);  // remove noise
    ball.Update();
//    ball.SetPosition(100,100);
    ball.Draw(&frame);

    // For the first time, store the background
    if (background.empty()) {
      grey_frame.copyTo(background);
      continue;
    }


//cout << difference.at<uchar>Point(10,10)[0]; 

    // make the difference image binary
    threshold(difference, difference, threshold_value, 255, THRESH_BINARY);
   
    if(hitBuffer >= 10) hitBuffer = 0;
    if(hitBuffer > 0) hitBuffer++;

//    cout << ball.GetVelocity()[0] << " " << ball.GetVelocity()[1] << endl;

    // get the difference between the background and the current frame
    absdiff(background, grey_frame, difference);
    ballCenter = difference.at<uchar>(ball.GetPosition());
    if(ballCenter[0] > threshold_value && hitBuffer == 0){
	cout << "HIT CENTER" << endl;
	//cout << difference.at<Vec3b>(ball.GetPosition().x,ball.GetPosition().y)[0] << endl;
	for(int i = -1*radius; i < radius ; ++i){
		for(int j = -1*radius; j < radius; ++j){
			if(difference.at<uchar>(Point(ball.GetPosition().x+i,ball.GetPosition().y+j)) > threshold_value){
				power++;
			}
		}
	}
	ball.SetVelocity(power/100,0);
	cout << power << endl;
	power = 0;
	hitBuffer++;
    }
 
    //get the grey frame for the next image
    grey_frame.copyTo(background);

    //detect hits

//    imshow("Target", difference);
//    imshow("Target", grey_frame);
    imshow("Target", frame);
    if(waitKey(30) >= 0) break;
  }
  return 0;
}
