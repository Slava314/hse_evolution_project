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
    using PlayerCards = std::vector<std::shared_ptr<Card>>;


    Game() {
        phase = std::make_unique<DevelopmentPhase>(*this);
    }
    void start_game();
    size_t get_deck_size();
    [[nodiscard]] std::unique_ptr<Phase> const &get_phase() const;
    void set_phase(std::unique_ptr<Phase> new_phase);

    std::vector<Player> &get_players();

    // do not take into account different players
    void add_animal(std::shared_ptr<Card> &card, std::shared_ptr<Animal> &new_animal);
    void add_property(const std::shared_ptr<Card> &card, const std::shared_ptr<Animal> &new_animal);

    void cards_delivery();
    void add_player(Player const &player_);

    std::vector<PlayerCards> get_players_cards_in_hands();

private:

    std::unique_ptr<Phase> phase;
    //    Board board;
    std::vector<Player> players;
    Deck deck;
};

#endif  // EVOLUTION_PROJECT_INCLUDE_GAME_H_