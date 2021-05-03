#include "button.h"
#include <SFML/Graphics.hpp>
#include <utility>

void Button::set_color(const sf::Color &color) {
    shape.setFillColor(color);
}

sf::RectangleShape const &Button::get_shape() const {
    return shape;
}

void Button::set_position(const sf::Vector2f &position) {
    shape.setPosition(position);
}

bool Button::is_clicked(const sf::Vector2i &mouse_position) const {
    auto bounds = shape.getGlobalBounds();
    return (mouse_position.x >= bounds.left && mouse_position.x <= bounds.left + bounds.width &&
            mouse_position.y >= bounds.top && mouse_position.y <= bounds.top + bounds.height) && is_active_;
}

void Button::set_size(const sf::Vector2f &size) {
    shape.setSize(size);
}

void Button::set_outline_color(const sf::Color &color) {
    shape.setOutlineColor(color);
}

void Button::set_outline_thickness(float thickness) {
    shape.setOutlineThickness(thickness);
}

sf::Vector2f const &Button::get_position() const {
    return shape.getPosition();
}

sf::Vector2f const &Button::get_size() const {
    return shape.getSize();
}

void Button::set_scale(const sf::Vector2f &scale) {
    shape.setScale(scale);
}

void Button::activate() {
    is_active_ = true;
    sf::Color color = shape.getFillColor();
    color.a = 255;
    shape.setFillColor(color);
    color = shape.getOutlineColor();
    color.a = 255;
    shape.setOutlineColor(color);
}

void Button::deactivate() {
    is_active_ = false;
    sf::Color color = shape.getFillColor();
    color.a = 150;
    shape.setFillColor(color);
    color = shape.getOutlineColor();
    color.a = 150;
    shape.setOutlineColor(color);
}
void Button::draw(sf::RenderWindow &window) const {
    window.draw(shape);
}
bool Button::is_active() const {
    return is_active_;
}
void Button::set_active(bool value) {
    is_active_ = value;
}

sf::Text const &TextButton::get_text() const {
    return text;
}

void TextButton::set_position(const sf::Vector2f &position_) {
    Button::set_position(position_);
    text.setPosition(
        shape.getPosition().x + (shape.getSize().x - text.getGlobalBounds().width) / 2.0f,
        shape.getPosition().y);
}

void TextButton::set_text_size(int size) {
    text.setCharacterSize(size);
    text.setPosition(
        shape.getPosition().x + (shape.getSize().x - text.getGlobalBounds().width) / 2.0f,
        shape.getPosition().y);
}

void TextButton::set_scale(const sf::Vector2f &scale) {
    Button::set_scale(scale);
    text.setScale(scale);
}

void TextButton::activate() {
    Button::activate();
    sf::Color color = text.getFillColor();
    color.a = 255;
    text.setFillColor(color);
    color = text.getOutlineColor();
    color.a = 255;
    text.setOutlineColor(color);
}

void TextButton::deactivate() {
    Button::deactivate();
    sf::Color color = text.getFillColor();
    color.a = 150;
    text.setFillColor(color);
    color = text.getOutlineColor();
    color.a = 150;
    text.setOutlineColor(color);
}

void TextButton::set_text_color(const sf::Color &color) {
    text.setFillColor(color);
}

void TextButton::set_text(const std::wstring &line, const sf::Font &font) {
    text = sf::Text(line, font);
}

void TextButton::set_text(const std::string &line, const sf::Font &font) {
    text = sf::Text(line, font);
}

void TextButton::set_font(const sf::Font &font) {
    text.setFont(font);
}
void TextButton::draw(sf::RenderWindow &window) const {
    window.draw(shape);
    window.draw(text);
}

void AnimalButton::set_object(const std::shared_ptr<Animal> &obj) {
    object = obj;
}
std::shared_ptr<Animal> const &AnimalButton::get_object() const {
    return object;
}
void AnimalButton::set_position(const sf::Vector2f &position_) {
    TextButton::set_position(position_);
    property_button->set_position(position_);
}
void AnimalButton::draw(sf::RenderWindow &window) const {
    TextButton::draw(window);
    property_button->draw(window);
}

void CardButton::set_object(const std::shared_ptr<Card> &obj) {
    object = obj;
}
std::shared_ptr<Card> const &CardButton::get_object() const {
    return object;
}
Properties PropertyButton::get_property() {
    return prop;
}
