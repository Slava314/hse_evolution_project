#ifndef EVOLUTION_PROJECT_INCLUDE_CARDS_H_
#define EVOLUTION_PROJECT_INCLUDE_CARDS_H_

#include "properties.h"
using Property = Properties::_enumerated;
struct Card {
public:
    Property property = Properties::DEFAULT;
    int extra_food = 0;
    // this one only for default case, to create a fake card to deliver cards to players
    explicit Card(Property prop) : property(prop) {
    }

    std::pair<Property, int> get_info();

protected:
    explicit Card(Property prop, int food) : property(prop), extra_food(food) {
    }
};

struct FatTissue : Card {
public:
    explicit FatTissue(Property &prop) : Card(prop, 0) {
        [[maybe_unused]] bool is_it_full = false;
    }
};

struct Big : Card {
public:
    explicit Big(Property &prop) : Card(prop, 1) {
    }
};

struct Stomper : Card {
public:
    explicit Stomper(Property &prop) : Card(prop, 0) {
    }
};

#endif  // EVOLUTION_PROJECT_INCLUDE_CARDS_H_
