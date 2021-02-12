#ifndef EVOLUTION_PROJECT_ANIMAL_H
#define EVOLUTION_PROJECT_ANIMAL_H

#include <vector>
#include "Properties.h"

struct Animal {
    std::vector<Properties> animals_properties{};
    int animals_food_needed = 1;
    int animals_owning_food = 0;
    [[nodiscard]] std::vector<Properties> GetProperties() const;
    void UseProperty(Properties properties);

    Animal() = default;
};
#endif //EVOLUTION_PROJECT_ANIMAL_H
