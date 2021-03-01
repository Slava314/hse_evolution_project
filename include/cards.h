#ifndef EVOLUTION_PROJECT_INCLUDE_CARDS_H_
#define EVOLUTION_PROJECT_INCLUDE_CARDS_H_

#include "properties.h"
struct Card {
public:
    bool is_it_full = false;
    Properties::_enumerated property = Properties::DEFAULT;
    int extra_food = 0;
    // this one only for default case, to create a fake card to deliver cards to players
    explicit Card(Properties::_enumerated prop) : property(prop) {
    }

protected:
    explicit Card(Properties::_enumerated prop, int food) : property(prop), extra_food(food) {
    }
};

struct FatTissue : Card {
public:
    explicit FatTissue(Properties::_enumerated &prop) : Card(prop, 0) {
        [[maybe_unused]] bool is_it_full = false;
    }
};

struct Big : Card {
public:
    explicit Big(Properties::_enumerated &prop) : Card(prop, 1) {
    }
};

struct Stomper : Card {
public:
    explicit Stomper(Properties::_enumerated &prop) : Card(prop, 0) {
    }
};

#endif  // EVOLUTION_PROJECT_INCLUDE_CARDS_H_
