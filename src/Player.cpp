//
// Created by Андрей Шеремеев on 07.02.2021.
//

#include "Cards.h"
#include "Animal.h"

#include <string>

struct Player {
  std::string name;
  std::vector<std::unique_ptr<Card>> cards_in_hands;
  std::vector<Animal> animals_on_board;

  int cards_owning_in_hands() const {
    return cards_in_hands.size();
  }

  int get_animals_count() const {
    return animals_on_board.size();
  }

  void use_card_as_animal(int which_card) {
    //добавляется новая карта животного у игрока
    animals_on_board.emplace_back(Animal());
    //удаляется в руках
    cards_in_hands.erase(cards_in_hands.begin() + which_card);
  }

  void use_card_as_property(int which_card, int to_which_card) {
    //FUTURE-TODO учесть в будуем, что нужно еще выбрать игрока, которому применяется свойство
    animals_on_board[to_which_card].animals_properties.push_back(cards_in_hands[which_card]->property);
    cards_in_hands.erase(cards_in_hands.begin() + which_card);
  }

  bool can_make_move(){}


  std::vector<std::unique_ptr<Card>> get_cards(){
    return cards_in_hands;
  }


};
