#include <window.h>
#include <cassert>
#include <memory>
#include "text_field.h"
#include <string>

namespace {
void check_text_field(TextField &field, sf::RenderWindow &window) {
    if (field.is_clicked(sf::Mouse::getPosition(window))) {
        field.set_focus(true);
    } else {
        field.set_focus(false);
    }
}
}  // namespace

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
                        if (make_game_button.is_clicked(sf::Mouse::getPosition(window))) {
                            window.close();
                            return std::make_unique<MakeGameWindow>();
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
                        check_text_field(room_field, window);
                        check_text_field(name_field, window);
                        if (join_button.is_clicked(sf::Mouse::getPosition(window))) {
                            if (room_field.get_text() != "" && name_field.get_text() != "") {
                                // TODO join room?
                            }
                        }
                    }
                    break;
                case sf::Event::TextEntered:
                    room_field.handle_input(event);
                    name_field.handle_input(event);
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
    room_field = TextField(20, "meow");
    room_field.set_additional_text("Enter room name:");
    room_field.set_position(
        sf::Vector2f((window.getSize().x - 2 * room_field.get_shape().getSize().x) / 2.0 - 20,
                     (window.getSize().y - room_field.get_shape().getSize().y) / 2.0));
    name_field = TextField(20, "no name");
    name_field.set_additional_text("Enter your name:");
    name_field.set_position(
        sf::Vector2f((window.getSize().x - 2 * name_field.get_shape().getSize().x) / 2.0 +
                         name_field.get_shape().getSize().x + 20,
                     (window.getSize().y - room_field.get_shape().getSize().y) / 2.0));
    join_button = TextButton(sf::Vector2f(200, 40), sf::Text("Join", font));
    join_button.set_color(sf::Color(55, 55, 55));
    join_button.set_position(
        sf::Vector2f((window.getSize().x - join_button.get_shape().getSize().x) / 2.0,
                     (window.getSize().y - join_button.get_shape().getSize().y) / 2.0 + 100));
}

void JoinGameWindow::draw() {
    window.clear();
    room_field.draw(window);
    name_field.draw(window);
    join_button.draw(window);
    window.display();
}

std::unique_ptr<Window> MakeGameWindow::handle_events() {
    while (window.isOpen()) {
        sf::Event event{};
        if (window.waitEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    return nullptr;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        check_text_field(room_field, window);
                        check_text_field(name_field, window);
                        check_text_field(number_of_players_field, window);
                        check_text_field(number_of_cards_field, window);
                        check_text_field(seconds_for_turn_field, window);
                        if (start_button.is_clicked(sf::Mouse::getPosition(window))) {
                            if (room_field.get_text() != "" && name_field.get_text() != "" &&
                                number_of_players_field.get_text() != "" &&
                                number_of_cards_field.get_text() != "" &&
                                seconds_for_turn_field.get_text() != "") {
                                Settings settings(
                                    room_field.get_text(),
                                    std::stoi(number_of_players_field.get_text()),
                                    std::stoi(number_of_cards_field.get_text()),
                                    std::stoi(seconds_for_turn_field.get_text()));
                                window.close();
                                return std::make_unique<GameWindow>(settings);
                                // TODO make room?
                            }
                        }
                    }
                    break;
                case sf::Event::TextEntered:
                    room_field.handle_input(event);
                    name_field.handle_input(event);
                    number_of_cards_field.handle_input(event);
                    number_of_players_field.handle_input(event);
                    seconds_for_turn_field.handle_input(event);
                    break;
                default:
                    break;
            }
        }
        draw();
    }
    assert(false);
}

void MakeGameWindow::init_window() {
    room_field = TextField(20, "meow");
    room_field.set_additional_text("Enter room name:");
    room_field.set_position(
        sf::Vector2f((window.getSize().x - 2 * room_field.get_shape().getSize().x) / 2.0 - 20,
                     (window.getSize().y - room_field.get_shape().getSize().y) / 2.0 - 100));
    name_field = TextField(20, "no name");
    name_field.set_additional_text("Enter your name:");
    name_field.set_position(
        sf::Vector2f((window.getSize().x - 2 * name_field.get_shape().getSize().x) / 2.0 +
                         name_field.get_shape().getSize().x + 20,
                     (window.getSize().y - room_field.get_shape().getSize().y) / 2.0 - 100));

    number_of_players_field = TextField(20, "2");
    number_of_players_field.set_additional_text("Enter number of players (2-4):");
    number_of_players_field.set_position(
        sf::Vector2f((window.getSize().x - 3 * name_field.get_shape().getSize().x) / 2.0 - 40,
                     (window.getSize().y - number_of_players_field.get_shape().getSize().y) / 2.0));

    number_of_cards_field = TextField(20, "84");
    number_of_cards_field.set_additional_text("Enter number of cards:");
    number_of_cards_field.set_position(
        sf::Vector2f((window.getSize().x - number_of_cards_field.get_shape().getSize().x) / 2.0,
                     (window.getSize().y - number_of_cards_field.get_shape().getSize().y) / 2.0));

    seconds_for_turn_field = TextField(20, "60");
    seconds_for_turn_field.set_additional_text("Enter time for turn in seconds:");
    seconds_for_turn_field.set_position(
        sf::Vector2f((window.getSize().x - seconds_for_turn_field.get_shape().getSize().x) / 2.0 +
                         seconds_for_turn_field.get_shape().getSize().x + 40,
                     (window.getSize().y - room_field.get_shape().getSize().y) / 2.0));

    start_button = TextButton(sf::Vector2f(200, 40), sf::Text("Make", font));
    start_button.set_color(sf::Color(55, 55, 55));
    start_button.set_position(
        sf::Vector2f((window.getSize().x - start_button.get_shape().getSize().x) / 2.0,
                     (window.getSize().y - start_button.get_shape().getSize().y) / 2.0 + 100));
}

void MakeGameWindow::draw() {
    window.clear();
    room_field.draw(window);
    name_field.draw(window);
    number_of_cards_field.draw(window);
    number_of_players_field.draw(window);
    seconds_for_turn_field.draw(window);
    start_button.draw(window);
    window.display();
}
