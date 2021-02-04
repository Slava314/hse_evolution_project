#include <SFML/Graphics.hpp>
#include "button.h"

int main() {
    sf::RenderWindow start_window(sf::VideoMode(1000, 800), "Start_window", sf::Style::Default);

    sf::Font font;
    font.loadFromFile("../times.ttf");

    Text_Button start_button(sf::Vector2f(200, 40), "Start", font);
    start_button.set_color(sf::Color(55, 55, 55));
    start_button.set_position(
            sf::Vector2f((start_window.getSize().x - start_button.get_shape().getSize().x) / 2.0,
                         (start_window.getSize().y -
                          start_button.get_shape().getSize().y) / 2.0));

    //start_button.set_text_size(20);

    while (start_window.isOpen()) {
        sf::Event event;
        while (start_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                start_window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if(start_button.is_clicked(sf::Mouse::getPosition(start_window))){
                        start_window.close();
                    }
                }
            }
        }


        start_window.clear();
        start_window.draw(start_button.get_shape());
        start_window.draw(start_button.get_text());
        start_window.display();
    }

    return 0;
}