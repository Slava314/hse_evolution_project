//
// Created by Андрей Шеремеев on 11.02.2021.
//
#include <vector>
#include <random>

#include "Deck.h"

void Deck::generate_deck(std::vector<std::pair<Properties, int>> &cards_info) {
  for (auto card : cards_info) {
    while (card.second--) {
      switch (card.first) {
        case ЖИРОВОЙ_ЗАПАС:deck_of_cards.push_back(std::make_unique<FatTissue>(FatTissue(card.first)));
        case БОЛЬШОЕ:deck_of_cards.push_back(std::make_unique<Big>(Big(card.first)));
        case ТОПОТУН:deck_of_cards.push_back(std::make_unique<Stomper>(Stomper(card.first)));
        default:continue;
      }
    }
  }

  auto rnd = std::default_random_engine{};
  std::shuffle(deck_of_cards.begin(), deck_of_cards.end(), rnd);
}

int Deck::get_deck_size() const {
  return deck_of_cards.size();
}

//TODO - check its correctness
void Deck::cards_delivery(Deck &deck, std::vector<Player> &players) {
  for (auto i = 0; i < players.size(); ++i) {
    int need_to_get;
    if (players[i].cards_in_hands.empty()) {
      need_to_get = 6;
    } else {
      need_to_get = players[i].cards_in_hands.size() + 1;
    }

    for (int j = 0; j < need_to_get; ++j) {
//    std::move(end(deck.deck), end(deck.deck), std::inserter(player.cards_in_hands, end(player.cards_in_hands)));
      players[j].cards_in_hands.push_back(nullptr);
      std::swap(deck.deck_of_cards.back(), players[j].cards_in_hands.back());
      deck.deck_of_cards.pop_back();
    }
  }
}