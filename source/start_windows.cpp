#include <window.h>
#include <cassert>
#include <memory>
#include "TextField.h"
std::unique_ptr<Window> StartWindow::handle_events() {
    while (window.isOpen()) {
        sf::Event event{};
        if (window.waitEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    return nullptr;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (start_button.is_clicked(sf::Mouse::getPosition(window))) {
                            window.close();
                            return std::make_unique<StartChoiceWindow>();
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        draw();
    }
    assert(false);
}

void StartWindow::init_window() {
    start_button = TextButton(sf::Vector2f(200, 40), sf::Text("Start", font));
    start_button.set_color(sf::Color(55, 55, 55));
    start_button.set_position(
        sf::Vector2f((window.getSize().x - start_button.get_shape().getSize().x) / 2.0,
                     (window.getSize().y - start_button.get_shape().getSize().y) / 2.0));
}
void StartWindow::draw() {
    window.clear();
    start_button.draw(window);
    window.display();
}

std::unique_ptr<Window> StartChoiceWindow::handle_events() {
    while (window.isOpen()) {
        sf::Event event{};
        if (window.waitEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    return nullptr;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (default_button.is_clicked(sf::Mouse::getPosition(window))) {
                            window.close();
                            return std::make_unique<GameWindow>();
                        }
                    }
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (make_game_button.is_clicked(sf::Mouse::getPosition(window))) {
                            window.close();
                            return std::make_unique<GameWindow>();
                        }
                    }
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (join_game_button.is_clicked(sf::Mouse::getPosition(window))) {
                            window.close();
                            return std::make_unique<JoinGameWindow>();
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        draw();
    }
    assert(false);
}

void StartChoiceWindow::init_window() {
    default_button = TextButton(sf::Vector2f(200, 40), sf::Text("Start", font));
    default_button.set_color(sf::Color(55, 55, 55));
    default_button.set_position(
        sf::Vector2f((window.getSize().x - default_button.get_shape().getSize().x) / 2.0,
                     (window.getSize().y - default_button.get_shape().getSize().y) / 2.0 + 100));
    make_game_button = TextButton(sf::Vector2f(200, 40), sf::Text("Make game", font));
    make_game_button.set_color(sf::Color(55, 55, 55));
    make_game_button.set_position(
        sf::Vector2f((window.getSize().x - 2 * make_game_button.get_shape().getSize().x) / 2.0 - 20,
                     (window.getSize().y - make_game_button.get_shape().getSize().y) / 2.0));
    join_game_button = TextButton(sf::Vector2f(200, 40), sf::Text("Join game", font));
    join_game_button.set_color(sf::Color(55, 55, 55));
    join_game_button.set_position(
        sf::Vector2f((window.getSize().x - 2 * join_game_button.get_shape().getSize().x) / 2.0 +
                         20 + make_game_button.get_shape().getSize().x,
                     (window.getSize().y - join_game_button.get_shape().getSize().y) / 2.0));
}

void StartChoiceWindow::draw() {
    window.clear();
    default_button.draw(window);
    make_game_button.draw(window);
    join_game_button.draw(window);
    window.display();
}
std::unique_ptr<Window> JoinGameWindow::handle_events() {
    while (window.isOpen()) {
        sf::Event event{};
        if (window.waitEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    return nullptr;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (text_field.is_clicked(sf::Mouse::getPosition(window))) {
                            text_field.set_focus(true);
                        } else {
                            text_field.set_focus(false);
                        }
                    }
                    break;
                case sf::Event::TextEntered:
                    text_field.handle_input(event);
                    break;
                default:
                    break;
            }
        }
        draw();
    }
    assert(false);
}
void JoinGameWindow::init_window() {
    text_field = TextField(20);
    text_field.set_position(sf::Vector2f((window.getSize().x - text_field.get_shape().getSize().x) / 2.0,
                                         (window.getSize().y - text_field.get_shape().getSize().y) / 2.0));
}
void JoinGameWindow::draw() {
    window.clear();
    text_field.draw(window);
    window.display();
}
std::unique_ptr<Window> MakeGameWindow::handle_events() {
    return std::unique_ptr<Window>();
}
void MakeGameWindow::init_window() {
}
void MakeGameWindow::draw() {
}
