#include <SFML/Graphics.hpp>
#include "button.h"

int main() {
    sf::RenderWindow start_window(sf::VideoMode(1500, 1000), "Start_window", sf::Style::Default);

    sf::Font font;
    font.loadFromFile("../times.ttf");

    Text_Button start_button(sf::Vector2f(200, 40), "Start", font);
    start_button.set_color(sf::Color(55, 55, 55));
    start_button.set_position(
            sf::Vector2f((start_window.getSize().x - start_button.get_shape().getSize().x) / 2.0,
                         (start_window.getSize().y -
                          start_button.get_shape().getSize().y) / 2.0));


    bool new_window = 0;
    while (start_window.isOpen()) {
        sf::Event event;
        while (start_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                start_window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (start_button.is_clicked(sf::Mouse::getPosition(start_window))) {
                        new_window = 1;
                        start_window.close();
                    }
                }
            }

//            if (event.type == sf::Event::Resized) {
//                start_button.set_text_size(32);
//            }
        }


        start_window.clear();
        start_window.draw(start_button.get_shape());
        start_window.draw(start_button.get_text());
        start_window.display();
    }

    if (new_window) {

        //создание игры с колодой игроками и тд наверное в другой файл вообще всё надо вынести

        sf::RenderWindow game_window(sf::VideoMode(1500, 1000), "Game_window", sf::Style::Default);

        sf::RectangleShape deck_shape({140, 210});
        deck_shape.setFillColor(sf::Color(73, 215, 115));
        deck_shape.setOutlineThickness(5);
        deck_shape.setOutlineColor(sf::Color(4, 137, 44));

        deck_shape.setPosition((game_window.getSize().x - deck_shape.getSize().x) / 2.0f,
                               (game_window.getSize().y / 3.0f - deck_shape.getSize().y) / 2.0f);

        sf::Text deck_text("deck: 0", font); //need number of cards

        deck_text.setPosition(deck_shape.getPosition().x + (deck_shape.getSize().x - deck_text.getGlobalBounds().width) / 2.0f,
                              deck_shape.getPosition().y);



        while (game_window.isOpen()) {
            sf::Event event;
            while (game_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    game_window.close();
            }


            game_window.clear();
            game_window.draw(deck_shape);
            game_window.draw(deck_text);
            game_window.display();
        }
    }

    return 0;
}