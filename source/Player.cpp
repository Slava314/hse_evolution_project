//
// Created by Андрей Шеремеев on 07.02.2021.
//

#include <string>

#include "Player.h"
int Player::size_cards_owning_in_hands() const {
  return cards_in_hands.size();
}

int Player::get_animals_count() const {
  return animals_on_board.size();
}

void Player::use_card_as_animal(int which_card) {
  //добавляется новая карта животного у игрока
  animals_on_board.emplace_back(Animal());
  //удаляется в руках
  cards_in_hands.erase(cards_in_hands.begin() + which_card);
}

void Player::use_card_as_property(int which_card, int to_which_card) {
  //FUTURE-TODO учесть в будуем, что нужно еще выбрать игрока, которому применяется свойство
  animals_on_board[to_which_card].animals_properties.push_back(cards_in_hands[which_card]->property);
  cards_in_hands.erase(cards_in_hands.begin() + which_card);
}

bool Player::can_make_move() { return false; }

std::vector<std::unique_ptr<Card>> const & Player::get_cards() const {
  return cards_in_hands;
}

