#ifndef EVOLUTION_PROJECT_INCLUDE_PLAYER_H_
#define EVOLUTION_PROJECT_INCLUDE_PLAYER_H_

#include <memory>
#include <string>
#include "animal.h"
#include "cards.h"

class Player {
public:
    using BoardAnimals = std::vector<std::shared_ptr<Animal>>;

    int get_animals_count() const;
    std::size_t size_cards_owning_in_hands() const;

    const std::vector<std::shared_ptr<Animal>> & get_animals_on_board() const;
    void put_card_as_animal(std::shared_ptr<Card> card, std::shared_ptr<Animal> new_animal);
    void use_card_as_property(int which_card, int to_which_card);

    void add_card_in_hands(const std::shared_ptr<Card> &card);

    [[nodiscard]] std::vector<std::shared_ptr<Card>> const &get_cards_in_hands() const;
    std::pair<Properties, int> get_card_information(const std::shared_ptr<Card> &card);
    void update_animals_on_board(BoardAnimals const &animals);

    [[nodiscard]] std::string get_name() const;
    void set_name(std::string name_);

private:
    void erase_card_from_hand(const std::shared_ptr<Card> &which_card);
    void add_card(std::shared_ptr<Card> card);
    void handle_animal_death(std::shared_ptr<Animal> const & animal);

    std::vector<std::shared_ptr<Card>> cards_in_hands;
    std::vector<std::shared_ptr<Animal>> animals_on_board;
    std::string name;
    bool chose_to_end_phase = false;
};

#endif  // EVOLUTION_PROJECT_INCLUDE_PLAYER_H_