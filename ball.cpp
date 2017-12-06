#include "ball.h"

void Ball::Update() {
  position.x += velocity[0];
  position.y += velocity[1];
  if (position.x <= 0) velocity[0] *= -1;
  if (position.x >= cam_width) velocity[0] *= -1;
  if (position.y <= 0) velocity[1] *= -1;
  if (position.y >= cam_height) velocity[1] *= -1;
}

void Ball::Draw(Mat* image) {
    circle(*image, position, radius, color, -1);
}
