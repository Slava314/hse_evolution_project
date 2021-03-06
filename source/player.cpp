#include "player.h"
#include <cassert>
#include <utility>

std::string &Player::get_name() {
    return name;
}

const std::vector<std::shared_ptr<Animal>> &Player::get_animals_on_board() const {
    return animals_on_board;
}

void Player::erase_card_from_hands(const std::shared_ptr<Card> &which_card) {
    assert(which_card.get() != nullptr);
    for (auto it = cards_in_hands.begin(); it != cards_in_hands.end(); ++it) {
        if (it->get() == which_card.get()) {
            cards_in_hands.erase(it);
            return;
        }
    }
    throw std::logic_error("CANNOT ERASE CARD FROM HANDS");
}

void Player::add_card_in_hands(const std::shared_ptr<Card> &card) {
    cards_in_hands.push_back(card);
}

std::vector<std::shared_ptr<Card>> const &Player::get_cards_in_hands() const {
    return cards_in_hands;
}

void Player::use_card_as_property(const std::shared_ptr<Card> &which_card,
                                  const std::shared_ptr<Animal> &to_which_card) {
    std::pair<Prop, int> adding = get_card_info(which_card);
    assert(which_card.get() != nullptr);
    assert(to_which_card.get() != nullptr);
    try {
        for (auto &it : animals_on_board) {
            if (it.get() == to_which_card.get()) {
                if (it->get_properties().find(static_cast<const Prop>(adding.second)) ==
                    it->get_properties().end()) {
                    erase_card_from_hands(which_card);  // delete only if can insert property
                    to_which_card->get_properties().insert(adding.first);
                    to_which_card->increase_food_needed(adding.second);
                }  // else{} - throw like an exeption for GUI - to look for another animal or
                // another card with property
            }
        }
    } catch (...) {
        throw std::logic_error("NON-VALID CARDS FOR THE MOVE");
    }
}

void Player::put_card_as_animal(const std::shared_ptr<Card> &which_card,
                                const std::shared_ptr<Animal> &animal) {
    assert(which_card.get() != nullptr);
    assert(animal.get() != nullptr);
    animals_on_board.push_back(animal);
    erase_card_from_hands(which_card);
}

std::pair<Player::Prop, int> Player::get_card_info(
    const std::shared_ptr<Card> &looking_card) {
    try {
        for (const auto &card : cards_in_hands) {
            if (card.get() == looking_card.get()) {
                assert(card->property != Properties::DEFAULT);
                return card->get_info();
            }
        }
    } catch (...) {
        throw std::logic_error("DID NOT FIND CARD IN HANDS");
    }
    return {Properties(static_cast<Properties::_enumerated>(0)), -1};
}

void Player::kill_animal(const std::shared_ptr<Animal> &animal) {
    handle_animal_death(animal);
}

void Player::handle_animal_death(const std::shared_ptr<Animal> &animal) {
    for (size_t i = 0; i < animals_on_board.size(); ++i) {
        if (animal == animals_on_board[i]) {
            animals_on_board.erase(animals_on_board.begin() + i);
            return;
        }
    }
    throw std::invalid_argument("PLAYER HAS NO SUCH ANIMAL");
}

size_t Player::count_animal_properties(const std::shared_ptr<Animal> &animal) {
    try {
        for (const auto &anim : animals_on_board) {
            if (anim.get() == animal.get()) {
                return animal->get_properties().size();
            }
        }
    } catch (...) {
        throw std::logic_error("DID NOt FIND ANIMAL ON thE BOARD");
    }
    return 1;
}