#ifndef EVOLUTION_PROJECT_INCLUDE_GAME_H_
#define EVOLUTION_PROJECT_INCLUDE_GAME_H_
#include <memory>
#include <vector>
#include "deck.h"
#include "phase.h"
#include "player.h"
#include "settings.h"

class Game {
public:
    using PlayerCards = std::vector<std::shared_ptr<Card>>;

    Game(struct Settings settings_);
    Game();

    void start_game();
    [[nodiscard]] std::unique_ptr<Phase> const &get_phase() const;
    void set_phase(std::unique_ptr<Phase> new_phase);

    std::vector<Player> &get_players();
    std::size_t get_cur_player() const;
    std::vector<PlayerCards> get_players_cards_in_hands();
    std::vector<std::shared_ptr<Card>> get_deck_cards();
    Deck &get_deck();

    size_t get_deck_size();

private:
    std::unique_ptr<Phase> phase;
    std::vector<Player> players;
    Deck deck;
    Settings settings;
};

#endif  // EVOLUTION_PROJECT_INCLUDE_GAME_H_