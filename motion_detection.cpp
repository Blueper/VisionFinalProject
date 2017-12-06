// porting to cpp from:
// http://www.robindavid.fr/opencv-tutorial/motion-detection-with-opencv.html
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

string type2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

int main() {
	int ceil_ = 15;
	VideoCapture capture_(0);
	if (! capture_.isOpened()) { cout << "can't find webcam\n"; }
	
	// Captures the first frame to get size
	Mat frame;
	capture_.read(frame);
	Size s = frame.size();

	int width = s.width;
	int height = s.height;
	int surface = width * height; // surface area of image
	int curSurface = 0; // hold current surface that have changed // wtf lol

	Mat color_image;
	Mat grey_image = Mat(height, width, CV_8UC1);
	Mat moving_average = Mat(height, width, CV_32FC3);
	Mat difference;
	// difference = None // wtf is this python bullshit lol
	
	while(true) {	
		capture_.read(color_image);
		GaussianBlur(color_image, color_image, Size(3, 3), 0, 0); // Removes false positives
		
		// For the first time, put values into difference, temp, & moving_average
		Mat temp;
		if (difference.empty()) {
			//difference = color_image.clone(); // Useless
			temp = color_image.clone();
			color_image.convertTo(moving_average, CV_32FC3, 1.0, 0.0);
		} else {
			accumulateWeighted(color_image, moving_average, 0.020);
		}
		
		// Convert the scale of the moving average
		moving_average.convertTo(temp, CV_8UC3);
		
		// cout << "temp: " << type2str(temp.type()) << endl;
		// cout << "color_image: " << type2str(color_image.type()) << endl;
		// cout << "difference: " << type2str(difference.type()) << endl;
		// cout << "moving_average: " <<type2str(difference.type()) << endl;
		
		// Minus the current frame from the moving average
		absdiff(color_image, temp, difference);
		
		
		// Convert the image so that it can be thresholded
		cvtColor(difference, grey_image, CV_BGR2GRAY);
		threshold(grey_image, grey_image, 70.0, 255.0, THRESH_BINARY);
		
		dilate(grey_image, grey_image, Mat(), Point(-1, -1), 30);
		//erode(grey_image, grey_image, Mat(), Point(-1, -1), 10); // Useless?
		
		// Find contours
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours(grey_image, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point());
		
		vector<vector<Point> > backcontours = contours; // Save contours
		
		// For all contours, compute the area
		vector<vector<Point> >:: iterator itr;
		double cursurface = 0.0; 
		for (itr = contours.begin(); itr != contours.end(); ++itr) {
			cursurface += contourArea(*itr);
		} 
		
		// Calculate the average of contour area on the total size
		int avg = (cursurface * 100) / surface;
		if (avg > ceil_) {
			cout << "Something is moving! ";
		} 
		// Set current surface back to 0
		cursurface = 0.0;
		
		// Draw the contours on the image
		Scalar color = Scalar(0, 255, 255);
		int maxLevel = 1;
		drawContours(color_image, backcontours, 0, color, 2, CV_FILLED, hierarchy, maxLevel, Point());
		
		imshow("Target", color_image);
		if(waitKey(30) >= 0) break;
	}
	return 0;
}
