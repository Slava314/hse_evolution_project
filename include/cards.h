#ifndef EVOLUTION_PROJECT_INCLUDE_CARDS_H_
#define EVOLUTION_PROJECT_INCLUDE_CARDS_H_

#include "properties.h"

class Card {
public:
    // this is weird
    Properties property = Properties::DEFAULT;

    int extra_food = 0;
    // this one only for default case, to create a fake card to deliver cards to players
    explicit Card(Properties prop) : property(prop) {
    }

    std::pair<Properties, int> get_info();
    //    Card() = default;

    ~Card() = default;

protected:
    explicit Card(Properties prop, int food) : property(prop), extra_food(food) {
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

struct Swimmings : Card {
public:
    explicit Swimmings(const Properties &prop) : Card(prop, 0) {
    }
};

struct Running : Card {
public:
    explicit Running(const Properties &prop) : Card(prop, 0) {
    }
};

struct Carnivorous : Card {
public:
    explicit Carnivorous(const Properties &prop) : Card(prop, 1) {
    }
};

struct Burrowing : Card {
public:
    explicit Burrowing(const Properties &prop) : Card(prop, 0) {
    }
};

struct Camouflage : Card {
public:
    explicit Camouflage(const Properties &prop) : Card(prop, 0) {
    }
};

struct SharpVision : Card {
public:
    explicit SharpVision(const Properties &prop) : Card(prop, 0) {
    }
};

#endif  // EVOLUTION_PROJECT_INCLUDE_CARDS_H_
