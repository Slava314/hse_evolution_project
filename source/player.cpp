#include "player.h"
#include <cassert>
int Player::size_cards_owning_in_hands() const {
    return cards_in_hands.size();
}

int Player::get_animals_count() const {
    return animals_on_board.size();
}

void Player::put_card_as_animal(int which_card) {
    //карта добавляется к себе в массив и также в вектор указателей доски

    //добавляется новая карта животного у игрока, чистая, без свойств
    animals_on_board.emplace_back(Animal());
    //удаляется в руках, это ок, тк храним структуры
    cards_in_hands.erase(cards_in_hands.begin() + which_card);
}

void Player::use_card_as_property(int which_card, int to_which_card) {
    // FUTURE-TODO учесть в будуем, что нужно еще выбрать игрока, к которому применяется свойство

    //проверка на владение объектом
    assert(cards_in_hands[which_card].operator bool());

    animals_on_board[to_which_card].animals_properties.push_back(
        cards_in_hands[which_card]->property);
    cards_in_hands[which_card].reset(nullptr);
    assert(cards_in_hands[which_card].get() == nullptr);
    cards_in_hands.erase(cards_in_hands.begin() + which_card);
}

bool Player::can_lay_out_as_animal() const {
    return (!cards_in_hands.empty());
}

std::vector<std::unique_ptr<Card>> const &Player::get_cards() const {
    return cards_in_hands;
}

void Player::add_card(std::unique_ptr<Card> &card) {
    cards_in_hands.emplace_back(std::move(card));
}
