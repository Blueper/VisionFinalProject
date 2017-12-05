#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
  VideoCapture stream1(0);

  if (!stream1.isOpened()) { //check if video device has been initialised
    cout << "cannot open camera";
  }

//  Mat edges;
//  namedWindow("edges", 1);
  int x = 25;
  int y = 25;
  int xMovement = 0;
  int yMovement = 0;
  int threshold = 50; //used to detect when an object makes contact with the ball
  int hitBuffer = 0; //manual timer to reset ball "hittability." Bad practice. should replace.
//  int xWallBuffer = 0;
//  int yWallBuffer = 0;
  Mat cameraFrame;
  stream1.read(cameraFrame);
  Vec3b current = cameraFrame.at<Vec3b>(Point(x,y));
  Vec3b previous = cameraFrame.at<Vec3b>(Point(x,y));
  while (true) {
//    Mat cameraFrame;
    stream1.read(cameraFrame);  // read webcam frame

    current = cameraFrame.at<Vec3b>(Point(x,y));
   
    //increment hit/wall buffers
    if(hitBuffer > 0) hitBuffer++;
    if(hitBuffer >= 10)	hitBuffer = 0;

    //Code to detect hit from boundary
    if( x <= 25 || x >= cameraFrame.cols || y <= 25 || y >= cameraFrame.rows){
        x = cameraFrame.cols/2;
	y = cameraFrame.rows/2;
	xMovement = 0;
	yMovement = 0;
    }

    //Code to detect hit from game object
    if((current[0]-previous[0] > threshold || previous[0]-current[0] > threshold
     ||current[1]-previous[1] > threshold || previous[1]-current[1] > threshold
     ||current[2]-previous[2] > threshold || previous[2]-current[2] > threshold)
     && hitBuffer == 0){
        cout << "HIT!" << endl;
	if(xMovement == 0 && yMovement == 0){	
		xMovement = 5; 
		yMovement = 5;
	}
	else{
		xMovement *= -1;
		yMovement *= -1;
	}
	hitBuffer = 1;
    }

   

//     cout << "M = "<< endl << " "  << cameraFrame.rows << ", "
//          << cameraFrame.cols << endl << endl;  //  image size
//     cout << cameraFrame.at<Vec3b>(Point(30,30)) << endl;  // RGB at x,y = 30,30

    //CODE TO CANNY EDGE DETECTOR
//     cvtColor(cameraFrame, edges, CV_BGR2GRAY);
//     GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
//     Canny(edges, edges, 0, 100, 3);

    //CODE TO ACCESS PIXELS
//     uchar r, g, b;
//     for(int i = 0; i < cameraFrame.rows; ++i){
//       Vec3b* pixel = cameraFrame.ptr<Vec3b>(i);
//       for(int j = 0; j < cameraFrame.cols; ++j){
//         pixel[j][0] = pixel[j][2];
//         pixel[j][2] = pixel[j][0];
//       }
//     }

    previous = cameraFrame.at<Vec3b>(Point(x,y));    

    //CODE TO DRAW A CIRCLE
    circle(cameraFrame, Point(x,y), 25, Scalar(255, 255, 255), -1);
    circle(cameraFrame, Point(x,y), 25, Scalar(0,0,0), 1, 8);
    x += xMovement;
    y += yMovement;

    imshow("cameraFrame", cameraFrame);
    if(waitKey(30) >= 0) break;
  }
  return 0;
}
