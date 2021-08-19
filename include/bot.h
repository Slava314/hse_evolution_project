#ifndef EVOLUTION_PROJECT_BOT_H
#define EVOLUTION_PROJECT_BOT_H
#include <string>
#include <unordered_map>
#include <vector>
#include "game_fwd.h"
#include "cards.h"
#include "animal.h"
#include "player.h"

struct Bot {
private:
    void make_move_in_dev_phase(Game &game);
    void make_move_in_feed_phase(Game &game);
    void play_card_as_animal(Game &game, const std::shared_ptr<Card> &);
    void play_card_as_property(Game &game,
                               const std::shared_ptr<Card> &,
                               const std::shared_ptr<Animal> &);
    Player &get_bot_player(Game &game);
    int random_num(int min, int max);
    void end_turn(Game &game);

public:
    Bot() = default;
    void make_move(Game &game);
};
#endif  // EVOLUTION_PROJECT_BOT_H
