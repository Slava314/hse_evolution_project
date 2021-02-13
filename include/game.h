#ifndef EVOLUTION_PROJECT_INCLUDE_GAME_H_
#define EVOLUTION_PROJECT_INCLUDE_GAME_H_

#include <vector>
#include "board.h"
#include "deck.h"
#include "player.h"

struct Game {
    std::vector<Player> players;
    Deck deck;
    Board board;

    void shuffle_players(int quantity);

    void start_game() {
    }
};

#endif  // EVOLUTION_PROJECT_INCLUDE_GAME_H_
