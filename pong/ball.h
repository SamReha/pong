#include <SFML/Graphics.hpp>
#include <math.h>

class Ball {
private:
  int width, height;
  double xvel, yvel, xpos, ypos;
  sf::Sprite sprite;
public:
  Ball(int w, int h, double x, double y, sf::Sprite spr);
  
  int getRadius();              // Returns radius of ball (width/2)
  double getXPos();                // Returns val of xPos
  double getYPos();                // Returns val of yPos
  double getXVel();
  double getYVel();
  void  move(double, double);         // Int represents number of pixels to move the paddle by
  sf::Sprite getSprite();       // Fetches the sprite obj associated with this paddle
  void computeVelocity(double);  // Based on reflection angle given by paddle, compute new velocity
  void bounceOffCeiling();      // Compute new velocity when recoiling from ceiling or floor
  bool offLeft();               // Returns true iff ball is off the left-hand side of screen
  bool offRight();              // Returns true iff ball is off the right-hand side of screen
  void reset(bool);             // Reset the ball to the center of the screen w/ random velocity. Set parameter false for leftward and true for rightward motion
  void update();                // Update the position of the ball based on the current velocity
};