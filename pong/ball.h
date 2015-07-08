#include <SFML/Graphics.hpp>
#include <math.h>

class Ball {
private:
  int width, height, xpos, ypos, xvel, yvel;
  sf::Sprite sprite;
public:
  Ball(int w, int h, int x, int y, sf::Sprite spr);
  
  void  move(int, int);         // Int represents number of pixels to move the paddle by
  sf::Sprite getSprite();       // Fetches the sprite obj associated with this paddle
  void computeVelocity(float);  // Based on reflection angle given by paddle, compute new velocity
  void bounceOffCeiling();      // Compute new velocity when recoiling from ceiling or floor
  bool offLeft();               // Returns true iff ball is off the left-hand side of screen
  bool offRight();              // Returns true iff ball is off the right-hand side of screen
  void reset(bool);             // Reset the ball to the center of the screen w/ random velocity. Set parameter false for leftward and true for rightward motion
  void update();                // Update the position of the ball based on the current velocity
};