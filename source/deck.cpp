#include "deck.h"
#include <algorithm>
#include <random>
#include <vector>
#include "properties.h"

void Deck::generate_deck(std::vector<std::pair<Properties, int>> &cards_info) {
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
                case Properties::SWIMMINGS:
                    deck_of_cards.push_back(
                        std::make_shared<Swimmings>(Properties(Properties::SWIMMINGS)));
                    break;
                case Properties::RUNNING:
                    deck_of_cards.push_back(
                        std::make_shared<Running>(Properties(Properties::RUNNING)));
                    break;
                case Properties::CARNIVOROUS:
                    deck_of_cards.push_back(
                        std::make_shared<Carnivorous>(Properties(Properties::CARNIVOROUS)));
                    break;
                case Properties::BURROWING:
                    deck_of_cards.push_back(
                        std::make_shared<Burrowing>(Properties(Properties::BURROWING)));
                    break;
                case Properties::CAMOUFLAGE:
                    deck_of_cards.push_back(
                        std::make_shared<Camouflage>(Properties(Properties::CAMOUFLAGE)));
                    break;
                case Properties::SHARP_VISION:
                    deck_of_cards.push_back(
                        std::make_shared<SharpVision>(Properties(Properties::SHARP_VISION)));
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
    if (player.get_animals_on_board().empty() and player.get_cards_in_hands().empty()) {
        return 6;
    } else {
        if (player.get_animals_on_board().size() + player.get_cards_in_hands().size() + 1 > 6) {
            return std::max(static_cast<unsigned long>(0), 6 - player.get_cards_in_hands().size());
        } else {
            return player.get_animals_on_board().size() + 1;
        }
    }
}

void Deck::cards_delivery(std::vector<Player> &players) {
    for (auto &player : players) {
        auto need = std::min(need_card(player), static_cast<int>(deck_of_cards.size()));
        while (need--) {
            player.add_card_in_hands(deck_of_cards.back());
            deck_of_cards.pop_back();
        }
    }
}
std::vector<std::shared_ptr<Card>> Deck::get_deck_cards() {
    return deck_of_cards;
}