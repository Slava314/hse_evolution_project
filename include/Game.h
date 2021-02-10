//
// Created by Андрей Шеремеев on 10.02.2021.
//


#ifndef EVOLUTION_PROJECT_INCLUDE_GAME_H_
#define EVOLUTION_PROJECT_INCLUDE_GAME_H_

#include <vector>

#include "Player.h"
#include "Board.h"
#include "Deck.h"

struct Game {

  std::vector<Player> players;
  Deck deck;
  Board board;

  int shuffle_players(int quantity) {}

  void start_game() {}



};

#endif //EVOLUTION_PROJECT_INCLUDE_GAME_H_
