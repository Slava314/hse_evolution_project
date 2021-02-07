#include <SFML/Graphics.hpp>
#include "button.h"
#include <vector>

int main() {
  constexpr int WINDOW_WIDTH = 1800;
  constexpr int WINDOW_HEIGHT = 1000;

  sf::RenderWindow
      start_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Start_window", sf::Style::Titlebar | sf::Style::Close);
  start_window.setPosition({50, 50});

  sf::Font font;
  font.loadFromFile("../times.ttf");

  Text_Button start_button(sf::Vector2f(200, 40), "Start", font);
  start_button.set_color(sf::Color(55, 55, 55));
  start_button.set_position(
      sf::Vector2f((start_window.getSize().x - start_button.get_shape().getSize().x) / 2.0,
                   (start_window.getSize().y -
                       start_button.get_shape().getSize().y) / 2.0));

  bool new_window = false;

  while (start_window.isOpen()) {
    sf::Event event;
    while (start_window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:start_window.close();
          break;
        case sf::Event::MouseButtonPressed:
          if (event.mouseButton.button == sf::Mouse::Left) {
            if (start_button.is_clicked(sf::Mouse::getPosition(start_window))) {
              new_window = true;
              start_window.close();
            }
          }
          break;
        default:break;
      }
    }
    start_window.clear();
    start_window.draw(start_button.get_shape());
    start_window.draw(start_button.get_text());
    start_window.display();
  }

  if (new_window) {

    //TODO создание игры с колодой игроками и тд наверное в другой файл вообще всё надо вынести

    sf::RenderWindow
        game_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game_window", sf::Style::Titlebar | sf::Style::Close);

    constexpr int CARD_WIDTH = 100;
    constexpr int CARD_HEIGHT = 150;
    constexpr int LEFT_WIDTH = 50;

    sf::RectangleShape left({LEFT_WIDTH, WINDOW_HEIGHT / 2});
    left.setPosition(0, WINDOW_HEIGHT / 4);
    left.setFillColor(sf::Color(55, 55, 55));

    sf::Text food_count("food: 0", font);

    sf::RectangleShape deck_shape({CARD_WIDTH, CARD_HEIGHT});
    deck_shape.setFillColor(sf::Color(73, 215, 115));
    deck_shape.setOutlineThickness(5);
    deck_shape.setOutlineColor(sf::Color(4, 137, 44));
    deck_shape.setPosition((WINDOW_WIDTH - CARD_WIDTH) / 2.0, (WINDOW_HEIGHT - CARD_HEIGHT) / 2.0 - 150);

    sf::Text deck_text("deck: 0", font); //TODO get number of cards in deck
    deck_text.setCharacterSize(28);

    deck_text.setPosition(deck_shape.getPosition().x + (CARD_WIDTH - deck_text.getGlobalBounds().width) / 2.0,
                          deck_shape.getPosition().y);

    std::vector<Button> player_cards(6, Button({CARD_WIDTH, CARD_HEIGHT}));
    int free_space = 20;
    int left_point = (WINDOW_WIDTH - CARD_WIDTH * player_cards.size() - free_space * (player_cards.size() - 1)) / 2;
    for (int i = 0; i < player_cards.size(); ++i) {
      player_cards[i].set_color(sf::Color(73, 215, 115));
      player_cards[i].set_outline_thickness(5);
      player_cards[i].set_outline_color(sf::Color(4, 137, 44));
      player_cards[i].set_position(sf::Vector2f(left_point + (free_space + CARD_WIDTH) * i,
                                                WINDOW_HEIGHT - CARD_HEIGHT - 50));
    }

    while (game_window.isOpen()) {
      sf::Event event;
      while (game_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          game_window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
          if (event.mouseButton.button == sf::Mouse::Left) {
            for (int i = 0; i < player_cards.size(); ++i) {
              if (player_cards[i].is_clicked(sf::Mouse::getPosition(game_window))) {
//                player_cards.erase(std::next(player_cards.begin(), i));
//                left_point =
//                    (WINDOW_WIDTH - CARD_WIDTH * player_cards.size() - free_space * (player_cards.size() - 1)) / 2;
//                for (int j = 0; j < player_cards.size(); ++j) {
//                  player_cards[j].set_position(sf::Vector2f(left_point + (free_space + CARD_WIDTH) * j,
//                                                            WINDOW_HEIGHT - CARD_HEIGHT - 50));
//                }
                player_cards[i].deactivate();
                break;
              }
            }
          }
        }
      }

      game_window.clear();
      game_window.draw(deck_shape);
      game_window.draw(deck_text);
      for (auto card : player_cards) {
        game_window.draw(card.get_shape());
      }
      game_window.draw(left);
      game_window.display();
    }
  }

  return 0;
}