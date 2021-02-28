#include "animal.h"
#include "game.h"
#include "phase.h"

std::unordered_multiset<Properties> Animal::GetProperties() const {
    return animals_properties;
}

void Animal::UseProperty(Properties properties, Feeding_Phase &phase) {
    switch (properties) {
        case STOMPER:
            phase.decrease_food_balance();
        default:
            throw std::logic_error("CANNOT USE THIS PROPERTY");
    }
}
void Animal::increase_owning_food() {
    if (owning_food == food_needed + animals_properties.count(FAT_TISSUE)) {
        throw std::logic_error("CANNOT FEED ANIMAL");
    } else {
        ++owning_food;
    }
}

bool Animal::is_hungry() const {
    return owning_food < food_needed;
}
