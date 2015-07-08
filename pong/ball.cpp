#include "ball.h"

#include <SFML/Graphics.hpp>
#include <math.h>

Ball::Ball(int w, int h, int x, int y, sf::Sprite spr) {
  width = w;
  height = h;
  xpos = x;
  ypos = y;
  xvel = 0;
  yvel = 0;
  sprite = spr;
  sprite.setPosition(xpos-w/2, ypos-h/2);
}

int _clamp(int val, int min, int max) {
  if (val < min) {
    val = min;
  } else if (val > max) {
    val = max;
  }
  return val;
}

void Ball::move(int newX, int newY) {
  xpos = newX;
  ypos = newY;
  
  sprite.setPosition(xpos-(width/2), ypos-(height/2));
}

sf::Sprite Ball::getSprite() {
  return sprite;
}

void Ball::computeVelocity(float reflectionAngle) {
  
}

void Ball::bounceOffCeiling() {
  yvel = yvel*(-1);
}

bool Ball::offLeft() {
  if (xpos < 0) {
    return true;
  } else return false;
}

bool Ball::offRight() {
  if (xpos > 800) {     // Magic numbers suck, but we can safely assume the screen will always be 800 wide
    return true;
  } else return false;
}

void Ball::reset(bool direction) {
  xpos = 400;
  ypos = 300;
  sprite.setPosition(xpos-(width/2), ypos-(height/2));
  
  // Compute new velocity with random angle
}

void Ball::update() {
  xpos += xvel;
  ypos += yvel;
  
  sprite.setPosition(xpos-(width/2), ypos-(height/2));
}