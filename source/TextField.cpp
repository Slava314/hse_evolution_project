#include "TextField.h"
const std::string TextField::get_text() const {
    return text;
}

void TextField::set_position(sf::Vector2f coordinates) {
    rect.setPosition(coordinates);
}

bool TextField::is_clicked(const sf::Vector2i &mouse_position) const  {
    auto bounds = rect.getGlobalBounds();
    return (mouse_position.x >= bounds.left && mouse_position.x <= bounds.left + bounds.width &&
        mouse_position.y >= bounds.top && mouse_position.y <= bounds.top + bounds.height);
}

void TextField::set_focus(bool focus) {
    has_focus = focus;
    if (focus){
        rect.setOutlineColor(sf::Color::Blue);
    }
    else{
        rect.setOutlineColor(sf::Color(127, 127, 127));
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
    window.draw(rect);
    sf::Text text_to_draw(text, font);
    text_to_draw.setCharacterSize(26);
    text_to_draw.setPosition({rect.getPosition().x, rect.getPosition().y - 3});
    text_to_draw.setFillColor(sf::Color::Black);
    window.draw(text_to_draw);
}
void TextField::change_focus() {
    set_focus(!has_focus);
}
sf::RectangleShape const &TextField::get_shape() const {
    return rect;
}
