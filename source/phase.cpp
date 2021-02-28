#include "phase.h"
#include "view.h"
std::unique_ptr<View> Development_Phase::get_view() {
    return std::make_unique<Development_Phase_View>(*this);
}
void Development_Phase::set_next_phase() {
    game.set_phase(std::make_unique<Feeding_Phase>(game));
}
std::vector<std::vector<std::shared_ptr<Card>>> Development_Phase::cards_delivery() {
    return game.cards_delivery();
}
bool Development_Phase::is_running_first_time() const {
    return start_of_phase;
}
void Development_Phase::set_start_of_phase(bool start) {
    start_of_phase = start;
}
void Development_Phase::add_animal(std::shared_ptr<Card> card, std::shared_ptr<Animal> new_animal) {
    game.add_animal(card, new_animal);
}
std::unique_ptr<View> Feeding_Phase::get_view() {
    return std::make_unique<Feeding_Phase_View>(*this);
}
void Feeding_Phase::set_next_phase() {
    game.set_phase(std::make_unique<Development_Phase>(game));
}
