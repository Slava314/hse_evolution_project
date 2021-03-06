#ifndef EVOLUTION_PROJECT_ANIMAL_H
#define EVOLUTION_PROJECT_ANIMAL_H

#include <vector>
#include <unordered_set>
#include "properties.h"
#include "phase_fwd.h"

class Animal {
public:
    using Prop = Properties::_enumerated;
    [[nodiscard]] std::unordered_multiset<Prop> get_properties() const;
    static void UseProperty(Properties properties, FeedingPhase &);
    void increase_owning_food();
    bool is_hungry() const;
    int get_food_needed() const;
    int get_owning_food() const;

    Animal() = default;

private:
    int food_needed = 1;
    int owning_food = 0;
    std::unordered_multiset<Prop> animals_properties{};
};
#endif  // EVOLUTION_PROJECT_ANIMAL_H
