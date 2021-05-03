#ifndef EVOLUTION_PROJECT_TEXTFIELD_H_
#define EVOLUTION_PROJECT_TEXTFIELD_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

class TextField : public sf::Transformable{
public:
    TextField() = default;
    TextField(std::size_t maxChars)
        : size(maxChars), rect(sf::Vector2f(14 * size, 26)), has_focus(false) {
        font.loadFromFile("resources/t.ttf");
        rect.setOutlineThickness(2);
        rect.setFillColor(sf::Color::White);
        rect.setOutlineColor(sf::Color(127, 127, 127));
        rect.setPosition(this->getPosition());
    }
    const std::string get_text() const;
    void set_position(sf::Vector2f coordinates);
    bool is_clicked(const sf::Vector2i &mouse_position) const;
    void set_focus(bool focus);
    void change_focus();
    void handle_input(sf::Event event);
    void draw(sf::RenderWindow &window) const;
    sf::RectangleShape const &get_shape() const;

private:
    std::size_t size;
    sf::Font font;
    std::string text;
    sf::RectangleShape rect;
    bool has_focus;
};

#endif  // EVOLUTION_PROJECT_TEXTFIELD_H_
