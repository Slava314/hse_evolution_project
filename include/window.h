#ifndef EVOLUTION_PROJECT__WINDOW_H_
#define EVOLUTION_PROJECT__WINDOW_H_
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "button.h"

class Window {
public:
    virtual std::unique_ptr<Window> handle_events() = 0;
    virtual ~Window() = default;

protected:
    sf::RenderWindow window;
    virtual void draw() = 0;
};

class Start_Window : public Window {
public:
    Start_Window(){
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Start_window",
                      sf::Style::Titlebar | sf::Style::Close);
        font.loadFromFile("resources/t.ttf");
        make_start_button();
    }

    std::unique_ptr<Window> handle_events() override;
    ~Start_Window() override = default;

private:
    Text_Button start_button;
    sf::Font font;

    void make_start_button();
    void draw() override;
};

class Game_Window : public Window{
public:
    std::unique_ptr<Window> handle_events() override;
    ~Game_Window() override = default;

private:
    void draw() override;
};

#endif  // EVOLUTION_PROJECT__WINDOW_H_
