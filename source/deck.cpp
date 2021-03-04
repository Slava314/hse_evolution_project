#include "deck.h"
#include <algorithm>
#include <random>
#include <vector>
#include "properties.h"

void Deck::generate_deck(std::vector<std::pair<Properties::_enumerated, int>> &cards_info) {
    for (auto card : cards_info) {
        while (card.second--) {
            Properties pr(static_cast<Properties::_enumerated>(0));
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

    auto rnd = std::default_random_engine{};
    std::shuffle(deck_of_cards.begin(), deck_of_cards.end(), rnd);
}

int Deck::get_deck_size() const {
    return deck_of_cards.size();
}

int need_card(Player const &player) {
    if (player.get_cards_in_hands().empty()) {
        return 6;
    } else {
        return std::max(6 - player.get_cards_in_hands().size(),
                        player.get_animals_on_board().size() + 1);
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
