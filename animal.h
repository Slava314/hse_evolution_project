#include <vector>

#ifndef EVOLUTION_PROJECT_ANIMAL_H
#define EVOLUTION_PROJECT_ANIMAL_H

struct Animal {
    std::vector<Property> animals_properties{};
    int animals_food_needed = 1;
    int animals_owning_food = 0;
    [[nodiscard]] std::vector<Property> GetProperties() const;
    void UseProperty(Property);

    Animal() = default;
};
#endif //EVOLUTION_PROJECT_ANIMAL_H
