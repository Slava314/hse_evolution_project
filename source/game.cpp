#include "game.h"
#include "constants.h"

std::unique_ptr<Phase> const &Game::get_phase() const {
    return phase;
}
void Game::cards_delivery() {
    deck.cards_delivery(players);
}
std::size_t Game::get_deck_size() const {
    return deck.get_deck_size();
}
void Game::start_game() {
    // TODO set number of players
    players.resize(1);

    constexpr int N = 3;
    std::vector<std::pair<Properties, int>> cards_info(N);
    // временное решение по генерации, пока нет настроек
    cards_info[0] = {FAT_TISSUE, 8};
    cards_info[1] = {BIG, 8};
    cards_info[2] = {STOMPER, 8};
    deck.generate_deck(cards_info);
}
void Game::set_phase(std::unique_ptr<Phase> new_phase) {
    phase.swap(new_phase);
}
std::vector<Player> const &Game::get_players() const {
    return players;
}
void Game::add_animal(const std::shared_ptr<Card> &card,
                      const std::shared_ptr<Animal> &new_animal) {
    players[current_player].put_card_as_animal(card, new_animal);
}
std::size_t Game::get_current_player() const {
    return current_player;
}
void Game::add_property_to_animal(const std::shared_ptr<Card> &card,
                                  const std::shared_ptr<Animal> &animal) {
    // TODO
}
