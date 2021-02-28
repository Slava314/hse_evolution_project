#include "view.h"
#include "cards.h"
#include "phase.h"
#include "window.h"

void DevelopmentPhaseView::start_development_phase(GameWindow &window) const {
    cards_delivery(window);
    phase.set_start_of_phase(false);
}
void DevelopmentPhaseView::cards_delivery(GameWindow &window) const {
    window.add_cards(phase.cards_delivery());
}
void DevelopmentPhaseView::add_animal(GameWindow &window) const {
    auto new_animal = std::make_shared<Animal>();
    auto card = window.play_animal(new_animal);
    phase.add_animal(card, new_animal);
}

void DevelopmentPhaseView::add_property(int selected_animal, GameWindow &window) const {
    window.add_property_to_animal(selected_animal);
    // TODO add property in logic
}

void DevelopmentPhaseView::handle_event(GameWindow &window, const sf::Event &event) const {
    if (phase.is_running_first_time()) {
        start_development_phase(window);
    }
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        if (window.check_end_turn()) {
            phase.set_next_phase();
            return;
        }
        if (auto clicked_card = window.check_cards(); clicked_card != -1) {
            window.click_card(clicked_card);
            return;
        }
        if (window.check_new_animal()) {
            add_animal(window);
            return;
        }
        if (auto clicked_animal = window.check_animals(); clicked_animal != -1) {
            add_property(clicked_animal, window);
            return;
        }
    }
}
void FeedingPhaseView::handle_event(GameWindow &window, const sf::Event &event) const {
    window.get_window().close();
}
