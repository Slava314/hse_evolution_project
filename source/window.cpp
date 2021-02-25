#include "window.h"
#include <cassert>
#include "view.h"
#include "player.h"
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
        draw();
        window.display();
    }
    assert(false);
}

void Start_Window::init_window() {
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
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return nullptr;
            }

            // chat.get_view()->handle_events(window);
            //auto phase = game.get_phase();
            if (game.get_phase()) {
                game.get_phase()->get_view()->handle_events(*this);
            } else {
                break;
            }
        }

        window.clear();
        draw();
        window.display();
    }
    assert(false);
}

void Game_Window::draw() {
    window.draw(deck_shape);
    window.draw(deck_text);
    for (auto card : player_cards_buttons) {
        window.draw(card.get_shape());
    }
    for (auto animal : player_animals_shapes) {
        window.draw(animal.get_shape());
        window.draw(animal.get_text());
    }

    if (selected_card != -1) {
        window.draw(place_for_new_animal.get_shape());
    }

    window.draw(end_turn.get_shape());
    window.draw(end_turn.get_text());
}

void Game_Window::init_window() {
    make_deck_shape();

    place_for_new_animal.set_size({CARD_WIDTH, CARD_HEIGHT});
    place_for_new_animal.set_color(sf::Color::Black);
    place_for_new_animal.set_outline_thickness(5);
    place_for_new_animal.set_outline_color(CARD_OUTLINE_COLOR);

    end_turn.set_size({150, 40});
    end_turn.set_color(sf::Color(55, 55, 55));
    end_turn.set_text("End turn", font);

    end_turn.set_position(
        {(WINDOW_WIDTH - CARD_WIDTH) / 2.0 + 50, (WINDOW_HEIGHT - CARD_HEIGHT) / 2.0 - 75});
}

void Game_Window::make_deck_shape() {
    deck_shape.setSize({CARD_WIDTH, CARD_HEIGHT});
    deck_shape.setFillColor(CARD_COLOR);
    deck_shape.setOutlineThickness(5);
    deck_shape.setOutlineColor(CARD_OUTLINE_COLOR);
    deck_shape.setPosition((WINDOW_WIDTH - CARD_WIDTH) / 2.0 - 100,
                           (WINDOW_HEIGHT - CARD_HEIGHT) / 2.0 - 150);

    deck_text.setString("deck: " + std::to_string(game.get_deck_size()));
    deck_text.setFont(font);
    deck_text.setCharacterSize(28);

    deck_text.setPosition(
        deck_shape.getPosition().x + (CARD_WIDTH - deck_text.getGlobalBounds().width) / 2.0f,
        deck_shape.getPosition().y);
}
void Game_Window::add_cards() {
    for (int i = player_cards_buttons.size(); i < game.get_players()[0].size_cards_owning_in_hands(); ++i) {
        player_cards_buttons.emplace_back(sf::Vector2f(CARD_WIDTH, CARD_HEIGHT));
        player_cards_buttons[i].set_color(CARD_COLOR);
        player_cards_buttons[i].set_outline_thickness(5);
        player_cards_buttons[i].set_outline_color(CARD_OUTLINE_COLOR);
    }
    set_cards_position();
    make_deck_shape();
}
void Game_Window::set_cards_position() {
    unsigned int left_point_cards = (WINDOW_WIDTH - CARD_WIDTH * player_cards_buttons.size() -
        free_space * (player_cards_buttons.size() - 1)) /
        2;
    for (int i = 0; i < player_cards_buttons.size(); ++i) {
        player_cards_buttons[i].set_position(sf::Vector2f(
            left_point_cards + (free_space + CARD_WIDTH) * i, WINDOW_HEIGHT - CARD_HEIGHT - 50));
    }
}
