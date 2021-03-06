#include "animal.h"
#include "game.h"
#include "phase.h"

std::unordered_multiset<Animal::Prop> Animal::get_properties() const {
    return animals_properties;
}

void Animal::UseProperty(Properties properties, FeedingPhase &phase) {
    switch (properties) {
        case Properties::DEFAULT:
            break;
        case Properties::FAT_TISSUE:
            break;
        case Properties::BIG:
            break;
        case Properties::STOMPER:
            phase.decrease_food_balance();
            break;
        default:
            throw std::logic_error("CANNOT USE THIS PROPERTY");
    }
}
void Animal::increase_owning_food() {
    if (owning_food == food_needed + animals_properties.count(Properties::STOMPER)) {
        throw std::logic_error("CANNOT FEED ANIMAL");
    } else {
        ++owning_food;
    }
}

bool Animal::is_hungry() const {
    return owning_food < food_needed;
}
int Animal::get_food_needed() const {
    return food_needed;
}
int Animal::get_owning_food() const {
    return owning_food;
}
void Animal::increase_food_needed(std::size_t how_much) {
    food_needed += how_much;
}