#include "window.h"
#include <cassert>
#include "player.h"
#include "view.h"
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
            // auto phase = game.get_phase();
            if (game.get_phase()) {
                game.get_phase()->get_view()->handle_events(*this, event);
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
    place_for_new_animal.deactivate();

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
void Game_Window::add_cards(std::vector<std::vector<std::shared_ptr<Card>>> new_cards) {
    for (int i = 0; i < new_cards[cur_player].size(); ++i) {
        player_cards_buttons.emplace_back(sf::Vector2f(CARD_WIDTH, CARD_HEIGHT));
        player_cards_buttons.back().set_color(CARD_COLOR);
        player_cards_buttons.back().set_outline_thickness(5);
        player_cards_buttons.back().set_outline_color(CARD_OUTLINE_COLOR);
        player_cards_buttons.back().set_object(new_cards[cur_player][i]);
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
void Game_Window::add_animal_shape(std::shared_ptr<Animal> new_animal) {
    player_animals_shapes.emplace_back(sf::Vector2f(CARD_WIDTH, CARD_HEIGHT), L"свойства: 0", font);
    player_animals_shapes.back().set_color(CARD_COLOR);
    player_animals_shapes.back().set_outline_thickness(5);
    player_animals_shapes.back().set_outline_color(CARD_OUTLINE_COLOR);
    player_animals_shapes.back().set_text_size(22);
    player_animals_shapes.back().is_active = false;
    player_animals_shapes.back().set_object(new_animal);
}
void Game_Window::set_animals_position(bool with_new_place) {
    int extra = with_new_place;
    int left_point_animals = (WINDOW_WIDTH - CARD_WIDTH * (player_animals_shapes.size() + extra) -
                              free_space * (player_animals_shapes.size() - 1 + extra)) /
                             2;
    for (int j = 0; j < player_animals_shapes.size(); ++j) {
        player_animals_shapes[j].set_position(sf::Vector2f(
            left_point_animals + (free_space + CARD_WIDTH) * j, WINDOW_HEIGHT - CARD_HEIGHT - 300));
    }
    if (with_new_place) {
        place_for_new_animal.set_position(sf::Vector2f(
            left_point_animals + (free_space + CARD_WIDTH) * player_animals_shapes.size(),
            WINDOW_HEIGHT - CARD_HEIGHT - 300));
    }
}
void Game_Window::delete_animal_shape() {
}
sf::RenderWindow &Game_Window::get_window() {
    return window;
}
int Game_Window::check_cards() {
    for (int i = 0; i < player_cards_buttons.size(); ++i) {  // choose card
        if (player_cards_buttons[i].is_clicked(sf::Mouse::getPosition(window)) &&
            player_cards_buttons[i].is_active) {
            if (selected_card == -1) {
                selected_card = i;
            } else {
                selected_card = -1;
            }
            return i;
        }
    }
    return -1;
}
void Game_Window::click_card(int i) {
    if (selected_card == i) {
        for (int j = 0; j < player_cards_buttons.size(); ++j) {
            if (i != j) {
                player_cards_buttons[j].deactivate();
            }
        }
        for (auto &player_animal_button : player_animals_shapes) {
            player_animal_button.is_active = true;
        }
        set_animals_position(true);
        place_for_new_animal.activate();
    } else {
        //                    player_cards_buttons[i].deactivate();
        for (auto &player_cards_button : player_cards_buttons) {
            player_cards_button.activate();
        }
        for (auto &player_animal_button : player_animals_shapes) {
            player_animal_button.is_active = false;
        }
        set_animals_position(false);
        place_for_new_animal.deactivate();
    }
}

bool Game_Window::check_new_animal() {
    return place_for_new_animal.is_clicked(sf::Mouse::getPosition(window)) &&
           place_for_new_animal.is_active;
}

std::shared_ptr<Card> Game_Window::play_animal(std::shared_ptr<Animal> animal) {
    // players[0].use_card_as_animal(selected_card);
    auto card = player_cards_buttons[selected_card].get_object();
    player_cards_buttons.erase(std::next(player_cards_buttons.begin(), selected_card));
    selected_card = -1;
    place_for_new_animal.deactivate();
    set_cards_position();
    add_animal_shape(animal);
    set_animals_position(false);
    for (auto &player_cards_button : player_cards_buttons) {
        player_cards_button.activate();
    }
    return card;
}
