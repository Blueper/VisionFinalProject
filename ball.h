#ifndef BALL_H
#define BALL_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>
#include <cmath>
using namespace cv;

class Ball {
  public:
    Ball(int width, int height, int rad, Vec2f vel, const Scalar& col) :
            cam_width{width}, cam_height{height}, radius{rad},
            position{Point(rad,rad)}, velocity{vel}, color{col} {}

    // Update ball physics
    void Update();

    // Draw ball at Point(x,y) position with Scalar(r,g,b) colors on image
    void Draw(Mat* image);

    // Reset velocity, and the position to the center of frame
    // LEFT = 0, NONE = 1, RIGHT = 2
    void Reset(int side);

    // Set Position
    void SetPosition(int x, int y) {
      position = Point(x,y);
    }

    // Get Position
    Point GetPosition() const{
	    return position;
    }

    // Set Velocity
    void SetVelocity(float x, float y) {
	    velocity = {x,y};
    }
  
    // Get Velocity
    Vec2f GetVelocity() {
	    return velocity;
    }
    
    // Get Radius
    int GetRadius() const{
      return radius;
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
