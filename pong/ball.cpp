#include "ball.h"

#include <SFML/Graphics.hpp>
#include <math.h>

#define PI 3.14159265

Ball::Ball(int w, int h, double x, double y, sf::Sprite spr) {
  xvel = 0.0;
  yvel = 0.0;
  speed_multiplier = 1;
  
  width = w;
  height = h;
  xpos = x;
  ypos = y;
  sprite = spr;
  sprite.setPosition(xpos-w/2, ypos-h/2);
}

int _clamp(double val, double min, double max) {
  if (val < min) {
    val = min;
  } else if (val > max) {
    val = max;
  }
  return val;
}

int Ball::getRadius() {
  return width/2;
}

double Ball::getXPos() {
  return xpos;
}

double Ball::getYPos() {
  return ypos;
}

double Ball::getXVel() {
  return xvel;
}

double Ball::getYVel() {
  return yvel;
}

void Ball::bumpUpSpeed() {
  speed_multiplier = speed_multiplier < 4.0 ? speed_multiplier + 0.2 : speed_multiplier;
}

void Ball::move(double newX, double newY) {
  xpos = newX;
  ypos = newY;
  
  sprite.setPosition(xpos-(width/2), ypos-(height/2));
}

sf::Sprite Ball::getSprite() {
  return sprite;
}

void Ball::computeVelocity(double reflectionAngle) {
  int multiplier = 1.0;
  if (xvel > 0.0) {
    multiplier = -1.0;
  }
  xvel = fabs(cosf(reflectionAngle*PI/180)) * speed_multiplier;
  yvel = sinf(reflectionAngle*PI/180)*(-1) * speed_multiplier;
  
  xvel = xvel*(multiplier);
}

void Ball::bounceOffCeiling() {
  yvel = yvel*(-1.0);
}

bool Ball::offLeft() {
  if (xpos < 0.0) {
    return true;
  } else return false;
}

bool Ball::offRight() {
  if (xpos > 800.0) {     // Magic numbers suck, but we can safely assume the screen will always be 800 wide
    return true;
  } else return false;
}

void Ball::reset(bool direction) {
  xpos = 400.0;
  ypos = 300.0;
  sprite.setPosition(xpos-(width/2), ypos-(height/2));
  
  // Compute new velocity with random angle
  double reflectionAngle = rand() % 51 + (-45);
  int multiplier = 1.0;
  
  if (direction) {
    multiplier = -1.0;
  }
  xvel = fabs(cosf(reflectionAngle*PI/180));
  yvel = sinf(reflectionAngle*PI/180)*(-1);
  
  speed_multiplier = 1;
  
  xvel = xvel*(multiplier);
}

void Ball::update() {
  xpos = xpos + xvel;
  ypos = ypos + yvel;
  
  sprite.setPosition(xpos-(width/2), ypos-(height/2));
}