class Paddle {
  int width, height, xpos, ypos;
public:
  void  move(int);  // Int represents number of pixels to move the paddle by
  float reflectionAngle(int); // returns what angle the ball should be bounced back at, depending on the ball's y position
  bool  checkCollision(int, int, int);  // returns true if a ball of a certain position and radiusis impacting this paddle
} Paddle;