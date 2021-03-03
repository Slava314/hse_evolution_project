#ifndef EVOLUTION_PROJECT_ANIMAL_H
#define EVOLUTION_PROJECT_ANIMAL_H

#include <vector>
#include <unordered_set>
#include "properties.h"
class Feeding_Phase;
class Animal {
public:
    [[nodiscard]] std::unordered_multiset<Properties> GetProperties() const;
    void UseProperty(Properties properties, Feeding_Phase &);
    void increase_owning_food();
    bool is_hungry() const;

    Animal() = default;

private:
    int food_needed = 1;
    int owning_food = 0;
    std::unordered_multiset<Properties> animals_properties{};
};
#endif  // EVOLUTION_PROJECT_ANIMAL_H