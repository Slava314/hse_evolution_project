#ifndef EVOLUTION_PROJECT_INCLUDE_BUTTON_H
#define EVOLUTION_PROJECT_INCLUDE_BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <utility>

class Button {
public:
    bool is_active = true;

    Button() = default;
    explicit Button(sf::Vector2f shape) : shape(shape) {
    }
    virtual ~Button() {
    }

    void set_color(sf::Color const &color);
    virtual void set_position(sf::Vector2f const &position_);
    void set_size(sf::Vector2f const &size);
    void set_outline_color(sf::Color const &color);
    void set_outline_thickness(float thickness);
    virtual void set_scale(sf::Vector2f scale);
    virtual void activate();
    virtual void deactivate();
    virtual void draw(sf::RenderWindow &window);

    sf::Vector2f get_size();
    sf::Vector2f const &get_position();
    sf::RectangleShape const &get_shape();

    bool is_clicked(sf::Vector2i const &mouse_position);

protected:
    sf::RectangleShape shape;
};

class Text_Button : public Button {
public:
    Text_Button() = default;
    explicit Text_Button(sf::Vector2f shape_, sf::Text text_)
        : Button(shape_), text(std::move(text_)) {
    }
    explicit Text_Button(sf::Vector2f const &shape_, std::wstring const &line, sf::Font const &font)
        : Button(shape_), text(line, font) {
    }
    explicit Text_Button(sf::Vector2f const &shape_, std::string const &line, sf::Font const &font)
        : Button(shape_), text(line, font) {
    }
    ~Text_Button() override = default;

    void set_position(sf::Vector2f const &position_) override;
    void set_text_size(int size);
    void set_text_color(sf::Color color);
    void set_scale(sf::Vector2f scale) override;
    void activate() override;
    void deactivate() override;
    void set_text(const std::wstring &line, sf::Font const &font);
    void set_text(const std::string &line, sf::Font const &font);
    void set_font(sf::Font const &font);
    void draw(sf::RenderWindow &window) override;

    sf::Text const &get_text();

private:
    sf::Text text;
};

#endif  // EVOLUTION_PROJECT_INCLUDE_BUTTON_H
