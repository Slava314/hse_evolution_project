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
                case Properties::RUNNING:
                    deck_of_cards.push_back(
                        std::make_shared<Running>(Properties(Properties::RUNNING)));
                case Properties::MIMICRY:
                    deck_of_cards.push_back(
                        std::make_shared<Mimicry>(Properties(Properties::MIMICRY)));
                case Properties::SWIMMINGS:
                    deck_of_cards.push_back(
                        std::make_shared<Swimmings>(Properties(Properties::SWIMMINGS)));
                    break;
                case Properties::RUNNING:
                    deck_of_cards.push_back(
                        std::make_shared<Running>(Properties(Properties::RUNNING)));
                case Properties::TAIL_LOSS:
                    deck_of_cards.push_back(
                        std::make_shared<TailLoss>(Properties(Properties::TAIL_LOSS)));
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
            auto n = std::max(static_cast<unsigned long>(0),
                              FULL_GET_CARDS - player.get_cards_in_hands().size());
            return (n > get_deck_size() ? get_deck_size() : n);
        } else {
            auto n = player.get_animals_on_board().size() + ADDING_CARDS;
            return (n > get_deck_size() ? get_deck_size() : n);
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

void Deck::cards_delivery(Player &player) {
    auto need = need_card(player);
    while (need--) {
        player.add_card_in_hands(deck_of_cards.back());
        deck_of_cards.pop_back();
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
    random_gen = std::mt19937(seed);
}
void Deck::set_cards_info() {
    cards_info.resize(CARDS_TYPE);

    cards_info[0] = {Properties::FAT_TISSUE, 8};
    cards_info[1] = {Properties::BIG, 8};
    cards_info[2] = {Properties::STOMPER, 8};
    cards_info[3] = {Properties::SWIMMINGS, 8};
    cards_info[4] = {Properties::RUNNING, 8};
    cards_info[5] = {Properties::CARNIVOROUS, 8};
    cards_info[6] = {Properties::BURROWING, 8};
    cards_info[7] = {Properties::CAMOUFLAGE, 8};
    cards_info[8] = {Properties::SHARP_VISION, 8};
}
