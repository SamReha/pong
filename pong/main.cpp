
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

#include "paddle.h"
#include "ball.h"

// Prototypes

int main(int, char const**) {
  // Create the main window
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
  
  // Set the Icon
  sf::Image icon;
  if (!icon.loadFromFile(resourcePath() + "icon.png")) {
    return EXIT_FAILURE;
  }
  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  // Load sprites
  sf::Texture texture;
  if (!texture.loadFromFile(resourcePath() + "background.png")) {
    return EXIT_FAILURE;
  }
  sf::Sprite sprite(texture);
  
  sf::Texture paddle_tex;
  if (!paddle_tex.loadFromFile(resourcePath() + "paddle.png")) {
    return EXIT_FAILURE;
  }
  sf::Sprite paddle_spr(paddle_tex);
  
  sf::Texture ball_tex;
  if (!ball_tex.loadFromFile(resourcePath() + "ball.png")) {
    return EXIT_FAILURE;
  }
  sf::Sprite ball_spr(ball_tex);

  // Load font and initialize textual elements
  sf::Font font;
  if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
    return EXIT_FAILURE;
  }
  sf::Text left_score_text("0", font, 50);
  left_score_text.setColor(sf::Color::White);
  left_score_text.setPosition(150, 0);
  
  sf::Text right_score_text("0", font, 50);
  right_score_text.setColor(sf::Color::White);
  right_score_text.setPosition(600, 0);
  
  sf::Text end_text("ERROR", font, 50);
  
  // Declare / Initialize the game objects
  Paddle left_paddle(20, 100, 40, 300, paddle_spr);
  Paddle right_paddle(20, 100, 760, 300, paddle_spr);
  Ball ball(30, 30, 400.0, 300.0, ball_spr);

  // Load sound effects
  sf::SoundBuffer padd_contact_buffer;
  if (!padd_contact_buffer.loadFromFile(resourcePath() + "259703__kwahmah-02__onebeep.flac")) {
    return EXIT_FAILURE;
  }
  sf::Sound padd_contact_sound;
  padd_contact_sound.setBuffer(padd_contact_buffer);
  
  sf::SoundBuffer ceil_bounce_buffer;
  if (!ceil_bounce_buffer.loadFromFile(resourcePath() + "16023_harri_perc-beep.wav")) {
    return EXIT_FAILURE;
  }
  sf::Sound ceil_bounce_sound;
  ceil_bounce_sound.setBuffer(ceil_bounce_buffer);
  
  sf::SoundBuffer ball_offsides_buffer;
  if (!ball_offsides_buffer.loadFromFile(resourcePath() + "86101__scarkord__pss-bleep.wav")) {
    return EXIT_FAILURE;
  }
  sf::Sound ball_offsides_sound;
  ball_offsides_sound.setBuffer(ball_offsides_buffer);
  
  // Game Variables
  int left_score = 0;
  int right_score = 0;
  int player_speed = 2;
  bool paused = false;
  
  // Let's hack a button together, maybe I'll make a class later (becuase who wants to do events?)
  sf::Texture reset_tex;
  if (!reset_tex.loadFromFile(resourcePath() + "reset.png")) {
    return EXIT_FAILURE;
  }
  sf::Sprite reset_spr(reset_tex);
  reset_spr.setPosition(250, 375);
  sf::Rect<int> reset_rect(250, 375, 300, 150);
  
  sf::Mouse mouse;
  sf::Vector2<int> mousePosition;

  // Start the game loop
  ball.reset(true);
  while (window.isOpen()) {
    /** HANDLE EVENTS */
    sf::Event event;
    while (window.pollEvent(event)) {
      // Close window: exit
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      // Escape pressed: exit
      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        window.close();
      }
    }
    /** UPDATE ROUTINE */
    if (!paused) {
      // Check to see if one player has won
      if (left_score >= 10) {
        paused = true;
        end_text.setPosition(50, 250);
        end_text.setString("LEFT PLAYER\n VICTORY");
      } else if (right_score >= 10) {
        paused = true;
        end_text.setPosition(410, 250);
        end_text.setString("RIGHT PLAYER\n VICTORY");
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        left_paddle.move(-player_speed);
      } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        left_paddle.move(player_speed);
      }
    
      // Debug - Player 2! :D
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        right_paddle.move(-player_speed);
      } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        right_paddle.move(player_speed);
      }
    
      // Check if ball is colliding with paddles
      if (left_paddle.checkCollision(ball.getRadius(), ball.getXPos(), ball.getYPos())) {
        ball.computeVelocity(left_paddle.reflectionAngle(ball.getYPos()));
        padd_contact_sound.play();
      } else if (right_paddle.checkCollision(ball.getRadius(), ball.getXPos(), ball.getYPos())) {
        ball.computeVelocity(right_paddle.reflectionAngle(ball.getYPos()));
        padd_contact_sound.play();
      }
    
      // Check if ball has gone offside
      if (ball.offLeft()) {
        ball.reset(false);
        right_score += 1;
        right_score_text.setString(std::to_string(right_score));
        ball_offsides_sound.play();
      } else if (ball.offRight()) {
        ball.reset(true);
        left_score += 1;
        left_score_text.setString(std::to_string(left_score));
        ball_offsides_sound.play();
      }
    
      // Bounce the ball off the floor or ceiling
      if (ball.getYPos() < 0.0 || ball.getYPos() > 600.0) {
        ball.bounceOffCeiling();
        ceil_bounce_sound.play();
      }
    
      ball.update();
    } else {  // Else we are paused / gameovered
      // Check for mouse presses in the reset button.
      if (mouse.isButtonPressed(sf::Mouse::Button::Left)) {
        mousePosition = mouse.getPosition(window);
        if (reset_rect.contains(mousePosition.x, mousePosition.y)) {
          left_score = 0;
          right_score = 0;
          
          left_score_text.setString(std::to_string(left_score));
          right_score_text.setString(std::to_string(right_score));
          
          paused = false;
          ball.reset(true);
        }
      }
    }
    
    /** DRAW ROUTINE */
    window.clear();
    
    window.draw(sprite);
    window.draw(left_score_text);
    window.draw(right_score_text);
    window.draw(ball.getSprite());
    
    if (paused) {
      window.draw(end_text);
      window.draw(reset_spr);
    } else {
      window.draw(left_paddle.getSprite());
      window.draw(right_paddle.getSprite());
    }

    window.display();
  }

  return EXIT_SUCCESS;
}
