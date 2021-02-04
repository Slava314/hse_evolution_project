#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <utility>
#include <string>
#include <iostream>

struct Button {
protected:
    sf::RectangleShape shape;
public:
    Button() = default;

    explicit Button(sf::Vector2f shape_) : shape(shape_) {}

    void set_color(sf::Color const &color);

    virtual void set_position(sf::Vector2f const &position_);

    void set_size(sf::Vector2f const &size);

    void set_outline_color(sf::Color const &color);

    void set_outline_thickness(float thickness);

    sf::Vector2f const &get_position();

    bool is_clicked(sf::Vector2i const &mouse_position);

    sf::RectangleShape const &get_shape();

};

struct Text_Button : Button {
private:
    sf::Text text;
public:
    Text_Button() = default;

    explicit Text_Button(sf::Vector2f shape_, sf::Text text_) : Button(shape_), text(std::move(text_)) {
    }

    explicit Text_Button(sf::Vector2f const &shape_, std::string const &line, sf::Font const &font) : Button(shape_), text(line, font) {
    }

    void set_position(sf::Vector2f const &position_) override;

    void set_text_size(int size);

    sf::Text const &get_text();

};


#endif //EVOLUTION_PROJECT_BUTTON_H
