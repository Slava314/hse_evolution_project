#include <window.h>
#include <cassert>
#include <memory>
std::unique_ptr<Window> StartWindow::handle_events() {
    while (window.isOpen()) {
        sf::Event event{};
        if (window.waitEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    return nullptr;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (start_button.is_clicked(sf::Mouse::getPosition(window))) {
                            window.close();
                            return std::make_unique<GameWindow>();
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        draw();
    }
    assert(false);
}

void StartWindow::init_window() {
    start_button = TextButton(sf::Vector2f(200, 40), sf::Text("Start", font));
    start_button.set_color(sf::Color(55, 55, 55));
    start_button.set_position(
        sf::Vector2f((window.getSize().x - start_button.get_shape().getSize().x) / 2.0,
                     (window.getSize().y - start_button.get_shape().getSize().y) / 2.0));
}
void StartWindow::draw() {
    window.clear();
    start_button.draw(window);
    window.display();
}