#include "deck.h"
#include <algorithm>
#include <random>
#include <vector>
#include "properties.h"

void Deck::generate_deck(std::vector<std::pair<Properties::_enumerated, int>> &cards_info) {
    for (auto card : cards_info) {
        while (card.second--) {
            switch (card.first) {
                case Properties::FAT_TISSUE:
                    deck_of_cards.push_back(std::make_shared<FatTissue>(FatTissue(card.first)));
                    break;
                case Properties::BIG:
                    deck_of_cards.push_back(std::make_shared<Big>(Big(card.first)));
                    break;
                case Properties::STOMPER:
                    deck_of_cards.push_back(std::make_shared<Stomper>(Stomper(card.first)));
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
        return std::max(6 - player.size_cards_owning_in_hands(), player.get_animals_on_board().size() +1);
    }
}

void Deck::cards_delivery(std::vector<Player> &players) {
    for (std::size_t i = 0; i < players.size(); i++) {
        auto need = need_card(players[i]);
        while (need--) {
            players[i].add_card_in_hands(deck_of_cards.back());
            deck_of_cards.pop_back();
        }
    }
}