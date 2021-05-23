#include <cassert>
#include "player.h"
#include "properties.h"
#include "view.h"
#include "window.h"

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

int calc_player(int current, int other) {
    if (current == other) {
        return 0;
    } else {
        return other;
    }
}
}  // namespace

std::unique_ptr<Window> GameWindow::handle_events() {
    int count = 0;
    while (window.isOpen()) {
        sf::Event event{};
        if (window.waitEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return nullptr;
            }
            if (game.get_phase()) {
                game.get_phase()->run_phase(*this, event);
            } else {
                break;
            }
        }

        draw();
    }
    assert(false);
}

void GameWindow::draw() {
    window.clear();
    for (auto name : players_names) {
        window.draw(name);
    }
    window.draw(deck_shape);
    window.draw(deck_text);
    for (const auto &card : player_cards_buttons) {
        card.draw(window);
    }
    for (const auto &vec : player_animals_buttons) {
        for (const auto &animal : vec) {
            animal.draw(window);
        }
    }

    if (selected_card != nullptr) {
        place_for_new_animal.draw(window);
    }
    if (dynamic_cast<FeedingPhase *>(game.get_phase().get())) {
        food.draw(window);
    }

    end_turn.draw(window);
    window.display();
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
    player_animals_buttons.resize(game.get_players().size());

    for (int i = 0; i < game.get_players().size(); ++i) {
        sf::Text new_name(game.get_players()[i].get_name(), font);
        new_name.setCharacterSize(28);
        players_names.push_back(new_name);
    }
    std::cout << "PLAYERS COUNT = " << game.get_players().size() << std::endl;
    set_players_names_positions();
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

void GameWindow::recalc_cards() {
    player_cards_buttons.clear();
    auto cards = game.get_players()[game.get_cur_player_index()].get_cards_in_hands();
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
            Properties prop = card->get_info().first;
            new_button.set_text(get_name(prop), font);
            new_button.set_text_size(20);
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
void GameWindow::add_animal_shape(const std::shared_ptr<Animal> &new_animal, int id) {
    AnimalButton new_animal_shape(
        sf::Vector2f(CARD_WIDTH, CARD_HEIGHT),

        sf::Text("properties: " +
                     std::to_string(game.get_players()[id].count_animal_properties(new_animal)),
                 font));

    new_animal_shape.set_color(CARD_COLOR);
    new_animal_shape.set_outline_thickness(5);
    new_animal_shape.set_outline_color(CARD_OUTLINE_COLOR);
    new_animal_shape.set_text_size(22);
    new_animal_shape.set_active(false);
    new_animal_shape.set_object(new_animal);
    new_animal_shape.property_button->set_color({0, 0, 0, 0});
    player_animals_buttons[id].push_back(new_animal_shape);
}

void GameWindow::set_animals_position(bool with_new_place) {
    int extra = with_new_place;
    std::size_t player = game.get_cur_player_index();
    // local player
    std::size_t left_point_animals =
        (WINDOW_WIDTH - CARD_WIDTH * (player_animals_buttons[player].size() + extra) -
         FREE_SPACE * (player_animals_buttons[player].size() - 1 + extra)) /
        2;
    for (std::size_t j = 0; j < player_animals_buttons[player].size(); ++j) {
        player_animals_buttons[player][j].set_position(sf::Vector2f(
            left_point_animals + (FREE_SPACE + CARD_WIDTH) * j, WINDOW_HEIGHT - CARD_HEIGHT - 300));
    }
    if (with_new_place) {
        place_for_new_animal.set_position(sf::Vector2f(
            left_point_animals + (FREE_SPACE + CARD_WIDTH) * player_animals_buttons[player].size(),
            WINDOW_HEIGHT - CARD_HEIGHT - 300));
    }

    // up player 1
    player = calc_player(game.get_cur_player_index(), 1);
    left_point_animals = (WINDOW_WIDTH - CARD_WIDTH * (player_animals_buttons[player].size()) -
                          FREE_SPACE * (player_animals_buttons[player].size() - 1)) /
                         2;
    for (std::size_t j = 0; j < player_animals_buttons[player].size(); ++j) {
        player_animals_buttons[player][j].set_position(
            sf::Vector2f(left_point_animals + (FREE_SPACE + CARD_WIDTH) * j, 50));
    }

    if (game.get_players().size() >= 3) {
        // right player 2
        player = calc_player(game.get_cur_player_index(), 2);
        int number_of_animals = player_animals_buttons[player].size();

        left_point_animals = 1350 + (450 - CARD_WIDTH * (std::min(3, number_of_animals)) -
                                     FREE_SPACE * (std::min(3, number_of_animals) - 1)) /
                                        2;
        for (int j = 0; j < std::min(3, number_of_animals); ++j) {
            player_animals_buttons[player][j].set_position(
                sf::Vector2f(left_point_animals + (FREE_SPACE + CARD_WIDTH) * j, 250));
        }

        left_point_animals = 1350 + (450 - CARD_WIDTH * (number_of_animals - 3) -
                                     FREE_SPACE * (number_of_animals - 3 - 1)) /
                                        2;
        for (int j = 0; j < number_of_animals - 3; ++j) {
            player_animals_buttons[player][j + 3].set_position(
                sf::Vector2f(left_point_animals + (FREE_SPACE + CARD_WIDTH) * j, 450));
        }
    }

    if (game.get_players().size() >= 4) {
        // left player 3
        player = calc_player(game.get_cur_player_index(), 3);
        int number_of_animals = player_animals_buttons[player].size();

        left_point_animals = (450 - CARD_WIDTH * (std::min(3, number_of_animals)) -
                              FREE_SPACE * (std::min(3, number_of_animals) - 1)) /
                             2;
        for (int j = 0; j < std::min(3, number_of_animals); ++j) {
            player_animals_buttons[player][j].set_position(
                sf::Vector2f(left_point_animals + (FREE_SPACE + CARD_WIDTH) * j, 250));
        }

        left_point_animals = (450 - CARD_WIDTH * (number_of_animals - 3) -
                              FREE_SPACE * (number_of_animals - 3 - 1)) /
                             2;
        for (int j = 0; j < number_of_animals - 3; ++j) {
            player_animals_buttons[player][j + 3].set_position(
                sf::Vector2f(left_point_animals + (FREE_SPACE + CARD_WIDTH) * j, 450));
        }
    }

    set_players_names_positions();
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
        for (auto &player_animal_button : player_animals_buttons[game.get_cur_player_index()]) {
            player_animal_button.set_active(true);
        }
        set_animals_position(true);
        place_for_new_animal.activate();
        end_turn.deactivate();
    } else {
        for (auto &player_cards_button : player_cards_buttons) {
            player_cards_button.activate();
        }
        for (auto &player_animal_button : player_animals_buttons[game.get_cur_player_index()]) {
            player_animal_button.set_active(false);
        }
        set_animals_position(false);
        place_for_new_animal.deactivate();
        end_turn.activate();
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
    add_animal_shape(animal, game.get_cur_player_index());
    set_animals_position(false);
    for (auto &player_cards_button : player_cards_buttons) {
        player_cards_button.activate();
    }
    end_turn.activate();
    return card;
}

bool GameWindow::check_end_turn() {
    return end_turn.is_clicked(sf::Mouse::getPosition(window));
}
std::shared_ptr<Animal> GameWindow::check_animals() {
    for (const auto &player_animals_shape : player_animals_buttons[game.get_cur_player_index()]) {
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
        if (int index =
                find_in_animal_buttons(animal, player_animals_buttons[game.get_cur_player_index()]);
            index >= 0) {
            player_animals_buttons[game.get_cur_player_index()][index].set_text(
                "properties: " + std::to_string(game.get_players()[game.get_cur_player_index()]
                                                    .count_animal_properties(animal)),

                font);
            player_animals_buttons[game.get_cur_player_index()][index].set_text_size(22);
        }
        for (auto &player_animal_button : player_animals_buttons[game.get_cur_player_index()]) {
            player_animal_button.set_active(false);
        }
        set_animals_position(false);
        place_for_new_animal.deactivate();

        for (auto &player_cards_button : player_cards_buttons) {
            player_cards_button.activate();
        }
        end_turn.activate();
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
    for (int k = 0; k < game.get_players().size(); ++k) {
        for (std::size_t i = 0; i < player_animals_buttons[k].size(); i++) {
            std::string str =
                "properties: " + std::to_string(game.get_players()[k].count_animal_properties(
                                     player_animals_buttons[k][i].get_object()));
            str += "\n   food: ";
            str += std::to_string(player_animals_buttons[k][i].get_object()->get_owning_food()) +
                   "/" +
                   std::to_string(player_animals_buttons[k][i].get_object()->get_food_needed());
            player_animals_buttons[k][i].set_text(str, font);
            player_animals_buttons[k][i].set_text_size(22);
            player_animals_buttons[k][i].set_active(true);
        }
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
        for (auto &animal : player_animals_buttons[game.get_cur_player_index()]) {
            if (!(animal.get_object()->is_hungry())) {
                animal.deactivate();
            }
        }
    } else {
        food_clicked = false;
        for (auto &animal : player_animals_buttons[game.get_cur_player_index()]) {
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
    if (int index =
            find_in_animal_buttons(animal, player_animals_buttons[game.get_cur_player_index()]);
        index >= 0) {
        make_food();
        food_clicked = false;
        for (auto &ani : player_animals_buttons[game.get_cur_player_index()]) {
            ani.activate();
        }
    }
}

void GameWindow::recalc_animals() {
    for (std::size_t i = 0; i < game.get_players().size(); i++) {
        auto animals = game.get_players()[i].get_animals_on_board();
        player_animals_buttons[i].clear();
        for (auto &animal : animals) {
            add_animal_shape(animal, i);
        }
    }

    set_animals_position(false);
}

void GameWindow::change_player() {
    recalc_cards();
    set_animals_position(false);
}
std::shared_ptr<AnimalButton> GameWindow::get_clicked_property_animal() {
    for (auto player_animals : player_animals_buttons) {
        for (auto animal : player_animals) {
            if (animal.property_button->is_clicked(sf::Mouse::getPosition(window))) {
                return std::make_shared<AnimalButton>(animal);
            }
        }
    }
    return nullptr;
}
void GameWindow::show_properties(std::shared_ptr<AnimalButton> animal_button, bool phase) {
    if (animal_button->get_object()->get_properties().size() > 0) {
        window.setActive(false);
        PropertyWindow property_window(phase);
        property_window.init_window(animal_button);
        Properties use_prop = property_window.handle_properties();
        window.setActive(true);
        if (use_prop != Properties::DEFAULT) {
            use_property(animal_button, use_prop);
        }
    }
}
void GameWindow::use_property(std::shared_ptr<AnimalButton>, Properties prop) {
}

void GameWindow::set_players_names_positions() {
    std::size_t player = game.get_cur_player_index();
    // local player
    players_names[player].setPosition(
        (WINDOW_WIDTH - players_names[player].getGlobalBounds().width) / 2, WINDOW_HEIGHT - 280);

    // up player 1
    player = calc_player(game.get_cur_player_index(), 1);
    players_names[player].setPosition(
        (WINDOW_WIDTH - players_names[player].getGlobalBounds().width) / 2, 0);

    if (game.get_players().size() >= 3) {
        // right player 2
        player = calc_player(game.get_cur_player_index(), 2);
        players_names[player].setPosition(
            1350 + (450 - players_names[player].getGlobalBounds().width) / 2, 200);
    }

    if (game.get_players().size() >= 4) {
        // left player 3
        player = calc_player(game.get_cur_player_index(), 3);
        players_names[player].setPosition((450 - players_names[player].getGlobalBounds().width) / 2,
                                          200);
    }
}

void PropertyWindow::draw() {
    window.clear();
    for (auto button : properties) {
        button.draw(window);
    }
    window.display();
}

void PropertyWindow::init_window(std::shared_ptr<AnimalButton> animal_button) {
    auto property_list = animal_button->get_object()->get_properties();
    int count = 0;
    for (Properties prop : property_list) {
        count++;
        PropertyButton new_prop(prop);
        new_prop.set_position(sf::Vector2f(0, (count - 1) * 50));
        new_prop.set_size({200, 50});
        new_prop.set_color(sf::Color::Black);
        new_prop.set_text(std::to_string(count) + ") " + get_name(prop), font);
        new_prop.set_text_size(18);
        //        if (able_to_use) {
        //            if(){ //check ability to use from game and current player
        //            new_prop.set_text_color(sf::Color::Green);
        //            }
        //        }
        new_prop.set_active(false);
        properties.push_back(new_prop);
    }
}

Properties PropertyWindow::handle_properties() {
    while (window.isOpen()) {
        sf::Event event{};
        if (window.waitEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (able_to_use) {
                if (event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Left) {
                    for (auto &button : properties) {
                        if (button.is_clicked(sf::Mouse::getPosition(window))) {
                            window.close();
                            return button.get_property();
                        }
                    }
                }
            }
        }
        draw();
    }
    return Properties::DEFAULT;
}
std::unique_ptr<Window> PropertyWindow::handle_events() {
    return std::unique_ptr<Window>();
}
