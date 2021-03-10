#ifndef EVOLUTION_PROJECT__WINDOW_H_
#define EVOLUTION_PROJECT__WINDOW_H_
#include <SFML/Graphics.hpp>
#include "button.h"
#include "constants.h"
#include "game.h"

class Window {
public:
    virtual std::unique_ptr<Window> handle_events() = 0;
    virtual ~Window() = default;

protected:
    sf::Font font;
    sf::RenderWindow window;
    virtual void draw() = 0;
};

class StartWindow : public Window {
public:
    StartWindow() {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Start_window",
                      sf::Style::Titlebar | sf::Style::Close);
        font.loadFromFile("resources/t.ttf");
        init_window();
    }

    std::unique_ptr<Window> handle_events() override;
    ~StartWindow() override = default;

private:
    TextButton start_button;

    void init_window();
    void draw() override;
};

class GameWindow : public Window {
public:
    GameWindow() {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game_window",
                      sf::Style::Titlebar | sf::Style::Close);
        font.loadFromFile("resources/t.ttf");

        game.start_game();  //важен порядок этих двух строчек, потом возможно надо будет исправить
        init_window();
    }

    std::unique_ptr<Window> handle_events() override;
    void add_cards();
    void set_cards_position();
    void init_window();
    void make_deck_shape();
    void add_animal_shape(const std::shared_ptr<Animal> &new_animal, int id);
    void set_animals_position(bool with_new_place);
    void kill_animals();
    sf::RenderWindow &get_window();
    std::shared_ptr<Card> get_clicked_card();
    void click_card(const std::shared_ptr<Card> &card);
    bool check_new_animal();
    std::shared_ptr<Card> play_animal(const std::shared_ptr<Animal> &shared_ptr);
    bool check_end_turn();
    std::shared_ptr<Animal> check_animals();
    void add_property_to_animal(const std::shared_ptr<Animal> &new_animal);
    std::shared_ptr<Card> const &get_selected_card() const;
    bool const &get_food_clicked() const;

    void make_food();

    ~GameWindow() override = default;

    bool check_food();

    void click_food();

    void feed_animal(const std::shared_ptr<Animal> &animal);

    void change_player();

private:
    void draw() override;
    Game game;
    sf::Font font;

    sf::RectangleShape deck_shape;
    sf::Text deck_text;
    std::vector<CardButton> player_cards_buttons;
    std::vector<std::vector<AnimalButton>> player_animals_buttons;
    std::shared_ptr<Card> selected_card = nullptr;
    Button place_for_new_animal;
    TextButton end_turn;
    TextButton food;
    bool food_clicked = false;
};

#endif  // EVOLUTION_PROJECT__WINDOW_H_
