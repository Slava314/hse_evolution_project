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
    Game() {
        phase = std::make_unique<DevelopmentPhase>(*this);
    }
    void start_game();
    std::size_t get_deck_size() const;
    std::unique_ptr<Phase> const &get_phase() const;
    void set_phase(std::unique_ptr<Phase> new_phase);
    std::vector<Player> const &get_players() const;
    void add_animal(const std::shared_ptr<Card> &card, const std::shared_ptr<Animal> &new_animal);
    std::size_t get_current_player() const;

    std::vector<std::vector<std::shared_ptr<Card>>> cards_delivery();

private:
    std::unique_ptr<Phase> phase;
    Board board;
    std::vector<Player> players;
    Deck deck;
    std::size_t current_player = 0;
};

#endif  // EVOLUTION_PROJECT_INCLUDE_GAME_H_
