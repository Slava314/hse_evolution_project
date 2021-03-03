#include "phase.h"
#include "player.h"
#include "view.h"

std::unique_ptr<View> DevelopmentPhase::get_view() {
    return std::make_unique<Development_Phase_View>(*this);
}

void DevelopmentPhase::set_next_phase() {
    game.set_phase(std::make_unique<FeedingPhase>(game));
}

void DevelopmentPhase::cards_delivery() {
    game.cards_delivery();
}

bool DevelopmentPhase::is_running_first_time() const {
    return start_of_phase;
}
void DevelopmentPhase::set_start_of_phase(bool start) {
    start_of_phase = start;
}
void DevelopmentPhase::add_animal(std::shared_ptr<Card> &card,
                                  std::shared_ptr<Animal> &new_animal) {
    game.add_animal(card, new_animal);
}

void DevelopmentPhase::give_property_to_animal(const std::shared_ptr<Card> &card,
                                                   const std::shared_ptr<Animal> &new_animal) {
    game.add_property(card, new_animal);
}

std::vector<std::vector<std::shared_ptr<Card>>> DevelopmentPhase::get_cards() {
    return game.get_players_cards_in_hands();
}