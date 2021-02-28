#ifndef EVOLUTION_PROJECT_INCLUDE_DECK_H_
#define EVOLUTION_PROJECT_INCLUDE_DECK_H_

#include <random>
#include <vector>
#include "cards.h"
#include "player.h"
#include "properties.h"

class Deck {
<<<<<<< HEAD
public:
    void generate_deck(std::vector<std::pair<Properties, int>> &cards_info);
    [[nodiscard]] int get_deck_size() const;
    void cards_delivery(std::vector<Player> &players);
    std::vector<std::unique_ptr<Card>> &get_deck();
private:
    std::vector<std::unique_ptr<Card>> deck_of_cards;  //*указатели на карты

=======
    std::vector<std::shared_ptr<Card>> deck_of_cards;  //*указатели на карты

public:
    void generate_deck(std::vector<std::pair<Properties, int>> &cards_info);
    [[nodiscard]] int get_deck_size() const;
    std::vector<std::vector<std::shared_ptr<Card>>> cards_delivery(std::vector<Player> &players);
>>>>>>> origin/main
};

#endif  // EVOLUTION_PROJECT_INCLUDE_DECK_H_
