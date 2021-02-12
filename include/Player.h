//
// Created by Андрей Шеремеев on 07.02.2021.
//

#ifndef EVOLUTION_PROJECT_INCLUDE_PLAYER_H_
#define EVOLUTION_PROJECT_INCLUDE_PLAYER_H_

#include "Animal.h"
#include "Cards.h"
#include <vector>
#include <string>

struct Player {
  std::string name;

  std::vector<std::unique_ptr<Card>> cards_in_hands;
  std::vector<Animal> animals_on_board;

  int size_cards_owning_in_hands() const;

  int get_animals_count() const;

  void use_card_as_animal(int which_card);

  void use_card_as_property(int which_card, int to_which_card);

//  std::vector<std::unique_ptr<Card>> get_cards{};

  bool can_make_move();

  std::vector<std::unique_ptr<Card>> const & get_cards() const;

};

#endif //EVOLUTION_PROJECT_INCLUDE_PLAYER_H_
