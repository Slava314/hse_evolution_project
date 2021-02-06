//
// Created by Андрей Шеремеев on 07.02.2021.
//
#include "Board.h"

namespace {
struct Deck {
  std::vector<std::unique_ptr<Card>> deck_of_uniqs;

  void generate_deck(std::vector<std::pair<Properties, int>> &cards_info) {
    for (auto card : cards_info) {
      while (card.second--) {
        switch (card.first) {
          case ЖИРОВОЙ_ЗАПАС:deck_of_uniqs.push_back(std::make_unique<FatTissue>(FatTissue(card.first)));
          case БОЛЬШОЕ:deck_of_uniqs.push_back(std::make_unique<Big>(Big(card.first)));
          case ТОПОТУН:deck_of_uniqs.push_back(std::make_unique<Stomper>(Stomper(card.first)));
          default:continue;
        }
      }
    }

    auto rnd = std::default_random_engine{};
    std::shuffle(deck_of_uniqs.begin(), deck_of_uniqs.end(), rnd);
  }

  int get_deck_size() const {
    return deck_of_uniqs.size();
  }

  //TODO - check its correctness
  void cards_delivery(Deck &deck, std::vector<Player> &players) {
    for (auto i = 0; i < players.size(); ++i) {
      int need_to_get;
      if (players[i].cards_in_hands.empty()) {
        need_to_get = 6;
      } else {
        need_to_get = players[i].cards_in_hands.size() + 1;
      }

      for (int i = 0; i < need_to_get; ++i) {
//    std::move(end(deck.deck), end(deck.deck), std::inserter(player.cards_in_hands, end(player.cards_in_hands)));
        players[i].cards_in_hands.push_back(nullptr);
        std::swap(deck.deck_of_uniqs.back(), players[i].cards_in_hands.back());
        deck.deck_of_uniqs.pop_back();
      }
    }
  }

};

struct Board {
  const int ALL_PLAYERS;
  Deck deck;
  std::vector<std::vector<std::unique_ptr<Animal>>> plyers_animals_on_board;

  int choose_players_order(int quantity) {
    int first = rand() % quantity;
    return first;
  }

  int whoose_next_turn(int prev, int quantity) {
    int next = (prev + 1) % quantity;
    return next;
  }

};
}


