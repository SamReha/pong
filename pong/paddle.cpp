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

double clampf(double val, double min, double max) {
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

double Paddle::reflectionAngle(double ballY) {
  int yDistance = ypos - ballY;
  return clampf((2*double(yDistance) / double(height))*45, -45.0, 45.0);
}

sf::Sprite Paddle::getSprite() {
  return sprite;
}

bool Paddle::checkCollision(int rad, double ballx, double bally) {
  double farRight = xpos + (double)width/2.0;
  double farLeft = xpos - (double)width/2.0;
  double top = ypos - (double)floor(height/2);
  double bottom = ypos + (double)floor(height/2);
  
  // Find the closest point to the circle within the rectangle
  double closestX = clampf(ballx, farLeft, farRight);
  double closestY = clampf(bally, top, bottom);
  
  // Calculate the distance between the circle's center and this closest point
  double distanceX = ballx - closestX;
  double distanceY = bally - closestY;
  
  // If the distance is less than the circle's radius, an intersection occurs
  double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
  return distanceSquared < (rad * rad);
}