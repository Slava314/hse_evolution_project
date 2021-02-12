//
// Created by Андрей Шеремеев on 07.02.2021.
//

#ifndef EVOLUTION_PROJECT_INCLUDE_CARDS_H_
#define EVOLUTION_PROJECT_INCLUDE_CARDS_H_

#include "Properties.h"
struct Card {
  Properties property = ДЕФОЛТНЫЙ;
  int extra_food = 0;
  explicit Card(Properties i) : property(i) {}
  Card(const Card &card){};
//  virtual ~Card() {};
};

struct FatTissue : Card {
  explicit FatTissue(Properties i) : Card(i) {
    [[maybe_unused]] bool is_it_full = 0;
  }

};

struct Big : Card {
  explicit Big(Properties i) : Card(i) {
    extra_food = 1;
  }
};

struct Stomper : Card {
  explicit Stomper(Properties i) : Card(i) {
  }
};

#endif //EVOLUTION_PROJECT_INCLUDE_CARDS_H_
