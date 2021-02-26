#include "view.h"
#include "cards.h"
#include "phase.h"
#include "window.h"

void Development_Phase_View::start_development_phase(Game_Window &window) const {
    cards_delivery(window);
    phase.set_start_of_phase(false);
}
void Development_Phase_View::cards_delivery(Game_Window &window) const {
    auto t = phase.cards_delivery();
    window.add_cards(t);
}
void Development_Phase_View::add_animal(Game_Window &window) const {
    auto new_animal = std::make_shared<Animal>();
    auto card = window.play_animal(new_animal);
    phase.add_animal(card, new_animal);
}

void Development_Phase_View::add_property(int selected_animal, Game_Window &window) const {
    window.add_property_to_animal(selected_animal);
    // TODO add proprty in logic
}

void Development_Phase_View::handle_events(Game_Window &window, sf::Event event) const {
    if (phase.is_running_first_time()) {
        start_development_phase(window);
    }

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        if (window.check_end_turn()) {
            phase.set_next_phase();
            return;
        }
        int clicked_card = window.check_cards();
        if (clicked_card != -1) {
            window.click_card(clicked_card);
            return;
        }
        if (window.check_new_animal()) {
            add_animal(window);
            return;
        }
        int clicked_animal = window.check_animals();
        if (clicked_animal != -1 and window.get_selected_card() != -1) {
            add_property(clicked_animal, window);
            return;
        }
    }

    //    while (auto event = window.poll_event()) {
    //        if (<что-то что приводит к разадче карт>) {
    //            cards_delivery(window);
    //        }
    //
    //        for (auto card : phase.get_cards_in_hands()) {
    //            if (<клик в card.get_coords()>) {
    //                place_card(card, window);
    //            }
    //        }
    //        if (!phase.is_running()) {
    //            break;
    //        }
    //    }
}
void Feeding_Phase_View::handle_events(Game_Window &window, sf::Event) const {
    window.get_window().close();
}
