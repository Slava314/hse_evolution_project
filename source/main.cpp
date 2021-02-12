//
// Created by Андрей Шеремеев on 30.01.2021.
//

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <random>
#include <memory>

#include "Game.h"
#include "Properties.h"
#include "Animal.h"
#include "Board.h"
#include "Cards.h"
#include "Player.h"



int main() {
  // THESE IS IMPORTANT
  constexpr int N = 3;
  std::vector<std::pair<Properties, int>> cards_info(N);
  cards_info[0] = {ЖИРОВОЙ_ЗАПАС, 8};
  cards_info[1] = {БОЛЬШОЕ, 8};
  cards_info[2] = {ТОПОТУН, 8};
  //--------------------


//  Deck deck;
//
//  deck.generate_deck(cards_info);
//   assert(deck.deck.size() == MUST_BE_IN_DECK);


//    for (int i = 0; i < deck.deck.size(); ++i) {
//        std::cout << deck.deck[i]->property1 << " ";
//    }
//
//    std::cout << std::endl;
//    for (int i = 0; i < deck.deck.size(); ++i) {
//        std::cout << deck.deck[i]->property2 << " ";
//    }

//---------

//  Player player1;
//  whoose_next_turn(1, 1);
//  Deck d;
//  d.generate_deck(cards_info);
////  cards_delivery();
//  for (int kI = 0; kI < player1.cards_owning_in_hands(); ++kI) {
//    std::cout << player1.cards_in_hands[kI] << " ";
//  }
//Board board;
//Player ok;
//Game g;
//  std::vector<std::vector<std::unique_ptr<Animal>>> a;
//  g.board.plyers_animals_on_board *a = g.players[0].animals_on_board;


}
