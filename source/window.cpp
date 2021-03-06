#include "window.h"
#include <cassert>
#include "player.h"
#include "view.h"

namespace {
int find_in_animal_buttons(const std::shared_ptr<Animal> &animal,
                           const std::vector<AnimalButton> &player_animals_buttons) {
    for (std::size_t i = 0; i < player_animals_buttons.size(); i++) {
        if (player_animals_buttons[i].get_object() == animal) {
            return i;
        }
    }
    return -1;
}

int find_in_card_buttons(const std::shared_ptr<Card> &card,
                         const std::vector<CardButton> &player_cards_shapes) {
    for (std::size_t i = 0; i < player_cards_shapes.size(); i++) {
        if (player_cards_shapes[i].get_object() == card) {
            return i;
        }
    }
    return -1;
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
    for (const auto &animal : player_animals_buttons) {
        animal.draw(window);
    }

    if (selected_card != nullptr) {
        place_for_new_animal.draw(window);
    }
    if (dynamic_cast<FeedingPhase *>(game.get_phase().get())) {
        food.draw(window);
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

    end_turn.set_position({(WINDOW_WIDTH - CARD_WIDTH) / 2.0 + 50, deck_shape.getPosition().y});
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
    auto cards = game.get_players()[cur_player].get_cards_in_hands();
    for (const auto &card : cards) {
        bool exist = false;
        for (auto &player_cards_button : player_cards_buttons) {
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
    AnimalButton new_animal_shape(
        sf::Vector2f(CARD_WIDTH, CARD_HEIGHT),
        sf::Text(
            "properties: " +
                std::to_string(game.get_players()[cur_player].count_animal_properties(new_animal)),
            font));

    new_animal_shape.set_color(CARD_COLOR);
    new_animal_shape.set_outline_thickness(5);
    new_animal_shape.set_outline_color(CARD_OUTLINE_COLOR);
    new_animal_shape.set_text_size(22);
    new_animal_shape.set_active(false);
    new_animal_shape.set_object(new_animal);
    player_animals_buttons.push_back(new_animal_shape);
}
void GameWindow::set_animals_position(bool with_new_place) {
    int extra = with_new_place;
    std::size_t left_point_animals =
        (WINDOW_WIDTH - CARD_WIDTH * (player_animals_buttons.size() + extra) -
         FREE_SPACE * (player_animals_buttons.size() - 1 + extra)) /
        2;
    for (std::size_t j = 0; j < player_animals_buttons.size(); ++j) {
        player_animals_buttons[j].set_position(sf::Vector2f(
            left_point_animals + (FREE_SPACE + CARD_WIDTH) * j, WINDOW_HEIGHT - CARD_HEIGHT - 300));
    }
    if (with_new_place) {
        place_for_new_animal.set_position(sf::Vector2f(
            left_point_animals + (FREE_SPACE + CARD_WIDTH) * player_animals_buttons.size(),
            WINDOW_HEIGHT - CARD_HEIGHT - 300));
    }
}
sf::RenderWindow &GameWindow::get_window() {
    return window;
}
std::shared_ptr<Card> GameWindow::get_clicked_card() {
    for (auto &player_cards_button : player_cards_buttons) {
        if (player_cards_button.is_clicked(sf::Mouse::getPosition(window))) {
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
        for (auto &player_animal_button : player_animals_buttons) {
            player_animal_button.set_active(true);
        }
        set_animals_position(true);
        place_for_new_animal.activate();
    } else {
        for (auto &player_cards_button : player_cards_buttons) {
            player_cards_button.activate();
        }
        for (auto &player_animal_button : player_animals_buttons) {
            player_animal_button.set_active(false);
        }
        set_animals_position(false);
        place_for_new_animal.deactivate();
    }
}

bool GameWindow::check_new_animal() {
    return place_for_new_animal.is_clicked(sf::Mouse::getPosition(window));
}

std::shared_ptr<Card> GameWindow::play_animal(const std::shared_ptr<Animal> &animal) {
    auto card = selected_card;
    if (int index = find_in_card_buttons(selected_card, player_cards_buttons); index >= 0) {
        player_cards_buttons.erase(std::next(player_cards_buttons.begin(), index));
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
    return end_turn.is_clicked(sf::Mouse::getPosition(window));
}
std::shared_ptr<Animal> GameWindow::check_animals() {
    for (const auto &player_animals_shape : player_animals_buttons) {
        if (player_animals_shape.is_clicked(sf::Mouse::getPosition(window))) {
            return player_animals_shape.get_object();
        }
    }
    return nullptr;
}
void GameWindow::add_property_to_animal(const std::shared_ptr<Animal> &animal) {
    if (selected_card != nullptr) {
        if (int index = find_in_card_buttons(selected_card, player_cards_buttons); index >= 0) {
            player_cards_buttons.erase(std::next(player_cards_buttons.begin(), index));
        }
        selected_card = nullptr;
        set_cards_position();
        if (int index = find_in_animal_buttons(animal, player_animals_buttons); index >= 0) {
            player_animals_buttons[index].set_text(
                "properties: " +
                    std::to_string(game.get_players()[cur_player].count_animal_properties(animal)),
                font);
            player_animals_buttons[index].set_text_size(22);
        }
        for (auto &player_animal_button : player_animals_buttons) {
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

void GameWindow::make_food() {
    food.set_size({40, 40});
    food.set_color(sf::Color::Yellow);
    food.set_text(
        std::to_string(dynamic_cast<FeedingPhase *>(game.get_phase().get())->get_food_balance()),
        font);
    food.set_text_color(sf::Color::Black);
    food.set_position({end_turn.get_position().x + (end_turn.get_size().x - food.get_size().x) / 2,
                       deck_shape.getPosition().y + deck_shape.getSize().y / 2});
    for (std::size_t i = 0; i < player_animals_buttons.size(); i++) {
        std::string str =
            "properties: " + std::to_string(game.get_players()[cur_player].count_animal_properties(
                                 player_animals_buttons[i].get_object()));
        str += "\n   food: ";
        str += std::to_string(player_animals_buttons[i].get_object()->get_owning_food()) + "/" +
               std::to_string(player_animals_buttons[i].get_object()->get_food_needed());
        player_animals_buttons[i].set_text(str, font);
        player_animals_buttons[i].set_text_size(22);
        player_animals_buttons[i].set_active(true);
    }

    set_animals_position(false);
}

bool GameWindow::check_food() {
    return food.is_clicked(sf::Mouse::getPosition(window)) &&
           dynamic_cast<FeedingPhase *>(game.get_phase().get())->get_food_balance() > 0;
}

void GameWindow::click_food() {
    if (!food_clicked) {
        food_clicked = true;
        for (auto &animal : player_animals_buttons) {
            if (!(animal.get_object()->is_hungry())) {
                animal.deactivate();
            }
        }
    } else {
        food_clicked = false;
        for (auto &animal : player_animals_buttons) {
            animal.activate();
        }
    }
}
bool const &GameWindow::get_food_clicked() const {
    return food_clicked;
}

void GameWindow::feed_animal(const std::shared_ptr<Animal> &animal) {
    std::size_t cur_food = dynamic_cast<FeedingPhase *>(game.get_phase().get())->get_food_balance();
    if (cur_food == 0) {
        food.deactivate();
    }
    if (int index = find_in_animal_buttons(animal, player_animals_buttons); index >= 0) {
        make_food();
        food_clicked = false;
        for (auto &ani : player_animals_buttons) {
            ani.activate();
        }
    }
}

void GameWindow::kill_animals() {
    auto animals = game.get_players()[cur_player].get_animals_on_board();
    player_animals_buttons.clear();
    for (auto &animal : animals) {
        add_animal_shape(animal);
    }
    set_animals_position(false);
}