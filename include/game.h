#ifndef EVOLUTION_PROJECT_INCLUDE_GAME_H_
#define EVOLUTION_PROJECT_INCLUDE_GAME_H_
#include <memory>
#include <vector>
#include "bot.h"
#include "deck.h"
#include "phase.h"
#include "player.h"
#include "settings.h"

class Game {
public:
    using PlayerCards = std::vector<std::shared_ptr<Card>>;

    Game(struct Settings settings_);
    Game();

    void start_game(Settings settings_);
    [[nodiscard]] std::unique_ptr<Phase> const &get_phase() const;
    void set_phase(std::unique_ptr<Phase> new_phase);

    std::vector<Player> &get_players();
    std::size_t get_cur_player_index() const;
    std::vector<PlayerCards> get_players_cards_in_hands();
    std::vector<std::shared_ptr<Card>> get_deck_cards();
    Deck &get_deck();
    size_t get_deck_size();
    Settings const &get_settings() const;
    std::size_t get_local_player_index() const;
    void set_end_game(int i);
    int get_end_game() const;
    void set_players_ended_turn(int value);
    int get_players_ended_turn() const;
    std::unique_ptr<Bot> const &get_bot() const;

private:
    std::unique_ptr<Phase> phase;
    std::vector<Player> players;
    Deck deck;
    Settings settings;
    int end_of_game = 0;
    int players_ended_turn = 0;
    std::unique_ptr<Bot> bot;
};

#endif  // EVOLUTION_PROJECT_INCLUDE_GAME_H_