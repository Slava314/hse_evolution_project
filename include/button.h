#ifndef EVOLUTION_PROJECT_INCLUDE_BUTTON_H
#define EVOLUTION_PROJECT_INCLUDE_BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include "animal.h"
#include "cards.h"

class Button {
public:
    Button() = default;
    explicit Button(const sf::Vector2f &shape_) : shape(shape_) {
    }
    virtual ~Button() = default;

    void set_color(const sf::Color &color);
    virtual void set_position(const sf::Vector2f &position_);
    void set_size(const sf::Vector2f &size);
    void set_outline_color(const sf::Color &color);
    void set_outline_thickness(float thickness);
    virtual void set_scale(const sf::Vector2f &scale);
    virtual void activate();
    virtual void deactivate();
    virtual void draw(sf::RenderWindow &window) const;
    virtual bool is_active() const;
    virtual void set_active(bool value);

    sf::Vector2f const &get_size() const;
    sf::Vector2f const &get_position() const;
    sf::RectangleShape const &get_shape() const;

    bool is_clicked(const sf::Vector2i &mouse_position) const;

protected:
    sf::RectangleShape shape;
    bool is_active_ = true;
};

class TextButton : public Button {
public:
    TextButton() = default;
    explicit TextButton(const sf::Vector2f &shape_) : Button(shape_) {
    }
    explicit TextButton(const sf::Vector2f &shape_, sf::Text text_)
        : Button(shape_), text(std::move(text_)) {
    }
    ~TextButton() override = default;

    void set_position(const sf::Vector2f &position_) override;
    void set_text_size(int size);
    void set_text_color(const sf::Color &color);
    void set_scale(const sf::Vector2f &scale) override;
    void activate() override;
    void deactivate() override;
    void set_text(const std::wstring &line, const sf::Font &font);
    void set_text(const std::string &line, const sf::Font &font);
    void set_font(const sf::Font &font);
    void draw(sf::RenderWindow &window) const override;

    sf::Text const &get_text() const;

protected:
    sf::Text text;
};

class CardButton : public TextButton {
public:
    explicit CardButton(const sf::Vector2f &shape_, const sf::Texture &texture)
        : TextButton(shape_), sprite(texture) {
    }
    explicit CardButton(const sf::Vector2f &shape_, sf::Text text_, const sf::Texture &texture)
        : TextButton(shape_, std::move(text_)), sprite(texture) {
    }

    void draw(sf::RenderWindow &window) const override;
    void set_object(const std::shared_ptr<Card> &obj);
    std::shared_ptr<Card> const &get_object() const;
    void set_sprite_scale(int x, int y);
    void set_position(const sf::Vector2f &position_) override;
    void activate() override;
    void deactivate() override;

private:
    std::shared_ptr<Card> object;
    sf::Sprite sprite;
};

class AnimalButton : public TextButton {
public:
    explicit AnimalButton(const sf::Vector2f &shape_, const sf::Texture &texture)
        : TextButton(shape_), sprite(texture) {
        property_button = std::make_unique<Button>(Button({shape_.x, shape_.y / 5}));
    }
    explicit AnimalButton(const sf::Vector2f &shape_, sf::Text text_, const sf::Texture &texture)
        : TextButton(shape_, std::move(text_)), sprite(texture) {
        property_button = std::make_unique<Button>(Button({shape_.x, shape_.y / 5}));
    }

    void set_object(const std::shared_ptr<Animal> &obj);
    void set_position(const sf::Vector2f &position_) override;
    void draw(sf::RenderWindow &window) const override;
    std::shared_ptr<Animal> const &get_object() const;
    std::shared_ptr<Button> &get_property_button();
    void set_sprite_scale(int x, int y);
    void activate() override;
    void deactivate() override;

private:
    std::shared_ptr<Button> property_button;
    std::shared_ptr<Animal> object;
    sf::Sprite sprite;
};

class PropertyButton : public TextButton {
public:
    PropertyButton(Properties prop_) : TextButton(), prop(prop_) {
    }
    Properties get_property();

private:
    Properties prop;
};

#endif  // EVOLUTION_PROJECT_INCLUDE_BUTTON_H
