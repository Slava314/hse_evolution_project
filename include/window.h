#ifndef EVOLUTION_PROJECT_WINDOW_H_
#define EVOLUTION_PROJECT_WINDOW_H_
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
    std::shared_ptr<AnimalButton> get_clicked_property_animal();
    void show_properties(std::shared_ptr<AnimalButton> animal_button, bool phase);

    void make_food();

    ~GameWindow() override = default;

    bool check_food();

    void click_food();

    void feed_animal(const std::shared_ptr<Animal> &animal);

    void change_player();

    void use_property(std::shared_ptr<AnimalButton>, Properties prop);

private:
    void draw() override;
    Game game;
    sf::Font font;

    TextButton end_turn;
    sf::RectangleShape deck_shape;
    sf::Text deck_text;
    std::vector<CardButton> player_cards_buttons;
    std::vector<std::vector<AnimalButton>> player_animals_buttons;
    std::shared_ptr<Card> selected_card = nullptr;
    Button place_for_new_animal;
    // TextButton end_turn;
    TextButton food;
    bool food_clicked = false;
};

class PropertyWindow : Window {
public:
    PropertyWindow(bool able_to_use_) : able_to_use(able_to_use_) {
        window.create(sf::VideoMode(200, 300), "property_window",
                      sf::Style::Titlebar | sf::Style::Close);
        window.setPosition({200, 200});
        font.loadFromFile("resources/t.ttf");
    }

    std::unique_ptr<Window> handle_events() override;
    Properties handle_properties();
    void init_window(std::shared_ptr<AnimalButton> animal_button);

    ~PropertyWindow() override = default;

private:
    bool able_to_use;
    std::vector<PropertyButton> properties;
    void draw() override;
};

class StartChoiceWindow : public Window {
public:
    StartChoiceWindow() {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Choice_window",
                      sf::Style::Titlebar | sf::Style::Close);
        font.loadFromFile("resources/t.ttf");
        init_window();
    }

    std::unique_ptr<Window> handle_events() override;
    ~StartChoiceWindow() override = default;

private:
    TextButton default_button;
    TextButton join_game_button;
    TextButton make_game_button;

    void init_window();
    void draw() override;
};

class JoinGameWindow : public Window {
public:
    JoinGameWindow() {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Join_window",
                      sf::Style::Titlebar | sf::Style::Close);
        font.loadFromFile("resources/t.ttf");
        init_window();
    }

    std::unique_ptr<Window> handle_events() override;
    ~JoinGameWindow() override = default;

private:

    void init_window();
    void draw() override;
};

class MakeGameWindow : public Window {
public:
    MakeGameWindow() {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Make_window",
                      sf::Style::Titlebar | sf::Style::Close);
        font.loadFromFile("resources/t.ttf");
        init_window();
    }

    std::unique_ptr<Window> handle_events() override;
    ~MakeGameWindow() override = default;

private:

    void init_window();
    void draw() override;
};

#endif  // EVOLUTION_PROJECT_WINDOW_H_
