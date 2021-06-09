#ifndef EVOLUTION_PROJECT_ANIMAL_H
#define EVOLUTION_PROJECT_ANIMAL_H

#include <unordered_set>
#include <map>
#include <vector>
#include "phase_fwd.h"
#include "properties.h"

class Player;
class Animal {
public:
    using Prop = Properties::_enumerated;
    [[nodiscard]] std::unordered_multiset<Prop> &get_properties();
    void set_property_is_used(Properties property, bool value);
    void use_property(Properties properties, FeedingPhase &phase);
    bool can_use_property(Properties property);
    void increase_owning_food();
    void increase_food_needed(std::size_t how_much);
    bool is_hungry() const;
    int get_food_needed() const;
    int get_owning_food() const;
    bool could_be_attacked(std::shared_ptr<Animal> attacker);
    Player get_owner() const;

    Animal(Player &owner_);

    void set_owning_food(int new_food);

private:
    int food_needed = 1;
    int owning_food = 0;
    Player &owner;
    std::unordered_multiset<Prop> animals_properties{};
    std::map<Properties, bool> property_is_used{{Properties::FAT_TISSUE, false},
                                                          {Properties::STOMPER, false},
                                                          {Properties::CARNIVOROUS, false}};
};
#endif  // EVOLUTION_PROJECT_ANIMAL_H
