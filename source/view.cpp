#include "view.h"
#include <thread>
#include "phase.h"
#include "window.h"

void DevelopmentPhaseView::start_development_phase(GameWindow &window) const {
    cards_delivery(window);
    window.recalc_cards();
    phase.set_start_of_phase(false);
}

void DevelopmentPhaseView::cards_delivery(GameWindow &window) const {
    phase.cards_delivery();
    window.recalc_cards();
}
void DevelopmentPhaseView::add_animal(GameWindow &window) const {
    auto new_animal = std::make_shared<Animal>(phase.get_cur_player());
    phase.add_animal(window.get_selected_card(), new_animal);
    window.play_animal(new_animal);
}

void DevelopmentPhaseView::add_property(const std::shared_ptr<Animal> &selected_animal,
                                        GameWindow &window) const {
    phase.give_property_to_animal(window.get_selected_card(), selected_animal);
    window.add_property_to_animal(selected_animal);
}

int DevelopmentPhaseView::handle_event(GameWindow &window, const sf::Event &event) const {
    if (phase.is_running_first_time()) {
        start_development_phase(window);
    }
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        if (window.check_end_turn()) {
            return 2;
        }
        if (const auto &clicked_property_animal = window.get_clicked_property_animal();
            clicked_property_animal != nullptr) {
            window.show_properties(clicked_property_animal, false);
            return 0;
        }
        if (const auto &clicked_card = window.get_clicked_card(); clicked_card != nullptr) {
            window.click_card(clicked_card);
            return 0;
        }
        if (window.get_selected_card() != nullptr && window.check_new_animal()) {
            add_animal(window);
            return 1;
        }
        if (const auto &clicked_animal = window.check_animals(); clicked_animal != nullptr) {
            add_property(clicked_animal, window);
            return 1;
        }
    }
    return 0;
}

int FeedingPhaseView::handle_event(GameWindow &window, const sf::Event &event) const {
    if (phase.is_running_first_time()) {
        start_feeding_phase(window);
    }
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        if (window.check_end_turn()) {
            return 2;
        }
        if (const auto &clicked_property_animal = window.get_clicked_property_animal();
            clicked_property_animal != nullptr) {
            window.show_properties(clicked_property_animal, true);
            return 0;
        }
        if (window.check_food()) {
            window.click_food();
            return 0;
        }
        if (window.get_food_clicked()) {
            if (const auto &clicked_animal = window.check_animals(); clicked_animal != nullptr) {
                feed_animal(clicked_animal, window);
                return 1;
            }
        }
    }
    return 0;
}
void FeedingPhaseView::start_feeding_phase(GameWindow &window) const {
    window.make_food();
    window.recalc_cards();
    phase.set_start_of_phase(false);
}
void FeedingPhaseView::feed_animal(const std::shared_ptr<Animal> &animal,
                                   GameWindow &window) const {
    phase.feed_animal(animal);
    window.feed_animal(animal);
}
