#include "button.h"
#include <SFML/Graphics.hpp>

void Button::set_shape_color(sf::Color color) {
    shape.setFillColor(color);
}

sf::RectangleShape const &Button::get_shape() {
    return shape;
}

void Button::set_shape_position(sf::Vector2f position_) {
    shape.setPosition(position_);
}

bool Button::is_clicked(sf::Vector2i mouse_position) {
    auto bounds = shape.getGlobalBounds();
    return (mouse_position.x >= bounds.left and mouse_position.x <= bounds.left + bounds.width and mouse_position.y >= bounds.top and mouse_position.y <= bounds.top + bounds.height);
}

