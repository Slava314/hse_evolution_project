//
// Created by Андрей Шеремеев on 10.02.2021.
//


#include <vector>

#include "Player.h"
#include "Board.h"
#include "Deck.h"

struct Game {
  Deck deck;
  Board board;

std::vector<Player> players;


  int shuffle_players (int quantity) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(players.begin(), players.end(), g);
  }



};