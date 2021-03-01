#include "board.h"

std::vector<std::shared_ptr<Animal>> Board::get_players_animals(std::size_t index) {
    return lying_cards[index];
}

std::size_t Board::get_players_animals_size(std::size_t index) {
    return lying_cards[index].size();
}

std::size_t Board::lying_cards_size() {
    return lying_cards.size();
}

void Board::put_card_as_animal(const std::shared_ptr<Animal> &new_animal) {
    lying_cards[0].push_back(new_animal);
}

void Board::use_card_as_property(std::pair<Properties, int> adding,
                                 const std::shared_ptr<Animal> &to_which_card) {
    ////TODO учесть в будуем, что нужно еще выбрать игрока, к которому применяется свойство
    for (auto it = lying_cards[0].begin(); it != lying_cards[0].end(); it++) {
        if (it->get() == to_which_card.get()) {
            it->get()->animals_properties.push_back(adding.first);

            // TODO раскомментить когда притянется animal.h

            //            it->get().food_needed = adding.second;
        }
    }
}

std::size_t Board::count_animals_properties(std::size_t position,
                                            const std::shared_ptr<Animal> &animal) {
    for (const auto &anim : lying_cards[position]) {
        if (anim.get() == animal.get()) {
            return anim->animals_properties.size();
        }
    }
    return -1;
}

void Board::resize_lying_cards(std::size_t counter) {
    lying_cards.resize(counter);
}
