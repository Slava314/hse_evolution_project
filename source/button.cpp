#include "button.h"
#include <SFML/Graphics.hpp>

void Button::set_color(sf::Color const &color) {
    shape.setFillColor(color);
}

sf::RectangleShape const &Button::get_shape() {
    return shape;
}

void Button::set_position(sf::Vector2f const &position) {
    shape.setPosition(position);
}

bool Button::is_clicked(sf::Vector2i const &mouse_position) {
    auto bounds = shape.getGlobalBounds();
    return (mouse_position.x >= bounds.left and mouse_position.x <= bounds.left + bounds.width and
            mouse_position.y >= bounds.top and mouse_position.y <= bounds.top + bounds.height);
}

void Button::set_size(sf::Vector2f const &size) {
    shape.setSize(size);

}

void Button::set_outline_color(const sf::Color &color) {
    shape.setOutlineColor(color);
}

void Button::set_outline_thickness(float thickness) {
    shape.setOutlineThickness(thickness);
}

sf::Vector2f const &Button::get_position() {
    return shape.getPosition();
}


sf::Text const &Text_Button::get_text() {
    return text;
}

void Text_Button::set_position(const sf::Vector2f &position_) {
    Button::set_position(position_);
    text.setPosition(shape.getPosition().x + (shape.getSize().x - text.getGlobalBounds().width) / 2.0,
                     shape.getPosition().y);
}

void Text_Button::set_text_size(int size) {
    text.setCharacterSize(size);
    text.setPosition(shape.getPosition().x + (shape.getSize().x - text.getGlobalBounds().width) / 2.0,
                     shape.getPosition().y);
}
