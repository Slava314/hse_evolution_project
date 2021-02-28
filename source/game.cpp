#include "game.h"
#include <algorithm>
struct FeedingPhase{};
void Game::shuffle_players(int quantity) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(players.begin(), players.end(), g);
}

void Game::delete_animal_shape() {
}

std::unique_ptr<Phase> const &Game::get_phase() const {
    return phase;
}

void Game::set_phase(std::unique_ptr<FeedingPhase> &new_phase){
    phase = std::move(dynamic_cast<Phase>(new_phase.get()));
    new_phase.reset();

}

