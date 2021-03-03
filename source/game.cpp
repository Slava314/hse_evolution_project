#include "game.h"
#include <SFML/Graphics.hpp>
#include <utility>

std::unique_ptr<Phase> const &Game::get_phase() const {
    return phase;
}

std::size_t Game::get_deck_size() {
    return deck.get_deck_size();
}
void Game::start_game() {
    // TODO set number of players

    // TODO - get count of players as a parametr. From GUI?
    std::size_t counter = 1;
    resize_all_data(counter);

    // временное решение по генерации, пока нет настроек и больше карт
    constexpr int N = 3;
    std::vector<std::pair<Properties::_enumerated, int>> cards_info(N);
    cards_info[0] = {Properties::FAT_TISSUE, 8};
    cards_info[1] = {Properties::BIG, 8};
    cards_info[2] = {Properties::STOMPER, 8};
    deck.generate_deck(cards_info);
}

void Game::set_phase(std::unique_ptr<Phase> new_phase) {
    phase.swap(new_phase);
}

std::vector<Player> &Game::get_players() {
    return players;
}

void Game::add_animal(const std::shared_ptr<Card> &card,
                      const std::shared_ptr<Animal> &new_animal) {
    board.put_card_as_animal(new_animal);
    update_every_player_animals();
}

void Game::add_property(const std::shared_ptr<Card> &card,
                        const std::shared_ptr<Animal> &new_animal) {
    assert(card.operator bool());
    assert(new_animal.operator bool());
    // get 'Property' and 'Extra_Food' from card
    std::pair<Properties, int> tmp = players[0].get_card_information(card);
    board.use_card_as_property(tmp, new_animal);
}

void Game::cards_delivery() {
    update_every_player_animals();
    deck.cards_delivery(players);
}

void Game::add_player(const Player &player_) {
    players.push_back(player_);
}

std::vector<Game::PlayersCards> Game::get_players_cards_in_hands() {
    std::vector<Game::PlayersCards> tmp(players.size());
    for (auto pl : players) {
        tmp.push_back(pl.get_cards_in_hands());
    }
    return tmp;
}

void Game::update_every_player_animals() {
    for (std::size_t i = 0; i < players.size(); i++) {
        if (board.lying_cards_size() and board.get_players_animals_size(i)) {
            players[i].update_animals_on_board(board.get_players_animals(i));
        }
    }
}

void Game::resize_all_data(std::size_t counter) {
    players.resize(counter);
    board.resize_lying_cards(counter);
}

Board &Game::get_board() {
    return board;
}
