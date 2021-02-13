#ifndef EVOLUTION_PROJECT_INCLUDE_BOARD_H_
#define EVOLUTION_PROJECT_INCLUDE_BOARD_H_

#include "animal.h"
#include "cards.h"
#include "player.h"

struct Board {
    int feeding_units;  //кол-во еды в кормовой базе
    std::vector<Animal> get_players_animals(Player player);

    //ждем Эмили для этого
    // TODO добавляем еды
};

#endif  // EVOLUTION_PROJECT_INCLUDE_BOARD_H_
