#include "paddle.h"

#include <SFML/Graphics.hpp>
#include <math.h>

/*class Paddle {
  int width, height, xpos, ypos;
  sf::Sprite sprite;
public:
  Paddle(int w, int h, int x, int y, sf::Sprite spr);
  
  void  move(int);                     // Int represents number of pixels to move the paddle by
  void  setPosition(int, int);         // Set the paddle to a specific position (x, y)
  float reflectionAngle(int);          // returns what angle the ball should be bounced back at, depending on the ball's y position
  bool  checkCollision(int, int, int); // returns true if a ball of a certain position and radius is impacting this paddle
};*/

Paddle::Paddle(int w, int h, int x, int y, sf::Sprite spr) {
  width = w;
  height = h;
  xpos = x;
  ypos = y;
  sprite = spr;
}

void Paddle::move(int amount) {
  ypos += amount;
}

void Paddle::setPosition(int newX, int newY) {
  xpos = newX;
  ypos = newY;
}

float Paddle::reflectionAngle(int ballY) {
  int yDistance = ypos - ballY;
  return (float(yDistance) / float(height)/2.0)*45;
}

int clamp(int val, int min, int max) {
  if (val < min) {
    val = min;
  } else if (val > max) {
    val = max;
  }
  return val;
}

bool Paddle::checkCollision(int rad, int ballx, int bally) {
  bool isCollided = false;
  int farRight = xpos + floor(width/2);
  int farLeft = xpos - floor(width/2);
  int top = ypos - floor(height/2);
  int bottom = ypos + floor(height/2);
  
  // Find the closest point to the circle within the rectangle
  float closestX = clamp(ballx, farLeft, farRight);
  float closestY = clamp(bally, top, bottom);
  
  // Calculate the distance between the circle's center and this closest point
  float distanceX = ballx - closestX;
  float distanceY = bally - closestY;
  
  // If the distance is less than the circle's radius, an intersection occurs
  float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
  return distanceSquared < (rad * rad);
}