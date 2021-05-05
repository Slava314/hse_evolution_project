#ifndef EVOLUTION_PROJECT_TEXTFIELD_H_
#define EVOLUTION_PROJECT_TEXTFIELD_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

class TextField : public sf::Transformable {
public:
    TextField() = default;
    TextField(std::size_t maxChars, const sf::Font &font_, std::string str = "")
        : size(maxChars),
          font(font_),
          text(std::move(str)),
          shape(sf::Vector2f(14 * size, 26)),
          has_focus(false) {
        shape.setOutlineThickness(2);
        shape.setFillColor(sf::Color::White);
        shape.setOutlineColor(sf::Color(127, 127, 127));
    }
    const std::string get_text() const;
    void set_position(sf::Vector2f coordinates);
    bool is_clicked(const sf::Vector2i &mouse_position) const;
    void set_focus(bool focus);
    void handle_input(sf::Event event);
    void draw(sf::RenderWindow &window) const;
    sf::RectangleShape const &get_shape() const;
    void set_additional_text(const std::string &str);

private:
    std::size_t size;
    sf::Font font;
    std::string text;
    sf::RectangleShape shape;
    bool first_click = true;
    bool has_focus;
    sf::Text additional_text;
};

#endif  // EVOLUTION_PROJECT_TEXTFIELD_H_
