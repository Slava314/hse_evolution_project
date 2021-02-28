#include "deck.h"
#include <algorithm>
#include <random>
#include <vector>

void Deck::generate_deck(std::vector<std::pair<Properties, int>> &cards_info) {
    for (auto card : cards_info) {
        while (card.second--) {
            switch (card.first) {
                case FAT_TISSUE:
                    deck_of_cards.push_back(std::make_unique<FatTissue>(FatTissue(card.first)));
                    break;
                case BIG:
                    deck_of_cards.push_back(std::make_unique<Big>(Big(card.first)));
                    break;
                case STOMPER:
                    deck_of_cards.push_back(std::make_unique<Stomper>(Stomper(card.first)));
                    break;
                default:
                    continue;
            }
        }
    }

    auto rnd = std::default_random_engine{};
    std::shuffle(deck_of_cards.begin(), deck_of_cards.end(), rnd);
}

int Deck::get_deck_size() const {
    return deck_of_cards.size();
}

int need_card(Player const &player) {
    if (player.size_cards_owning_in_hands() == 0) {
        return 6;
    } else {
        return player.size_cards_owning_in_hands() + 1;
    }
}

void Deck::cards_delivery(std::vector<Player> &players) {
    for (auto &player : players) {
        auto need = need_card(player);
        while (need--) {
            player.add_card(deck_of_cards.back());
            deck_of_cards.pop_back();
        }
    }
}

std::vector<std::unique_ptr<Card>> &Deck::get_deck() {
    return deck_of_cards;
}
