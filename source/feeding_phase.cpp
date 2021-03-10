#include <cassert>
#include "phase.h"
#include "phase_fwd.h"
#include "player.h"
#include "view.h"

std::unique_ptr<View> FeedingPhase::get_view() {
    return std::make_unique<FeedingPhaseView>(*this);
}

void FeedingPhase::set_next_phase() {
    game.set_phase(std::make_unique<DevelopmentPhase>(game));
}

FeedingPhase::FeedingPhase(Game &game_)
    : game(game_), food_balance(define_food_balance()), cur_player(0) {
    end_turn.resize(2, 0);
}

size_t FeedingPhase::define_food_balance() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(MIN_FOOD_BALANCE, MAX_FOOD_BALANCE);
    return distrib(gen);
}

void FeedingPhase::feed_animal(std::shared_ptr<Animal> animal) {
    assert(animal != nullptr);
    decrease_food_balance();
    animal->increase_owning_food();
}

void FeedingPhase::decrease_food_balance() {
    if (food_balance == 0) {
        throw std::logic_error("CANNOT DECREASE FOOD BALANCE");
    } else {
        --food_balance;
    }
}

bool FeedingPhase::is_end_of_phase() const {
    return food_balance == 0;
}

void FeedingPhase::kill_animals() {
    for (auto &player : game.get_players()) {
        for (int i = 0; i < player.get_animals_on_board().size(); ++i) {
            if (player.get_animals_on_board()[i]->is_hungry()) {
                player.handle_animal_death(player.get_animals_on_board()[i]);
                i--;
            } else {
                player.get_animals_on_board()[i]->set_owning_food(0);
            }
        }
    }
}

size_t FeedingPhase::get_food_balance() const {
    return food_balance;
}
bool FeedingPhase::is_running_first_time() const {
    return start_of_phase;
}
void FeedingPhase::set_start_of_phase(bool start) {
    start_of_phase = start;
}
void FeedingPhase::run_phase(GameWindow &window, sf::Event event) {
    //TODO check auto end turn
    int ans = get_view()->handle_event(window, event);
    if (ans != 0) {
        if (ans == 2) {
            end_turn[cur_player] = 1;
            sum += 1;
            if (sum == game.get_players().size()) {
                kill_animals();
                window.kill_animals();
                set_next_phase();
                return;
            }
        }
        cur_player = (cur_player + 1) % game.get_players().size();
        while (end_turn[cur_player] == 1) {
            cur_player = (cur_player + 1) % game.get_players().size();
        }
        window.change_player();
    }
}
std::size_t FeedingPhase::get_cur_player() const {
    return cur_player;
}
