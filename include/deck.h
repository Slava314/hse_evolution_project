#ifndef EVOLUTION_PROJECT_INCLUDE_DECK_H_
#define EVOLUTION_PROJECT_INCLUDE_DECK_H_

#include <random>
#include <vector>
#include "cards.h"
#include "player.h"
#include "properties.h"

class Deck {
public:
    void generate_deck(std::vector<std::pair<Properties, int>> &cards_info);
    [[nodiscard]] int get_deck_size() const;
    void cards_delivery(std::vector<Player> &players);
    std::vector<std::unique_ptr<Card>> &get_deck();
private:
    std::vector<std::unique_ptr<Card>> deck_of_cards;  //*указатели на карты

};

#endif  // EVOLUTION_PROJECT_INCLUDE_DECK_H_
