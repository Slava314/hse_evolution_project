#ifndef EVOLUTION_PROJECT_INCLUDE_DECK_H_
#define EVOLUTION_PROJECT_INCLUDE_DECK_H_

#include <random>
#include <vector>
#include "cards.h"
#include "player.h"
#include "properties.h"

struct Deck {
    std::vector<std::unique_ptr<Card>> deck_of_cards;  //*указатели на карты

    void generate_deck(std::vector<std::pair<Properties, int>> &cards_info);

    int get_deck_size() const;

    void cards_delivery(std::vector<Player> &players);
};

#endif  // EVOLUTION_PROJECT_INCLUDE_DECK_H_
