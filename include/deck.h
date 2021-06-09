#ifndef EVOLUTION_PROJECT_INCLUDE_DECK_H_
#define EVOLUTION_PROJECT_INCLUDE_DECK_H_

#include <random>
#include <vector>
#include "cards.h"
#include "player.h"
#include "properties.h"

class Deck {
public:
    Deck() = default;
    Deck(const int &seed, const int &size);
    std::vector<std::shared_ptr<Card>> get_deck_cards();
    void generate_deck();
    [[nodiscard]] int get_deck_size() const;
    void cards_delivery(Player& player);
    void cards_delivery(std::vector<Player> &players);

        void set_random_gen(int seed);
    void set_cards_info();
    int need_card(const Player &player);
private:
    static const int CARDS_TYPE = 7;
    std::vector<std::pair<Properties, int>> cards_info;
    std::vector<std::shared_ptr<Card>> deck_of_cards;
    //TODO initialoze random with seed
    std::mt19937 random_gen;
    int deck_size;
    static const int FULL_GET_CARDS = 6;
    static const int ADDING_CARDS = 1;
};

#endif  // EVOLUTION_PROJECT_INCLUDE_DECK_H_