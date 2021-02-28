#include "player.h"
#include <cassert>
int Player::size_cards_owning_in_hands() const {
    return cards_in_hands.size();
}

int Player::get_animals_count() const {
    return animals_on_board.size();
}

void Player::erase_card_from_hand(int which_card){
    cards_in_hands.erase(cards_in_hands.begin() + which_card);
}

void Player::put_card_as_animal(std::shared_ptr<Card> card, std::shared_ptr<Animal> new_animal) {
    //карта добавляется к себе в массив и также в вектор указателей доски

    //добавляется новая карта животного у игрока, чистая, без свойств
    animals_on_board.push_back(new_animal);
    //удаляется в руках, это ок, тк храним структуры
    erase_card_from_hand(which_card);
}

void Player::use_card_as_property(int which_card, int to_which_card) {
    // FUTURE-TODO учесть в будуем, что нужно еще выбрать игрока, к которому применяется свойство

    //проверка на владение объектом
    assert(cards_in_hands[which_card].operator bool());

    animals_on_board[to_which_card].animals_properties.push_back(
        cards_in_hands[which_card]->property);
    cards_in_hands[which_card].reset(nullptr);
    assert(cards_in_hands[which_card].get() == nullptr);
    erase_card_from_hand(which_card);

    for (int i = 0; i < cards_in_hands.size(); ++i) {
        if(cards_in_hands[i] == card){
            cards_in_hands.erase(cards_in_hands.begin() + i);
        }
    }
}

bool Player::can_lay_out_as_animal() const {
    //это неправда - тут нужно брать значение колоды и этого буля
    return (!cards_in_hands.empty() or !chose_to_end_phase);
}

//std::vector<std::unique_ptr<Card>> const &Player::get_cards() const {
//    return cards_in_hands;
//}

void Player::add_card(std::shared_ptr<Card> card) {
    cards_in_hands.push_back(card);
}

std::string Player::get_name() {
    return name;
}