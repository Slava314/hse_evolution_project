#include "view.h"
#include "window.h"
#include "cards.h"
#include "phase.h"

void Development_Phase_View::init_game(Game_Window &window) const {
    cards_delivery(window);
}
void Development_Phase_View::cards_delivery(Game_Window &window) const{
    phase.cards_delivery();
    //window.draw_cards_in_hand();
}
void Development_Phase_View::place_card(Card &card, Game_Window &window) {
//    phase.place_card_on_board(card);
    //window.draw_card(card.get_coords());
}
void Development_Phase_View::handle_events(Game_Window &window) const{
    if (phase.is_running_first_time()) {
        init_game(window);
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
