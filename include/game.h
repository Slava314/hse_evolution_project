#ifndef EVOLUTION_PROJECT_INCLUDE_GAME_H_
#define EVOLUTION_PROJECT_INCLUDE_GAME_H_
#include <memory>
#include <vector>
#include "board.h"
#include "deck.h"
#include "phase.h"
#include "player.h"

class Game {
public:
    // Game() = default;
    Game() {
        phase = std::make_unique<Development_Phase>(*this);
    }
    void start_game();
    std::size_t get_deck_size();
    std::unique_ptr<Phase> get_phase() const;

    void cards_delivery();


private:
    std::unique_ptr<Phase> phase;
    Board board;
    std::vector<Player> players;
    Deck deck;
};

#endif  // EVOLUTION_PROJECT_INCLUDE_GAME_H_
