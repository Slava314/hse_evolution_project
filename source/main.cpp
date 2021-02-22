#include "window.h"

int main() {
    std::unique_ptr<Window> window = std::make_unique<Start_Window>();

    while (window) {
        std::unique_ptr<Window> new_window = window->handle_events();
        window.swap(new_window);
    }
//    constexpr int WINDOW_WIDTH1 = 1800;
//    constexpr int WINDOW_HEIGHT1 = 1000;
//
//    sf::RenderWindow start_window(sf::VideoMode(WINDOW_WIDTH1, WINDOW_HEIGHT1), "Start_window",
//                                  sf::Style::Titlebar | sf::Style::Close);
//    start_window.setPosition({50, 50});
//
//    sf::Font font;
//    font.loadFromFile("../t.ttf");
//
//    Text_Button start_button(sf::Vector2f(200, 40), "Start", font);
//    start_button.set_color(sf::Color(55, 55, 55));
//    start_button.set_position(
//        sf::Vector2f((start_window.getSize().x - start_button.get_shape().getSize().x) / 2.0,
//                     (start_window.getSize().y - start_button.get_shape().getSize().y) / 2.0));
//
//    bool new_window = false;
//
//    while (start_window.isOpen()) {
//        sf::Event event;
//        while (start_window.pollEvent(event)) {
//            switch (event.type) {
//                case sf::Event::Closed:
//                    start_window.close();
//                    break;
//                case sf::Event::MouseButtonPressed:
//                    if (event.mouseButton.button == sf::Mouse::Left) {
//                        if (start_button.is_clicked(sf::Mouse::getPosition(start_window))) {
//                            new_window = true;
//                            start_window.close();
//                        }
//                    }
//                    break;
//                default:
//                    break;
//            }
//        }
//        start_window.clear();
//        start_window.draw(start_button.get_shape());
//        start_window.draw(start_button.get_text());
//        start_window.display();
//    }

    return 0;
}