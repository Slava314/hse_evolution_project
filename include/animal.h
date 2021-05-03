#ifndef EVOLUTION_PROJECT_ANIMAL_H
#define EVOLUTION_PROJECT_ANIMAL_H

#include <unordered_set>
#include <vector>
#include "phase_fwd.h"
#include "properties.h"

class Animal {
public:
    using Prop = Properties;
    [[nodiscard]] std::unordered_multiset<Prop> get_properties() const;
    static void UseProperty(Properties properties, FeedingPhase &);
    void increase_owning_food();
    void increase_food_needed(std::size_t how_much);
    bool is_hungry() const;
    int get_food_needed() const;
    int get_owning_food() const;

    Animal() = default;

    void set_owning_food(int new_food);
private:
    int food_needed = 1;
    int owning_food = 0;
    std::unordered_multiset<Prop> animals_properties{};
};
#endif  // EVOLUTION_PROJECT_ANIMAL_H
