#ifndef EVOLUTION_PROJECT_INCLUDE_PLAYER_H_
#define EVOLUTION_PROJECT_INCLUDE_PLAYER_H_

#include <memory>
#include <string>
#include "animal.h"
#include "cards.h"

class Player {
    std::string name;
    bool chose_to_end_phase = false;

    std::vector<std::unique_ptr<Card>> cards_in_hands;
    std::vector<Animal> animals_on_board;

public:
    int size_cards_owning_in_hands() const;
    int get_animals_count() const;
    void put_card_as_animal(int which_card);
    void use_card_as_property(int which_card, int to_which_card);

      std::vector<std::unique_ptr<Card>> get_cards{};

    bool can_lay_out_as_animal() const;

    void add_card(std::unique_ptr<Card> &card);

    //[[nodiscard]] std::vector<std::unique_ptr<Card>> const &get_cards() const;
};

#endif  // EVOLUTION_PROJECT_INCLUDE_PLAYER_H_
