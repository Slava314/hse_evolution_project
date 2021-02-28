#include "phase.h"
#include "view.h"
#include "player.h"
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
Feeding_Phase::Feeding_Phase(Game &game_) : game(game_), food_balance(define_food_balance()) {
}
size_t Feeding_Phase::define_food_balance() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(MIN_FOOD_BALANCE, MAX_FOOD_BALANCE);
    return distrib(gen);
}
void Feeding_Phase::feed_animal(std::shared_ptr<Animal> animal) {
    assert(animal != nullptr);
    decrease_food_balance();
    animal->increase_owning_food();
}
void Feeding_Phase::decrease_food_balance() {
    if (food_balance == 0) {
        throw std::logic_error("CANNOT DECREASE FOOD BALANCE");
    } else {
        --food_balance;
    }
}
bool Feeding_Phase::is_end_of_phase() const {
    return food_balance == 0;
}
void Feeding_Phase::kill_animals() {
    for (auto &player : game.get_players()) {
        for (auto &animal : player.get_animals_on_board()) {
            if (animal->is_hungry()) {
                player.handle_animal_death(animal);
            }
        }
    }
}
