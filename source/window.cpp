#include "window.h"
#include <cassert>
#include "player.h"
#include "view.h"
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
                            return std::make_unique<GameWindow>();
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

void StartWindow::init_window() {
    start_button = TextButton(sf::Vector2f(200, 40), sf::Text("Start", font));
    start_button.set_color(sf::Color(55, 55, 55));
    start_button.set_position(
        sf::Vector2f((window.getSize().x - start_button.get_shape().getSize().x) / 2.0,
                     (window.getSize().y - start_button.get_shape().getSize().y) / 2.0));
}
void StartWindow::draw() {
    start_button.draw(window);
}

std::unique_ptr<Window> GameWindow::handle_events() {
    while (window.isOpen()) {
        sf::Event event{};
        if (window.waitEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return nullptr;
            }
            if (game.get_phase()) {
                game.get_phase()->get_view()->handle_event(*this, event);
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

void GameWindow::draw() {
    window.draw(deck_shape);
    window.draw(deck_text);
    for (const auto &card : player_cards_buttons) {
        card.draw(window);
    }
    for (const auto &animal : player_animals_shapes) {
        animal.draw(window);
    }

    if (selected_card != nullptr) {
        place_for_new_animal.draw(window);
    }

    end_turn.draw(window);
}

void GameWindow::init_window() {
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

void GameWindow::make_deck_shape() {
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
void GameWindow::add_cards() {
    auto cards = game.get_players()[cur_player].get_cards();
    for (const auto &card : cards) {
        bool exist = false;
        for (const auto &player_cards_button : player_cards_buttons) {
            if (card == player_cards_button.get_object()) {
                exist = true;
            }
        }
        if (!exist) {
            CardButton new_button(sf::Vector2f(CARD_WIDTH, CARD_HEIGHT));
            new_button.set_color(CARD_COLOR);
            new_button.set_outline_thickness(5);
            new_button.set_outline_color(CARD_OUTLINE_COLOR);
            new_button.set_object(card);
            player_cards_buttons.push_back(new_button);
        }
    }
    set_cards_position();
    make_deck_shape();
}
void GameWindow::set_cards_position() {
    std::size_t left_point_cards = (WINDOW_WIDTH - CARD_WIDTH * player_cards_buttons.size() -
                                    FREE_SPACE * (player_cards_buttons.size() - 1)) /
                                   2;
    for (std::size_t i = 0; i < player_cards_buttons.size(); ++i) {
        player_cards_buttons[i].set_position(sf::Vector2f(
            left_point_cards + (FREE_SPACE + CARD_WIDTH) * i, WINDOW_HEIGHT - CARD_HEIGHT - 50));
    }
}
void GameWindow::add_animal_shape(const std::shared_ptr<Animal> &new_animal) {
    AnimalButton new_animal_shape(sf::Vector2f(CARD_WIDTH, CARD_HEIGHT),
                                  sf::Text(L"свойства: 0", font));

    new_animal_shape.set_color(CARD_COLOR);
    new_animal_shape.set_outline_thickness(5);
    new_animal_shape.set_outline_color(CARD_OUTLINE_COLOR);
    new_animal_shape.set_text_size(22);
    new_animal_shape.set_active(false);
    new_animal_shape.set_object(new_animal);
    player_animals_shapes.push_back(new_animal_shape);
}
void GameWindow::set_animals_position(bool with_new_place) {
    int extra = with_new_place;
    std::size_t left_point_animals =
        (WINDOW_WIDTH - CARD_WIDTH * (player_animals_shapes.size() + extra) -
         FREE_SPACE * (player_animals_shapes.size() - 1 + extra)) /
        2;
    for (std::size_t j = 0; j < player_animals_shapes.size(); ++j) {
        player_animals_shapes[j].set_position(sf::Vector2f(
            left_point_animals + (FREE_SPACE + CARD_WIDTH) * j, WINDOW_HEIGHT - CARD_HEIGHT - 300));
    }
    if (with_new_place) {
        place_for_new_animal.set_position(sf::Vector2f(
            left_point_animals + (FREE_SPACE + CARD_WIDTH) * player_animals_shapes.size(),
            WINDOW_HEIGHT - CARD_HEIGHT - 300));
    }
}
void GameWindow::delete_animal_shape() {
}
sf::RenderWindow &GameWindow::get_window() {
    return window;
}
std::shared_ptr<Card> GameWindow::get_clicked_card() {
    for (auto &player_cards_button : player_cards_buttons) {
        if (player_cards_button.is_clicked(sf::Mouse::getPosition(window)) &&
            player_cards_button.is_active()) {
            if (!selected_card) {
                selected_card = player_cards_button.get_object();
            } else {
                selected_card = nullptr;
            }
            return player_cards_button.get_object();
        }
    }
    return nullptr;
}
void GameWindow::click_card(const std::shared_ptr<Card> &card) {
    if (selected_card == card) {
        for (auto &player_cards_button : player_cards_buttons) {
            if (card != player_cards_button.get_object()) {
                player_cards_button.deactivate();
            }
        }
        for (auto &player_animal_button : player_animals_shapes) {
            player_animal_button.set_active(true);
        }
        set_animals_position(true);
        place_for_new_animal.activate();
    } else {
        for (auto &player_cards_button : player_cards_buttons) {
            player_cards_button.activate();
        }
        for (auto &player_animal_button : player_animals_shapes) {
            player_animal_button.set_active(false);
        }
        set_animals_position(false);
        place_for_new_animal.deactivate();
    }
}

bool GameWindow::check_new_animal() {
    return place_for_new_animal.is_clicked(sf::Mouse::getPosition(window)) &&
           place_for_new_animal.is_active();
}

std::shared_ptr<Card> GameWindow::play_animal(const std::shared_ptr<Animal> &animal) {
    auto card = selected_card;
    for (std::size_t i = 0; i < player_cards_buttons.size(); ++i) {
        if (player_cards_buttons[i].get_object() == selected_card) {
            player_cards_buttons.erase(std::next(player_cards_buttons.begin(), i));
        }
    }
    selected_card = nullptr;
    place_for_new_animal.deactivate();
    set_cards_position();
    add_animal_shape(animal);
    set_animals_position(false);
    for (auto &player_cards_button : player_cards_buttons) {
        player_cards_button.activate();
    }
    return card;
}

bool GameWindow::check_end_turn() {
    return end_turn.is_clicked(sf::Mouse::getPosition(window)) && end_turn.is_active();
}
std::shared_ptr<Animal> GameWindow::check_animals() {
    for (auto &player_animals_shape : player_animals_shapes) {
        if (player_animals_shape.is_clicked(sf::Mouse::getPosition(window)) &&
            player_animals_shape.is_active()) {
            return player_animals_shape.get_object();
        }
    }
    return nullptr;
}
void GameWindow::add_property_to_animal(const std::shared_ptr<Animal> &new_animal) {
    if (selected_card != nullptr) {
        for (std::size_t i = 0; i < player_cards_buttons.size(); ++i) {
            if (player_cards_buttons[i].get_object() == selected_card) {
                player_cards_buttons.erase(std::next(player_cards_buttons.begin(), i));
            }
        }
        selected_card = nullptr;
        set_cards_position();
        for (auto &player_animals_shape : player_animals_shapes) {
            if (player_animals_shape.get_object() == new_animal) {
                player_animals_shape.set_text(L"свойства: " + std::to_wstring(1),
                                              font);  // TODO ask for number of properties
                player_animals_shape.set_text_size(22);
            }
        }
        for (auto &player_animal_button : player_animals_shapes) {
            player_animal_button.set_active(false);
        }
        set_animals_position(false);
        place_for_new_animal.deactivate();

        for (auto &player_cards_button : player_cards_buttons) {
            player_cards_button.activate();
        }
    }
}
std::shared_ptr<Card> const &GameWindow::get_selected_card() const {
    return selected_card;
}
