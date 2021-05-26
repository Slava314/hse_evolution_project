#include <window.h>
#include <cassert>
#include <memory>
#include <string>
#include "text_field.h"

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
                        if (start_local_game_button.is_clicked(sf::Mouse::getPosition(window))) {
                            window.close();
                            return std::make_unique<StartLocalGameWindow>();
                        }
                        if (start_online_game_button.is_clicked(sf::Mouse::getPosition(window))) {
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
    start_local_game_button = TextButton(sf::Vector2f(250, 40), sf::Text("Start local game", font));
    start_local_game_button.set_color(sf::Color(55, 55, 55));
    start_local_game_button.set_position(
        sf::Vector2f((window.getSize().x - 2 * start_local_game_button.get_size().x) / 2.0 - 20,
                     (window.getSize().y - start_local_game_button.get_size().y) / 2.0));

    start_online_game_button =
        TextButton(sf::Vector2f(250, 40), sf::Text("Start online game", font));
    start_online_game_button.set_color(sf::Color(55, 55, 55));
    start_online_game_button.set_position(
        sf::Vector2f((window.getSize().x - 2 * start_online_game_button.get_size().x) / 2.0 + 20 +
                         start_online_game_button.get_size().x,
                     (window.getSize().y - start_online_game_button.get_size().y) / 2.0));
}
void StartWindow::draw() {
    window.clear();
    start_local_game_button.draw(window);
    start_online_game_button.draw(window);
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
        sf::Vector2f((window.getSize().x - 2 * make_game_button.get_size().x) / 2.0 - 20,
                     (window.getSize().y - make_game_button.get_size().y) / 2.0));
    join_game_button = TextButton(sf::Vector2f(200, 40), sf::Text("Join game", font));
    join_game_button.set_color(sf::Color(55, 55, 55));
    join_game_button.set_position(
        sf::Vector2f((window.getSize().x - 2 * join_game_button.get_size().x) / 2.0 + 20 +
                         make_game_button.get_size().x,
                     (window.getSize().y - join_game_button.get_size().y) / 2.0));
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
    room_field = TextField(20, font, "meow");
    room_field.set_additional_text("Enter room name:");
    room_field.set_position(
        sf::Vector2f((window.getSize().x - 2 * room_field.get_size().x) / 2.0 - FREE_SPACE,
                     (window.getSize().y - room_field.get_size().y) / 2.0));
    name_field = TextField(20, font, "no name");
    name_field.set_additional_text("Enter your name:");
    name_field.set_position(sf::Vector2f((window.getSize().x - 2 * name_field.get_size().x) / 2.0 +
                                             name_field.get_size().x + FREE_SPACE,
                                         (window.getSize().y - room_field.get_size().y) / 2.0));
    join_button = TextButton(sf::Vector2f(200, 40), sf::Text("Join", font));
    join_button.set_color(sf::Color(55, 55, 55));
    join_button.set_position(
        sf::Vector2f((window.getSize().x - join_button.get_size().x) / 2.0,
                     (window.getSize().y - join_button.get_size().y) / 2.0 + 100));
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
                                Settings settings(room_field.get_text(),
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
    room_field = TextField(20, font, "meow");
    room_field.set_additional_text("Enter room name:");
    room_field.set_position(
        sf::Vector2f((window.getSize().x - 2 * room_field.get_size().x) / 2.0 - FREE_SPACE,
                     (window.getSize().y - room_field.get_size().y) / 2.0 - 100));
    name_field = TextField(20, font, "no name");
    name_field.set_additional_text("Enter your name:");
    name_field.set_position(
        sf::Vector2f((window.getSize().x - 2 * name_field.get_size().x) / 2.0 +
                         name_field.get_size().x + FREE_SPACE,
                     (window.getSize().y - room_field.get_size().y) / 2.0 - 100));

    number_of_players_field = TextField(20, font, "2");
    number_of_players_field.set_additional_text("Enter number of players (2-4):");
    number_of_players_field.set_position(
        sf::Vector2f((window.getSize().x - 3 * name_field.get_size().x) / 2.0 - 2 * FREE_SPACE,
                     (window.getSize().y - number_of_players_field.get_size().y) / 2.0));

    number_of_cards_field = TextField(20, font, "84");
    number_of_cards_field.set_additional_text("Enter number of cards:");
    number_of_cards_field.set_position(
        sf::Vector2f((window.getSize().x - number_of_cards_field.get_size().x) / 2.0,
                     (window.getSize().y - number_of_cards_field.get_size().y) / 2.0));

    seconds_for_turn_field = TextField(20, font, "60");
    seconds_for_turn_field.set_additional_text("Enter time for turn in seconds:");
    seconds_for_turn_field.set_position(
        sf::Vector2f((window.getSize().x - seconds_for_turn_field.get_size().x) / 2.0 +
                         seconds_for_turn_field.get_size().x + 2 * FREE_SPACE,
                     (window.getSize().y - room_field.get_size().y) / 2.0));

    start_button = TextButton(sf::Vector2f(200, 40), sf::Text("Make", font));
    start_button.set_color(sf::Color(55, 55, 55));
    start_button.set_position(
        sf::Vector2f((window.getSize().x - start_button.get_size().x) / 2.0,
                     (window.getSize().y - start_button.get_size().y) / 2.0 + 100));
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

std::unique_ptr<Window> StartLocalGameWindow::handle_events() {
    while (window.isOpen()) {
        sf::Event event{};
        if (window.waitEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    return nullptr;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (number_of_players == 0) {
                            check_text_field(number_of_players_field, window);
                            check_text_field(number_of_cards_field, window);
                            check_text_field(seconds_for_turn_field, window);
                            if (start_button.is_clicked(sf::Mouse::getPosition(window))) {
                                if (number_of_players_field.get_text() != "" &&
                                    number_of_cards_field.get_text() != "" &&
                                    seconds_for_turn_field.get_text() != "") {
                                    settings = Settings(
                                        "local", std::stoi(number_of_players_field.get_text()),
                                        std::stoi(number_of_cards_field.get_text()),
                                        std::stoi(seconds_for_turn_field.get_text()));
                                    number_of_players =
                                        std::stoi(number_of_players_field.get_text());
                                    players_names.resize(number_of_players);
                                    init_window();
                                }
                            }
                        } else {
                            if (start_button.is_clicked(sf::Mouse::getPosition(window))) {
                                int cnt = 0;
                                for (int i = 0; i < number_of_players; ++i) {
                                    if (players_names[i].get_text() != "") {
                                        cnt++;
                                    }
                                }
                                if (cnt == number_of_players) {
                                    for (int i = 0; i < number_of_players; ++i) {
                                        settings.set_player_name(players_names[i].get_text(), i);
                                    }
                                    window.close();
                                    return std::make_unique<GameWindow>(settings);
                                }
                            }
                        }
                    }
                    break;
                case sf::Event::TextEntered:
                    if (number_of_players == 0) {
                        number_of_cards_field.handle_input(event);
                        number_of_players_field.handle_input(event);
                        seconds_for_turn_field.handle_input(event);
                    } else {
                        for (int i = 0; i < number_of_players; ++i) {
                            players_names[i].handle_input(event);
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

void StartLocalGameWindow::init_window() {
    if (number_of_players == 0) {
        number_of_players_field = TextField(20, font, "2");
        number_of_players_field.set_additional_text("Enter number of players (2-4):");
        number_of_players_field.set_position(sf::Vector2f(
            (window.getSize().x - 3 * number_of_players_field.get_size().x) / 2.0 - 2 * FREE_SPACE,
            (window.getSize().y - number_of_players_field.get_size().y) / 2.0));

        number_of_cards_field = TextField(20, font, "84");
        number_of_cards_field.set_additional_text("Enter number of cards:");
        number_of_cards_field.set_position(
            sf::Vector2f((window.getSize().x - number_of_cards_field.get_size().x) / 2.0,
                         (window.getSize().y - number_of_cards_field.get_size().y) / 2.0));

        seconds_for_turn_field = TextField(20, font, "60");
        seconds_for_turn_field.set_additional_text("Enter time for turn in seconds:");
        seconds_for_turn_field.set_position(
            sf::Vector2f((window.getSize().x - seconds_for_turn_field.get_size().x) / 2.0 +
                             seconds_for_turn_field.get_size().x + 2 * FREE_SPACE,
                         (window.getSize().y - seconds_for_turn_field.get_size().y) / 2.0));

    } else {
        players_names[0] = TextField(20, font, "Rick");
        players_names[0].set_additional_text("Enter first player name:");

        players_names[1] = TextField(20, font, "Rick");
        players_names[1].set_additional_text("Enter second player name:");

        if (number_of_players >= 3) {
            players_names[2] = TextField(20, font, "Rick");
            players_names[2].set_additional_text("Enter third player name:");
        }

        if (number_of_players == 4) {
            players_names[3] = TextField(20, font, "Rick");
            players_names[3].set_additional_text("Enter fourth player name:");
        }

        std::size_t left_point =
            (WINDOW_WIDTH - players_names[0].get_size().x * (players_names.size()) -
             2 * FREE_SPACE * (players_names.size() - 1)) /
            2;
        for (std::size_t j = 0; j < players_names.size(); ++j) {
            players_names[j].set_position(
                sf::Vector2f(left_point + (2 * FREE_SPACE + players_names[0].get_size().x) * j,
                             (WINDOW_HEIGHT - seconds_for_turn_field.get_size().y) / 2.0));
        }
    }

    start_button = TextButton(sf::Vector2f(200, 40), sf::Text("Start", font));
    start_button.set_color(sf::Color(55, 55, 55));
    start_button.set_position(
        sf::Vector2f((window.getSize().x - start_button.get_size().x) / 2.0,
                     (window.getSize().y - start_button.get_size().y) / 2.0 + 100));
}
void StartLocalGameWindow::draw() {
    window.clear();
    if (number_of_players == 0) {
        number_of_cards_field.draw(window);
        number_of_players_field.draw(window);
        seconds_for_turn_field.draw(window);
    }
    start_button.draw(window);
    for (int i = 0; i < number_of_players; ++i) {
        players_names[i].draw(window);
    }
    window.display();
}
