
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
  
  // Declare / Initialize the game objects
  Paddle left_paddle(20, 100, 40, 300, paddle_spr);
  Paddle right_paddle(20, 100, 760, 300, paddle_spr);
  Ball ball(30, 30, 400, 300, ball_spr);

  // Load a music to play
  sf::Music music;
  if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
    return EXIT_FAILURE;
  }

  // Play the music
  music.play();
  
  // Game Variables
  int left_score = 0;
  int right_score = 0;
  int player_speed = 2;

  // Start the game loop
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
    left_score_text.setString(std::to_string(left_score));
    right_score_text.setString(std::to_string(right_score));
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      left_paddle.move(-player_speed);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      left_paddle.move(player_speed);
    }
    
    /** DRAW ROUTINE */
    window.clear();
    
    window.draw(sprite);
    window.draw(left_score_text);
    window.draw(right_score_text);
    window.draw(left_paddle.getSprite());
    window.draw(right_paddle.getSprite());
    window.draw(ball.getSprite());

    window.display();
  }

  return EXIT_SUCCESS;
}
