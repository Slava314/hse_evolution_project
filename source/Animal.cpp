#include "Animal.h"
#include "Game.h"

std::vector<Properties> Animal::GetProperties() const {
    return animals_properties;
}

void Animal::UseProperty(Properties properties) {
    switch (properties) {
        case ЖИРОВОЙ_ЗАПАС: ++animals_owning_food;
        case БОЛЬШОЕ: ++animals_food_needed;
        case ТОПОТУН: --Game::get_game().board.feeding_units;
        default: assert(false);
    }
}