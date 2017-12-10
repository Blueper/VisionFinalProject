#include "ball.h"

void Ball::Update() {
  position.x += velocity[0];
  position.y += velocity[1];

  // check bounds of camera only if not outside them
  if (!out_of_bounds) {
    if (position.x - radius <= 0 || position.x + radius >= cam_width) {
      velocity[0] *= -1;
      out_of_bounds = true;
    }
    if (position.y - radius <= 0 || position.y + radius >= cam_height) {
      velocity[1] *= -1;
      out_of_bounds = true;
    }
  }
  else {
    if (position.x - radius > 0 && position.x + radius < cam_width &&
        position.y - radius > 0 && position.y + radius < cam_height)
      out_of_bounds = false;
    }
}

void Ball::Draw(Mat* image) {
    circle(*image, position, radius, color, -1);
}
