#include "game.h"
#include <SFML/Graphics.hpp>
#include <utility>

Game::Game(Settings settings_) : settings(settings_) {
    phase = std::make_unique<DevelopmentPhase>(*this);
}

Game::Game() {
    phase = std::make_unique<DevelopmentPhase>(*this);
}

std::unique_ptr<Phase> const &Game::get_phase() const {
    return phase;
}

size_t Game::get_deck_size() {
    return deck.get_deck_size();
}

void Game::start_game(Settings settings_) {
    settings = settings_;
    // TODO set number of players

    // TODO - get count of players as a parametr. From GUI? or lobby?
    //    players.resize(1);

    // TODO - cycle where player will add to vector
    // TODO -

    // TODO - ask server about players count and get stream of messages about their names and
    // position
    //    int total_players = get_all_players();
    int i = 0;
    players.emplace_back("shershen0_first_player", 0);
    players.emplace_back("shershen0_second_player", 1);
    // временное решение по генерации, пока нет настроек и больше карт
    constexpr int N = 3;
    std::vector<std::pair<Properties, int>> cards_info(N);
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

std::vector<Game::PlayerCards> Game::get_players_cards_in_hands() {
    std::vector<Game::PlayerCards> tmp(players.size());
    for (auto pl : players) {
        tmp.push_back(pl.get_cards_in_hands());
    }
    return tmp;
}

std::vector<std::shared_ptr<Card>> Game::get_deck_cards() {
    return deck.get_deck_cards();
}

Deck &Game::get_deck() {
    return deck;
}
std::size_t Game::get_cur_player() const {
    return phase->get_cur_player();
}
Settings const &Game::get_settings() const {
    return settings;
}
