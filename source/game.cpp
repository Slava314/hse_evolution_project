#include "game.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "constants.h"

void Game::shuffle_players(int quantity) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(players.begin(), players.end(), g);
}

void Game::run_game() {
    //    sf::RectangleShape left({LEFT_WIDTH, WINDOW_HEIGHT / 2});
    //    left.setPosition(0, WINDOW_HEIGHT / 4);
    //    left.setFillColor(sf::Color(55, 55, 55));
    //
    //    sf::Text food_count("food: 0", font);

    prepare_game();

    //    int left_point_animals = (WINDOW_WIDTH - CARD_WIDTH * (player_animals_shapes.size() + 1) -
    //                              free_space * player_animals_shapes.size()) /
    //                             2;

    while (game_window.isOpen()) {
        if (cur_phase == Start_developing) {
            start_developing_phase();
            cur_phase = Developing;
        }
        if (cur_phase == Start_feeding) {
            start_feeding_phase();
            cur_phase = Feeding;
        }
        if (cur_phase == Death) {
            death_phase();
            cur_phase = Start_developing;
        }

        sf::Event event{};
        while (game_window.pollEvent(event)) {
            handle_event(event);
        }
        game_window.clear();
        draw_game_window();
        game_window.display();
    }
}

void Game::prepare_game() {
    // TODO set number of players
    players.resize(1);

    constexpr int N = 3;
    std::vector<std::pair<Properties, int>> cards_info(N);
    // временное решение по генерации, пока нет настроек
    cards_info[0] = {FAT_TISSUE, 8};
    cards_info[1] = {BIG , 8};
    cards_info[2] = {STOMPER, 8};
    deck.generate_deck(cards_info);

    font.loadFromFile("../times.ttf");
    game_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game_window",
                       sf::Style::Titlebar | sf::Style::Close);
    cur_phase = Start_developing;
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

void Game::start_developing_phase() {
    deck.cards_delivery(players);
    add_cards_buttons();
    deck_text.setString("deck: " + std::to_string(deck.get_deck_size()));
}

void Game::start_feeding_phase() {
    // TODO generate food, make food shapes
}

void Game::death_phase() {
    // TODO kill animals, delete animal buttons
}

void Game::draw_game_window() {
    game_window.draw(deck_shape);
    game_window.draw(deck_text);
    for (auto card : player_cards_buttons) {
        game_window.draw(card.get_shape());
    }
    for (auto animal : player_animals_shapes) {
        game_window.draw(animal.get_shape());
        game_window.draw(animal.get_text());
    }

    if (selected_card != -1) {
        game_window.draw(place_for_new_animal.get_shape());
    }

    game_window.draw(end_turn.get_shape());
    game_window.draw(end_turn.get_text());

    //    game_window.draw_game_window(left);
}

void Game::make_deck_shape() {
    deck_shape.setSize({CARD_WIDTH, CARD_HEIGHT});
    deck_shape.setFillColor(CARD_COLOR);
    deck_shape.setOutlineThickness(5);
    deck_shape.setOutlineColor(CARD_OUTLINE_COLOR);
    deck_shape.setPosition((WINDOW_WIDTH - CARD_WIDTH) / 2.0 - 100,
                           (WINDOW_HEIGHT - CARD_HEIGHT) / 2.0 - 150);

    deck_text.setString("deck: " + std::to_string(deck.get_deck_size()));
    deck_text.setFont(font);
    deck_text.setCharacterSize(28);

    deck_text.setPosition(
        deck_shape.getPosition().x + (CARD_WIDTH - deck_text.getGlobalBounds().width) / 2.0f,
        deck_shape.getPosition().y);
}

void Game::handle_event(sf::Event event) {
    if (event.type == sf::Event::Closed) {
        game_window.close();
    }

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        for (int i = 0; i < player_cards_buttons.size(); ++i) {  // choose card
            if (player_cards_buttons[i].is_clicked(sf::Mouse::getPosition(game_window)) &&
                player_cards_buttons[i].is_active) {
                if (selected_card != i) {
                    selected_card = i;
                    for (int j = 0; j < player_cards_buttons.size(); ++j) {
                        if (i != j) {
                            player_cards_buttons[j].deactivate();
                        }
                    }
                    set_animals_position(true);
                    for (auto &player_animal_button : player_animals_shapes) {
                        player_animal_button.is_active = true;
                    }
                    break;
                } else {
                    selected_card = -1;
                    //                    player_cards_buttons[i].deactivate();
                    for (auto &player_cards_button : player_cards_buttons) {
                        player_cards_button.activate();
                    }
                    for (auto &player_animal_button : player_animals_shapes) {
                        player_animal_button.is_active = false;
                    }
                    set_animals_position(false);
                    break;
                }
            }
        }
        if (place_for_new_animal.is_clicked(
                sf::Mouse::getPosition(game_window))) {  // use card as animal
            player_cards_buttons.erase(std::next(player_cards_buttons.begin(), selected_card));
            //players[0].use_card_as_animal(selected_card);
            selected_card = -1;
            set_cards_position();
            add_animal_shape();
            set_animals_position(false);
            for (auto &player_cards_button : player_cards_buttons) {
                player_cards_button.activate();
            }
        }

        for (int i = 0; i < player_animals_shapes.size(); ++i) {  // use card as property
            if (player_animals_shapes[i].is_clicked(sf::Mouse::getPosition(game_window)) &&
                player_animals_shapes[i].is_active) {
                if (selected_card != -1) {
                    players[0].use_card_as_property(selected_card, i);
                    player_cards_buttons.erase(
                        std::next(player_cards_buttons.begin(), selected_card));
                    selected_card = -1;
                    set_cards_position();
                    set_animals_position(false);
                    player_animals_shapes[i].set_text(
                        L"свойства: " + std::to_wstring(1), font);  // TODO ask for number of properties
                    for (auto &player_cards_button : player_cards_buttons) {
                        player_cards_button.activate();
                    }
                    break;
                }
            }
        }

        if (end_turn.is_clicked(sf::Mouse::getPosition(game_window)) and end_turn.is_active) {
            if (cur_phase == Developing) {
                cur_phase = Start_feeding;
            }
            if (cur_phase == Feeding) {
                cur_phase = Death;
            }
            game_window.close();
        }
    }
}
void Game::add_cards_buttons() {
    for (int i = player_cards_buttons.size(); i < players[0].size_cards_owning_in_hands(); ++i) {
        player_cards_buttons.emplace_back(sf::Vector2f(CARD_WIDTH, CARD_HEIGHT));
        player_cards_buttons[i].set_color(CARD_COLOR);
        player_cards_buttons[i].set_outline_thickness(5);
        player_cards_buttons[i].set_outline_color(CARD_OUTLINE_COLOR);
    }
    set_cards_position();
}

void Game::set_cards_position() {
    unsigned int left_point_cards = (WINDOW_WIDTH - CARD_WIDTH * player_cards_buttons.size() -
                                     free_space * (player_cards_buttons.size() - 1)) /
                                    2;
    for (int i = 0; i < player_cards_buttons.size(); ++i) {
        player_cards_buttons[i].set_position(sf::Vector2f(
            left_point_cards + (free_space + CARD_WIDTH) * i, WINDOW_HEIGHT - CARD_HEIGHT - 50));
    }
}

void Game::add_animal_shape() {
    player_animals_shapes.emplace_back(sf::Vector2f(CARD_WIDTH, CARD_HEIGHT), L"свойства: 0", font);
    player_animals_shapes.back().set_color(CARD_COLOR);
    player_animals_shapes.back().set_outline_thickness(5);
    player_animals_shapes.back().set_outline_color(CARD_OUTLINE_COLOR);
    player_animals_shapes.back().set_text_size(22);
    player_animals_shapes.back().is_active = false;
}

void Game::set_animals_position(bool with_new_place) {
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

void Game::delete_animal_shape() {
}
