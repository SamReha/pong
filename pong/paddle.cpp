#include "paddle.h"

#include <SFML/Graphics.hpp>
#include <math.h>

Paddle::Paddle(int w, int h, int x, int y, sf::Sprite spr) {
  width = w;
  height = h;
  xpos = x;
  ypos = y;
  sprite = spr;
  sprite.setPosition(xpos-w/2, ypos-h/2);
}

int clamp(int val, int min, int max) {
  if (val < min) {
    val = min;
  } else if (val > max) {
    val = max;
  }
  return val;
}

void Paddle::move(int amount) {
  ypos = clamp(ypos+amount, height/2, 600-(height/2));  // Magic numbers suck, but we can safely assume the screen will always be 600 tall.
  
  sprite.setPosition(xpos-(width/2), ypos-(height/2));
}

void Paddle::setPosition(int newX, int newY) {
  xpos = newX;
  ypos = newY;
  
  sprite.setPosition(xpos-(width/2), ypos-(height/2));
}

float Paddle::reflectionAngle(int ballY) {
  int yDistance = ypos - ballY;
  return (float(yDistance) / float(height)/2.0)*45;
}

sf::Sprite Paddle::getSprite() {
  return sprite;
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