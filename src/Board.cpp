//
// Created by Андрей Шеремеев on 07.02.2021.
//
#include <random>

#include "Animal.h"
#include "Board.h"
#include "Player.h"

namespace {
struct Board {
  //TODO - поддержать правильное их расположение (как и сами игроки в векторе players)

  //вернет вектор сутруктур Animal, в котором можно пройтись по вектору свойств (enum)?
  //TODO мне очень не нравится вообще этот момент и логика тут, нужно будет обдумать
  std::vector<Animal> get_players_animals(Player player) {
    //нужно учитыать, что при вызове этого метода в фазе Кормления карты могут модифицироваться
    //и нужно отображать изменения в обоих случаях
    //то есть в фазе Кормления они вызовуться в каждый ход игрока
    return player.animals_on_board;
  }

};
}


