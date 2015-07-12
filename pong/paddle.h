#include <SFML/Graphics.hpp>
#include <math.h>

class Paddle {
private:
  int width, height, xpos, ypos;
  sf::Sprite sprite;
public:
  Paddle(int w, int h, int x, int y, sf::Sprite spr);
  
  void  move(int);                     // Int represents number of pixels to move the paddle by
  void  setPosition(int, int);         // Set the paddle to a specific position (x, y)
  double reflectionAngle(double);          // returns what angle the ball should be bounced back at, depending on the ball's y position
  bool  checkCollision(int, double, double); // returns true if a ball of a certain position and radius is impacting this paddle
  sf::Sprite getSprite();              // Fetches the sprite obj associated with this paddle
};