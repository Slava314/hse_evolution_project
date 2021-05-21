#include "deck.h"
#include <algorithm>
#include <random>
#include <vector>
#include "properties.h"

void Deck::generate_deck() {
    for (auto card : cards_info) {
        while (card.second--) {
            switch (card.first) {
                case Properties::FAT_TISSUE:
                    deck_of_cards.push_back(
                        std::make_shared<FatTissue>(Properties(Properties::FAT_TISSUE)));
                    break;
                case Properties::BIG:
                    deck_of_cards.push_back(std::make_shared<Big>(Properties(Properties::BIG)));
                    break;
                case Properties::STOMPER:
                    deck_of_cards.push_back(
                        std::make_shared<Stomper>(Properties(Properties::STOMPER)));
                    break;
                default:
                    continue;
            }
        }
    }

    std::shuffle(deck_of_cards.begin(), deck_of_cards.end(), random_gen);
}

int Deck::get_deck_size() const {
    return deck_of_cards.size();
}

int Deck::need_card(const Player &player) {
    if (player.get_animals_on_board().empty() and player.get_cards_in_hands().empty()) {
        return FULL_GET_CARDS;
    } else {
        if (player.get_animals_on_board().size() + player.get_cards_in_hands().size() + 1 > 6) {
            return std::max(static_cast<unsigned long>(0), FULL_GET_CARDS - player.get_cards_in_hands().size());
        } else {
            return player.get_animals_on_board().size() + ADDING_CARDS;
        }
    }
}

void Deck::cards_delivery(std::vector<Player> &players) {
    for (auto &player : players) {
        auto need = need_card(player);
        while (need--) {
            player.add_card_in_hands(deck_of_cards.back());
            deck_of_cards.pop_back();
        }
    }
}
std::vector<std::shared_ptr<Card>> Deck::get_deck_cards() {
    return deck_of_cards;
}

Deck::Deck(const int &seed, const int &size) {
    random_gen.seed(seed);
    deck_size = size;
}
void Deck::set_random_gen(int seed) {
    random_gen = std::mt19937 (seed);
}
void Deck::set_cards_info() {
    cards_info.resize(CARDS_TYPE);

    cards_info[0] = {Properties::FAT_TISSUE, 8};
    cards_info[1] = {Properties::BIG, 8};
    cards_info[2] = {Properties::STOMPER, 8};
}
