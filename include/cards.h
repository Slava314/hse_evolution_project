#ifndef EVOLUTION_PROJECT_INCLUDE_CARDS_H_
#define EVOLUTION_PROJECT_INCLUDE_CARDS_H_

#include "properties.h"
class Card {
public:
    //this is weird
    Properties pr;
    Properties::_enumerated property = Properties::DEFAULT;
    int extra_food = 0;
    // this one only for default case, to create a fake card to deliver cards to players
    explicit Card(Properties prop) : property(prop._value), pr(prop) {
    }

    std::pair<Properties::_enumerated, int> get_info();
//    Card() = default;
    ~Card() = default;

protected:
    explicit Card(Properties prop, int food) : property(prop._value), extra_food(food), pr(prop) {
    }
};

struct FatTissue : Card {
public:
    explicit FatTissue(const Properties &prop) : Card(prop, 0) {
    }
};

struct Big : Card {
public:
    explicit Big(const Properties &prop) : Card(prop, 1) {
    }
};

struct Stomper : Card {
public:
    explicit Stomper(const Properties &prop) : Card(prop, 0) {
    }
};

#endif  // EVOLUTION_PROJECT_INCLUDE_CARDS_H_
