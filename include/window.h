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

class Start_Window : public Window {
public:
    Start_Window() {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Start_window",
                      sf::Style::Titlebar | sf::Style::Close);
        font.loadFromFile("resources/t.ttf");
        init_window();
    }

    std::unique_ptr<Window> handle_events() override;
    ~Start_Window() override = default;

private:
    Text_Button start_button;

    void init_window();
    void draw() override;
};

class Game_Window : public Window {
public:
    Game_Window() {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game_window",
                      sf::Style::Titlebar | sf::Style::Close);
        font.loadFromFile("resources/t.ttf");

        game.start_game(); //важен порядок этих двух строчек, потом возможно надо будет исправить
        init_window();
    }

    std::unique_ptr<Window> handle_events() override;
    void init_window();
    void make_deck_shape();
    ~Game_Window() override = default;

private:
    void draw() override;
    Game game;
    sf::Font font;

    sf::RectangleShape deck_shape;
    sf::Text deck_text;
    std::vector<Button> player_cards_buttons;
    std::vector<Text_Button> player_animals_shapes;
    int selected_card = -1;
    Button place_for_new_animal;
    Text_Button end_turn;
};

#endif  // EVOLUTION_PROJECT__WINDOW_H_
