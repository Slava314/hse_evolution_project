//
// Created by Андрей Шеремеев on 10.02.2021.
//?

#include "Game.h"

void Game::shuffle_players(int quantity) {
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(players.begin(), players.end(), g);
}

