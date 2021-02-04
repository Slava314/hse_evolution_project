//
// Created by Андрей Шеремеев on 30.01.2021.
//

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <random>

enum Properties {
    ЖИРОВОЙ_ЗАПАС,
    БОЛЬШОЕ,
    ТОПОТУН
};

struct Card {
    int property1 = 0;
    int property2 = 0;
    Card(int i, int j) {
        if(j == -1) {
            property1 = Properties(i);
        } else{
            property1 = Properties(i);
            property2 = Properties(j);
        }
    }
};


struct Deck {
    std::vector<Card*> deck;

    void generate_deck(std::vector<std::pair<std::pair<int, int>, int>>  &cards_info){
        for(auto card : cards_info){
            while (card.second--){
                deck.push_back(new Card(card.first.first, card.first.second));
            }
        }
        auto rnd = std::default_random_engine {};
        std::shuffle(deck.begin(), deck.end(), rnd);
    }

    int get_deck_size(){
        return deck.size();
    }



};

struct Player{
std::vector<Card*> cards_in_hands;
//TODO знает какие карты у него на руках и их свойства

//TODO уметь получать количество его животных, выложенных на карту

};

struct Board{
//TODO - поле должно знать колоду

//TODO - полле должно знать какие животные выложены у каждого игрока на карте

};

struct Game{
//TODO ???
};

int main() {
    constexpr int N = 3;
    constexpr int MUST_BE_IN_DECK = 24;
    std::vector<std::pair<std::pair<int, int>, int>> cards_info(N);
    cards_info[0] = {{0, -1}, 8};
    cards_info[1] = {{1, -1}, 8};
    cards_info[2] = {{2, -1}, 8};

   Deck deck;
   deck.generate_deck(cards_info);
//   assert(deck.deck.size() == MUST_BE_IN_DECK);


//    for (int i = 0; i < deck.deck.size(); ++i) {
//        std::cout << deck.deck[i]->property1 << " ";
//    }
//
//    std::cout << std::endl;
//    for (int i = 0; i < deck.deck.size(); ++i) {
//        std::cout << deck.deck[i]->property2 << " ";
//    }

}

namespace phase_development{
    //выбор первого игрока, а дальше по ходу
    int choose_players_order(int quantity){
        int first = rand() % quantity;
        return first;
    }

    int whoose_next_turn(int quantity, int prev){
        int next = (prev + 1) % quantity;
        return next;
    }

    //всегда добавляется кол-во животных + 1, а если 0 карт на руках - 6
    //TODO раздача карт, возможно траблы с указателями, нужно будет еще обработать этот момент
    void first_card_delivery(Deck& deck, Player player, int animal_cards){
        int need_to_deliver;
        if(animal_cards == 0) {
            need_to_deliver = 6;
        } else{
            need_to_deliver = animal_cards + 1;
        }

        for (int i = 0; i < need_to_deliver; ++i) {
            player.cards_in_hands.push_back(deck.deck.back());
            deck.deck.pop_back();
        }
    }




}