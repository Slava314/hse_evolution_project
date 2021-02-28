#include "phase.h"
#include "view.h"
std::unique_ptr<View> DevelopmentPhase::get_view() {
    return std::make_unique<DevelopmentPhaseView>(*this);
}
void DevelopmentPhase::set_next_phase() {
    game.set_phase(std::move(std::make_unique<FeedingPhase>(game)));
}
std::vector<std::vector<std::shared_ptr<Card>>> DevelopmentPhase::cards_delivery() {
    return game.cards_delivery();
}
bool DevelopmentPhase::is_running_first_time() const {
    return start_of_phase;
}
void DevelopmentPhase::set_start_of_phase(bool start) {
    start_of_phase = start;
}
void DevelopmentPhase::add_animal(std::shared_ptr<Card> card, std::shared_ptr<Animal> new_animal) {
    game.add_animal(card, new_animal);
}
std::unique_ptr<View> FeedingPhase::get_view() {
    return std::make_unique<FeedingPhaseView>(*this);
}
void FeedingPhase::set_next_phase() {
    game.set_phase(std::make_unique<DevelopmentPhase>(game));
}
