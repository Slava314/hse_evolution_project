#ifndef EVOLUTION_PROJECT_INCLUDE_DECK_H_
#define EVOLUTION_PROJECT_INCLUDE_DECK_H_

#include <random>
#include <vector>
#include "cards.h"
#include "player.h"
#include "properties.h"

class Deck {
    std::vector<std::shared_ptr<Card>> deck_of_cards;

public:
    void generate_deck(std::vector<std::pair<Properties::_enumerated, int>> &cards_info);
    [[nodiscard]] int get_deck_size() const;
    void cards_delivery(std::vector<Player> &players);
};

#endif  // EVOLUTION_PROJECT_INCLUDE_DECK_H_