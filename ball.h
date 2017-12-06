#ifndef BALL_H
#define BALL_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

class Ball {
  public:
    Ball(int width, int height, int rad, Vec2f vel, const Scalar& col) :
                                          cam_width{width}, cam_height{height},
                                          position{Point(0,0)}, velocity{vel},
                                          radius{rad}, color{col} {}

    // update ball physics
    void Update();

    // Draw ball at Point(x,y) position with Scalar(r,g,b) colors on image
    void Draw(Mat* image);


  private:
    int cam_width, cam_height;
    Point position;
    Vec2f velocity;
    Scalar color;
    int radius;
};

#endif
