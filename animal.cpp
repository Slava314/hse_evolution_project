#include "animal.h"

std::vector<Property> Animal::GetProperties() const {
    return animals_properties;
}

void Animal::UseProperty(Property) {
    switch (Property) {
        case ЖИРОВОЙ_ЗАПАС: ++animals_owning_food;
        case БОЛЬШОЕ: ++animals_food_needed;
        case ТОПОТУН: --feeding_units;
    }
}