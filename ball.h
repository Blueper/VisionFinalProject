#ifndef BALL_H
#define BALL_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

class Ball {
  public:
    Ball(int width, int height, int rad, int x, int y, Vec2f vel, const Scalar& col) :
            cam_width{width}, cam_height{height}, radius{rad},
            position{Point(x,y)}, velocity{vel}, color{col} {}

    // update ball physics
    void Update();

    // Draw ball at Point(x,y) position with Scalar(r,g,b) colors on image
    void Draw(Mat* image);

    //position getter and setter
    void SetPosition(int x, int y){
         position = Point(x,y);
    }
    Point GetPosition(){
	 return position;
    }

    //velocity getter and setter
    void SetVelocity(float x, float y){
	velocity = {x,y};
    }

    Vec2f GetVelocity(){
	return velocity;
    }

  private:
    int cam_width, cam_height;
    Point position;
    Vec2f velocity;
    Scalar color;
    int radius;
    bool out_of_bounds = false;
};

#endif
