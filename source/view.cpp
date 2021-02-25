#include "view.h"
#include "window.h"
#include "cards.h"
#include "phase.h"

void Development_Phase_View::start_development_phase(Game_Window &window) const {
    cards_delivery(window);
    phase.set_start_of_phase(false);
}
void Development_Phase_View::cards_delivery(Game_Window &window) const{
    phase.cards_delivery();
    window.add_cards();
}
void Development_Phase_View::place_card(Card &card, Game_Window &window) {
//    phase.place_card_on_board(card);
    //window.draw_card(card.get_coords());
}
void Development_Phase_View::handle_events(Game_Window &window) const{
    if (phase.is_running_first_time()) {
        start_development_phase(window);
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
void Feeding_Phase_View::handle_events(Game_Window &window) const {

}
