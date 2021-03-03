#include "player.h"
#include <cassert>
#include <utility>


size_t Player::size_cards_owning_in_hands() const {
    return cards_in_hands.size();
}

const std::vector<std::shared_ptr<Animal>> & Player::get_animals_on_board() const {
    return animals_on_board;
}

void Player::erase_card_from_hand(const std::shared_ptr<Card> &which_card) {
    for (auto it = cards_in_hands.begin(); it != cards_in_hands.end(); ++it) {
        if (it->get() == which_card.get()) {
            cards_in_hands.erase(it);
            break;
        }
    }
}

void Player::add_card_in_hands(const std::shared_ptr<Card> &card) {
    cards_in_hands.push_back(card);
}

std::string Player::get_name() const {
    return name;
}

std::vector<std::shared_ptr<Card>> const &Player::get_cards_in_hands() const {
    return cards_in_hands;
}

std::pair<Properties, int> Player::get_card_information(const std::shared_ptr<Card> &looking_card) {
    for (const auto &card : cards_in_hands) {
        if (card.get() == looking_card.get()) {
            assert(card->property != Properties::DEFAULT);
            std::pair<Properties::_enumerated, int> tmp = {card->property, card->extra_food};
            erase_card_from_hand(looking_card);
            return tmp;
        }
    }
    // bullshit? how to guarantee that he will find that card?
    return {Properties(static_cast<Properties::_enumerated>(0)), -1};
}

/////calling only if someone refer to player's animals_on_board
void Player::update_animals_on_board(Player::BoardAnimals const &animals) {
    animals_on_board = animals;
}

void Player::set_name(std::string name_) {
    name = std::move(name_);
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
