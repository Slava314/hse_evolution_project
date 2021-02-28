// TODO - поддержать правильное их расположение (как и сами игроки в векторе
// players)

//вернет вектор сутруктур Animal, в котором можно пройтись по вектору свойств
//(enum)?
// TODO мне очень не нравится вообще этот момент и логика тут, нужно будет
// обдумать

//нужно учитыать, что при вызове этого метода в фазе Кормления карты могут
//модифицироваться и нужно отображать изменения в обоих случаях то есть в фазе
//Кормления они вызовуться в каждый ход игрока

#include "board.h"

//std::vector<Animal> Board::get_players_animals(Player player) {
//    return player.animals_on_board;
//}

void Board::use_card_as_animal(int player_index){
    lying_cards[player_index].push_back(std::make_unique<Animal>(Animal()));
}

//void Board::get_player_index(Player &needed_player){
//    for (auto &player : lying_cards) {
//        if(player == needed_player.get_name()){
//
//        }
//    }
//}
