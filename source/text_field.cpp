#include "text_field.h"
const std::string TextField::get_text() const {
    return text;
}

void TextField::set_position(sf::Vector2f coordinates) {
    shape.setPosition(coordinates);
    additional_text.setPosition(coordinates.x, coordinates.y - 30);
}

bool TextField::is_clicked(const sf::Vector2i &mouse_position) const {
    auto bounds = shape.getGlobalBounds();
    return (mouse_position.x >= bounds.left && mouse_position.x <= bounds.left + bounds.width &&
            mouse_position.y >= bounds.top && mouse_position.y <= bounds.top + bounds.height);
}

void TextField::set_focus(bool focus) {
    has_focus = focus;
    if (focus) {
        if (first_click) {
            text = "";
            first_click = false;
        }
        shape.setOutlineColor(sf::Color::Blue);
    } else {
        shape.setOutlineColor(sf::Color(127, 127, 127));
    }
}

void TextField::handle_input(sf::Event event) {
    if (!has_focus || event.type != sf::Event::TextEntered) {
        return;
    }

    if (event.text.unicode == 8) {  // Delete key
        text = text.substr(0, text.size() - 1);
    } else if (text.size() < size) {
        text += event.text.unicode;
    }
}

void TextField::draw(sf::RenderWindow &window) const {
    window.draw(shape);
    window.draw(additional_text);
    sf::Text text_to_draw(text, font);
    text_to_draw.setCharacterSize(26);
    text_to_draw.setPosition({shape.getPosition().x, shape.getPosition().y - 3});
    text_to_draw.setFillColor(sf::Color::Black);
    window.draw(text_to_draw);
}

sf::RectangleShape const &TextField::get_shape() const {
    return shape;
}
void TextField::set_additional_text(const std::string &str) {
    additional_text = sf::Text(str, font, 20);
    additional_text.setFillColor(sf::Color::White);
}
