#include "animal.h"
#include <stdexcept>
#include "game.h"
#include "phase.h"

Animal::Animal(Player &owner_) : owner(owner_) {
}
Player Animal::get_owner() const {
    return owner;
}
std::unordered_multiset<Animal::Prop> &Animal::get_properties() {
    return animals_properties;
}
void Animal::set_property_is_used(Properties property, bool value) {
    property_is_used[property] = value;
}
bool Animal::can_use_property(Properties property) {
    return (!property_is_used[property]);
}
void Animal::use_property(Properties property, FeedingPhase &phase) {
    if (can_use_property(property)) {
        switch (property) {
            case Properties::DEFAULT:
                break;
            case Properties::FAT_TISSUE:
                increase_owning_food();
                property_is_used[property] = true;
                break;
            case Properties::BIG:
                break;
            case Properties::STOMPER:
                phase.decrease_food_balance();
                property_is_used[property] = true;
                break;
            case Properties::CARNIVOROUS:
                break;
            case Properties::SWIMMINGS:
                break;
            case Properties::RUNNING:
                break;
            case Properties::BURROWING:
                break;
            case Properties::CAMOUFLAGE:
                break;
            case Properties::SHARP_VISION:
                break;
            default:
                throw std::logic_error("CANNOT USE THIS PROPERTY");
        }
    } else {
        throw std::logic_error("CANNOT USE THIS PROPERTY");
    }
}
void Animal::increase_owning_food() {
    if (owning_food == food_needed + animals_properties.count(Properties::FAT_TISSUE)) {
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
void Animal::set_owning_food(int new_food) {
    owning_food = new_food;
}
void Animal::increase_food_needed(std::size_t how_much) {
    food_needed += how_much;
}
bool Animal::could_be_attacked(std::shared_ptr<Animal> attacker) {
    if (animals_properties.find(Properties::BIG) != animals_properties.end() &&
        attacker->animals_properties.find(Properties::BIG) == attacker->animals_properties.end()) {
        return false;
    }
    if (animals_properties.find(Properties::SWIMMINGS) != animals_properties.end() &&
        attacker->animals_properties.find(Properties::SWIMMINGS) ==
            attacker->animals_properties.end()) {
        return false;
    }
    if (animals_properties.find(Properties::BURROWING) != animals_properties.end() &&
        owning_food == food_needed) {
        return false;
    }
    if (animals_properties.find(Properties::CAMOUFLAGE) != animals_properties.end() &&
        attacker->animals_properties.find(Properties::SHARP_VISION) ==
        attacker->animals_properties.end()) {
        return false;
    }
    return true;
}