#include "game.h"
#include <SFML/Graphics.hpp>
#include <utility>

std::unique_ptr<Phase> const &Game::get_phase() const {
    return phase;
}

size_t Game::get_deck_size() {
    return deck.get_deck_size();
}

void Game::start_game() {
    // TODO set number of players

    // TODO - get count of players as a parametr. From GUI? or lobby?
//    players.resize(1);
    players.emplace_back("shershen0_first_player");
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

void Game::add_animal(std::shared_ptr<Card> &card,
                      std::shared_ptr<Animal> &new_animal) {
    players[0].put_card_as_animal(card, new_animal);
}

void Game::add_property(const std::shared_ptr<Card> &card,
                        const std::shared_ptr<Animal> &animal) {
    assert(card.get() != nullptr);
    assert(animal.get() != nullptr);
    players[0].use_card_as_property(card, animal);
}

void Game::cards_delivery() {
    deck.cards_delivery(players);
}

void Game::add_player(const Player &player_) {
    players.push_back(player_);
}

std::vector<Game::PlayerCards> Game::get_players_cards_in_hands() {
    std::vector<Game::PlayerCards> tmp(players.size());
    for (auto pl : players) {
        tmp.push_back(pl.get_cards_in_hands());
    }
    return tmp;
}
