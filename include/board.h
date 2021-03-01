#ifndef EVOLUTION_PROJECT_INCLUDE_BOARD_H_
#define EVOLUTION_PROJECT_INCLUDE_BOARD_H_

#include "animal.h"
#include "cards.h"
#include "player.h"

class Board {
public:
    std::vector<std::shared_ptr<Animal>> get_players_animals(std::size_t index);
    std::size_t get_players_animals_size(std::size_t index);
    std::size_t lying_cards_size();

    void put_card_as_animal(const std::shared_ptr<Animal> &);

    void use_card_as_property(std::pair<Properties, int> adding,
                              const std::shared_ptr<Animal> &to_which_card);

    std::size_t count_animals_properties(std::size_t position,
                                         const std::shared_ptr<Animal> &animal);
    void resize_lying_cards(std::size_t counter);

private:
    int feeding_units = 0;
    using PLayersAnimals = std::vector<std::shared_ptr<Animal>>;
    std::vector<PLayersAnimals> lying_cards;
};
#endif  // EVOLUTION_PROJECT_INCLUDE_BOARD_H_
