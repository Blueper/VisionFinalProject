#include "ball.h"

void Ball::Update() {
  position.x += velocity[0];
  position.y += velocity[1];

  // check bounds of camera only if not outside them
  if (!out_of_bounds) {
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
  circle(*image, position, radius, (0,0,0), 3);
}

void Ball::Reset(int side) {
  SetPosition(cam_width/2, cam_height/2);

  int radius = 30;  // velocity magnitude
  
  srand(time(NULL));
  int rand_side = rand() % 2; 
  
  int y = rand() % (radius * 2) - radius;
  int x = sqrt(pow(radius, 2) - pow(y, 2));

  if (side == 0) {
	x *= -1;
  } else if (side == 1) {
    if (rand_side == 0)
      x *= -1; 
  }

  SetVelocity(float(x), float(y));
}
