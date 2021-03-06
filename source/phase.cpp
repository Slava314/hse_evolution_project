#include "phase.h"
#include "view.h"
std::unique_ptr<View> DevelopmentPhase::get_view() {
    return std::make_unique<DevelopmentPhaseView>(*this);
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
void DevelopmentPhase::add_animal(const std::shared_ptr<Card> &card,
                                  const std::shared_ptr<Animal> &new_animal) {
    game.add_animal(card, new_animal);
}
std::shared_ptr<Card> const &DevelopmentPhase::get_selected_card() const {
    return selected_card;
}
void DevelopmentPhase::add_property_to_animal(const std::shared_ptr<Card> &card,
                                              const std::shared_ptr<Animal> &animal) {
    game.add_property_to_animal(card, animal);
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

size_t Feeding_Phase::get_food_balance() const {
    return food_balance;
}
