#ifndef EVOLUTION_PROJECT_ANIMAL_H
#define EVOLUTION_PROJECT_ANIMAL_H

#include <vector>
#include <unordered_set>
#include "properties.h"
#include "phase_fwd.h"

class Animal {
public:
    using Prop = Properties;
    [[nodiscard]] std::unordered_multiset<Prop> get_properties() const;
    static void UseProperty(Properties properties, FeedingPhase &);
    void increase_owning_food();
    void increase_food_needed(std::size_t how_much);
    [[nodiscard]] bool is_hungry() const;
    Animal() = default;

private:
    int food_needed = 1;
    int owning_food = 0;
    std::unordered_multiset<Prop> animals_properties{};
};
#endif  // EVOLUTION_PROJECT_ANIMAL_H