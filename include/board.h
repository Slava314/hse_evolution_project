#ifndef EVOLUTION_PROJECT_INCLUDE_BOARD_H_
#define EVOLUTION_PROJECT_INCLUDE_BOARD_H_

#include "animal.h"
#include "cards.h"
#include "player.h"

class Board {
    //TODO - generator for food - for Emily
    int feeding_units = 0;  //кол-во еды в кормовой базе
    //std::vector<std::vector<std::unique_ptr<Animal>>> lying_cards;

public:
    //он точно должени принимать стурктуру игрока, а не номер, например, в векторе всех игроков?
    std::vector<Animal> get_players_animals(Player player);
    void get_player_index(Player &player);
    void use_card_as_animal(int player_index);

        // TODO добавляем еды - Emily

private:
    //TODO - generator for food - for Emily
    int feeding_units = 0;  //кол-во еды в кормовой базе
    std::vector<std::vector<std::unique_ptr<Animal>>> lying_cards;
};

#endif  // EVOLUTION_PROJECT_INCLUDE_BOARD_H_
