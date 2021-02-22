#ifndef EVOLUTION_PROJECT_INCLUDE_CARDS_H_
#define EVOLUTION_PROJECT_INCLUDE_CARDS_H_

#include "properties.h"

#include <iostream>
struct Card {
    Properties property = DEFAULT;
    int extra_food = 0;
    Card(Properties prop) : property(prop){}
protected:
    explicit Card(Properties i, int food) : property(i), extra_food(food) {
    }
};


struct FatTissue : Card {
    explicit FatTissue(Properties &prop) : Card(prop, 0) {
        [[maybe_unused]] bool is_it_full = 0;
    }
};

struct Big : Card {
    explicit Big(Properties &prop) : Card(prop, 1) {
    }
};

struct Stomper : Card {
    explicit Stomper(Properties &prop) : Card(prop, 0) {
    }
};

#endif  // EVOLUTION_PROJECT_INCLUDE_CARDS_H_
