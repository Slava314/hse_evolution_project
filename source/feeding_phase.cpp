#include <cassert>
#include "phase.h"
#include "player.h"
#include "view.h"

std::unique_ptr<View> FeedingPhase::get_view() {
    return std::make_unique<FeedingPhaseView>(*this);
}

void FeedingPhase::set_next_phase() {
    game.set_players_ended_turn(0);
    for (auto &player : game.get_players()) {
        player.set_ended_turn(false);
    }
    game.set_phase(std::make_unique<DevelopmentPhase>(game));
}

FeedingPhase::FeedingPhase(Game &game_)
    : game(game_), food_balance(define_food_balance()), cur_player_index(0) {
    end_turn.resize(game.get_players().size(), 0);
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

void FeedingPhase::attack(std::shared_ptr<Animal> attacker, std::shared_ptr<Animal> victim) {
    if (attacker->can_use_property(Properties::CARNIVOROUS)) {
        if (victim->get_properties().find(Properties::RUNNING) != victim->get_properties().end()) {
            int dice = rand() % 6 + 1;
            if (dice <= 3) {
                return;
            }
        }
        if (victim->could_be_attacked(attacker)) {
            attacker->increase_owning_food();
            attacker->increase_owning_food();
            victim->get_owner().handle_animal_death(victim);
            attacker->set_property_is_used(Properties::CARNIVOROUS, true);
        }
    } else {
        throw std::logic_error("THIS ANIMAL HAD ALREADY ATTACKED IN THIS PHASE");
    }
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
    // TODO check auto end turn
    if (game.get_players()[cur_player_index].get_is_bot()) {
        game.get_bot()->make_move(game);
        if (game.get_players_ended_turn() == game.get_players().size()) {
            kill_animals();
            set_next_phase();
            window.recalc_animals();
            return;
        }
        cur_player_index = (cur_player_index + 1) % game.get_players().size();
        while (game.get_players()[cur_player_index].get_ended_turn()) {
            cur_player_index = (cur_player_index + 1) % game.get_players().size();
        }
        window.change_player();
    } else {
        int ans = get_view()->handle_event(window, event);
        if (ans != 0) {
            if (ans == 2) {
                game.get_players()[cur_player_index].set_ended_turn(true);
                game.set_players_ended_turn(game.get_players_ended_turn() + 1);
                if (game.get_players_ended_turn() == game.get_players().size()) {
                    kill_animals();
                    set_next_phase();
                    window.recalc_animals();
                    return;
                }
            }
            cur_player_index = (cur_player_index + 1) % game.get_players().size();
            while (game.get_players()[cur_player_index].get_ended_turn()) {
                cur_player_index = (cur_player_index + 1) % game.get_players().size();
            }
            window.change_player();
        }
    }
}
std::size_t FeedingPhase::get_cur_player_index() const {
    return cur_player_index;
}

std::string FeedingPhase::get_name() const {
    return "FeedingPhase";
Game const& FeedingPhase::get_game() {
    return game;
}
