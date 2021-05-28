#ifndef EVOLUTION_PROJECT_INCLUDE_PLAYER_H_
#define EVOLUTION_PROJECT_INCLUDE_PLAYER_H_

#include <memory>
#include <string>
#include <utility>
#include "animal.h"
#include "cards.h"
#include "properties.h"

class Player {
public:
    /// i will do it
    Player() = default;
    explicit Player(std::string name_);

    using BoardAnimals = std::vector<std::shared_ptr<Animal>>;
    using Prop = Properties;

    [[nodiscard]] std::string &get_name();
    void set_name(std::string name_);

    void add_card_in_hands(const std::shared_ptr<Card> &card);
    void put_card_as_animal(const std::shared_ptr<Card> &which_card,
                            const std::shared_ptr<Animal> &animal);
    void put_card_as_animal(const std::shared_ptr<Animal> &animal);
    void use_card_as_property(const std::shared_ptr<Card> &which_card,
                              const std::shared_ptr<Animal> &to_which_card);

    void kill_animal(const std::shared_ptr<Animal> &animal);

    std::pair<Prop, int> get_card_info(const std::shared_ptr<Card> &card);
    [[nodiscard]] const std::vector<std::shared_ptr<Animal>> &get_animals_on_board() const;
    [[nodiscard]] std::vector<std::shared_ptr<Card>> const &get_cards_in_hands() const;
    size_t count_animal_properties(const std::shared_ptr<Animal> &animal);

    void handle_animal_death(std::shared_ptr<Animal> const &animal);

    std::size_t count_result() const;
    const std::string &get_name() const;
    std::size_t get_reset() const;

private:
    void erase_card_from_hands(const std::shared_ptr<Card> &which_card);

    std::vector<std::shared_ptr<Card>> cards_in_hands;
    std::vector<std::shared_ptr<Animal>> animals_on_board;
    std::string name;
    std::size_t reset = 0;
    bool chose_to_end_phase = false;
};

#endif  // EVOLUTION_PROJECT_INCLUDE_PLAYER_H_