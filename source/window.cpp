#include "window.h"
#include <cassert>
std::unique_ptr<Window> Start_Window::handle_events() {
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    return nullptr;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (start_button.is_clicked(sf::Mouse::getPosition(window))) {
                            window.close();
                            return std::make_unique<Game_Window>();
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        window.clear();
        //        sf::Font font;
        //        font.loadFromFile("../times.ttf");
        //        sf::Text text("start", font);
        draw();
        //        window.draw(text);

        window.display();
    }
    assert(false);
}

void Start_Window::make_start_button() {
    sf::Font font;
    font.loadFromFile("../times.ttf");
    start_button = Text_Button(sf::Vector2f(200, 40), "Start", font);
    start_button.set_color(sf::Color(55, 55, 55));
    start_button.set_position(
        sf::Vector2f((window.getSize().x - start_button.get_shape().getSize().x) / 2.0,
                     (window.getSize().y - start_button.get_shape().getSize().y) / 2.0));
}
void Start_Window::draw() {
    start_button.draw(window);
}
std::unique_ptr<Window> Game_Window::handle_events() {
    return nullptr;
}
void Game_Window::draw() {
}
