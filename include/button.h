#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

struct Button {
private:
    sf::RectangleShape shape;

public:
    Button() = default;

    explicit Button(sf::Vector2f shape_) : shape(shape_) {

    }

    void set_shape_color(sf::Color color);

    void set_shape_position(sf::Vector2f position_);

    bool is_clicked(sf::Vector2i mouse_position);






    sf::RectangleShape const &get_shape();

};

#endif //EVOLUTION_PROJECT_BUTTON_H
