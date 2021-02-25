#include "game.h"
#include <SFML/Graphics.hpp>
#include "constants.h"

std::unique_ptr<Phase> Game::get_phase() const {
    return std::unique_ptr<Phase>();
}
void Game::cards_delivery() {
    deck.cards_delivery(players);
}
std::size_t Game::get_deck_size() {
    return deck.get_deck_size();
}
void Game::start_game() {
    // TODO set number of players
    players.resize(1);

    constexpr int N = 3;
    std::vector<std::pair<Properties, int>> cards_info(N);
    // временное решение по генерации, пока нет настроек
    cards_info[0] = {FAT_TISSUE, 8};
    cards_info[1] = {BIG , 8};
    cards_info[2] = {STOMPER, 8};
    deck.generate_deck(cards_info);
}
