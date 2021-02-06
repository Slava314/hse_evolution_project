//
// Created by Андрей Шеремеев on 06.02.2021.
//

#ifndef EVOLUTION_PROJECT_INCLUDE_BOARD_H_
#define EVOLUTION_PROJECT_INCLUDE_BOARD_H_

#include "Cards.h"
#include <random>
#include "Player.h"

struct Deck {
  std::vector<std::unique_ptr<Card>> deck_of_uniqs; //*указатели на карты

  void generate_deck(std::vector<std::pair<Properties, int>> &cards_info) {}

  int get_deck_size() const {}

  void cards_delivery(Deck &deck, std::vector<Player> &players) {}

};

struct Board {
  static const int ALL_PLAYERS;
  Deck deck;
  std::vector<std::vector<std::unique_ptr<Animal>>> plyers_animals_on_board;

  int choose_players_order(int ALL_PLAYERS) {}

  int whoose_next_turn(int prev, int ALL_PLAYERS) {}

  //ждем Эмили для этого
//TODO FEEDING UNITS PRIVATE?
// TODO добавляем еды

};

#endif //EVOLUTION_PROJECT_INCLUDE_BOARD_H_
