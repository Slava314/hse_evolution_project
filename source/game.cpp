#include "game.h"
#include <algorithm>

void Game::shuffle_players(int quantity) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(players.begin(), players.end(), g);
}
