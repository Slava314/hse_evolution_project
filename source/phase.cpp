#include "phase.h"
#include "view.h"
std::unique_ptr<View> Development_Phase::get_view() {
    return std::make_unique<Development_Phase_View>(*this);
}
void Development_Phase::set_next_phase() {
    game.set_phase(std::make_unique<Feeding_Phase>(game));
}
void Development_Phase::cards_delivery() {
    game.cards_delivery();
}
bool Development_Phase::is_running_first_time() const{
    return start_of_phase;
}
void Development_Phase::set_start_of_phase(bool start) {
    start_of_phase = start;
}
std::unique_ptr<View> Feeding_Phase::get_view() {
    return std::make_unique<Feeding_Phase_View>(*this);
}
void Feeding_Phase::set_next_phase() {
       game.set_phase(std::make_unique<Development_Phase>(game));
}
