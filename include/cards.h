#ifndef EVOLUTION_PROJECT_INCLUDE_CARDS_H_
#define EVOLUTION_PROJECT_INCLUDE_CARDS_H_

#include "properties.h"

class Card {
public:
    //this is weird
    Properties property = Properties::DEFAULT;
    int extra_food = 0;
    // this one only for default case, to create a fake card to deliver cards to players
    explicit Card(Properties prop) : property(prop){
    }

    std::pair<Properties, int> get_info();
//    Card() = default;
    ~Card() = default;

protected:
    explicit Card(Properties prop, int food) : property(prop), extra_food(food){
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
