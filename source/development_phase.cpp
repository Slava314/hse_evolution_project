#include <cassert>
#include "phase.h"
#include "player.h"
#include "view.h"

std::unique_ptr<View> DevelopmentPhase::get_view() {
    return std::make_unique<DevelopmentPhaseView>(*this);
}

void DevelopmentPhase::set_next_phase() {
    game.set_players_ended_turn(0);
    for (auto &player : game.get_players()) {
        player.set_ended_turn(false);
    }
    game.set_phase(std::make_unique<FeedingPhase>(game));
}

void DevelopmentPhase::cards_delivery() {
    if (game.get_end_game() == 1) {
        game.set_end_game(2);
        return;
    }
    game.get_deck().cards_delivery(game.get_players());
    if (game.get_deck_size() == 0) {
        game.set_end_game(1);
    }
}

bool DevelopmentPhase::is_running_first_time() const {
    return start_of_phase;
}
void DevelopmentPhase::set_start_of_phase(bool start) {
    start_of_phase = start;
}

void DevelopmentPhase::give_property_to_animal(const std::shared_ptr<Card> &card,
                                               const std::shared_ptr<Animal> &new_animal) {
    assert(card.get() != nullptr);
    assert(new_animal.get() != nullptr);
    game.get_players()[cur_player_index].use_card_as_property(card, new_animal);
}

std::vector<std::vector<std::shared_ptr<Card>>> DevelopmentPhase::get_cards() {
    return game.get_players_cards_in_hands();
}

void DevelopmentPhase::add_animal(const std::shared_ptr<Card> &card,
                                  std::shared_ptr<Animal> &new_animal) {
    assert(card.get() != nullptr);
    assert(new_animal.get() != nullptr);
    game.get_players()[cur_player_index].put_card_as_animal(card, new_animal);
}
void DevelopmentPhase::run_phase(GameWindow &window, sf::Event event) {
    // TODO check auto end turn
    if (game.get_players()[cur_player_index].get_is_bot()) {
        game.get_bot()->make_move(game);
        if (game.get_players_ended_turn() == game.get_players().size()) {
            set_next_phase();
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
                    set_next_phase();
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
DevelopmentPhase::DevelopmentPhase(Game &game_) : game(game_), cur_player_index(0) {
    end_turn.resize(game.get_players().size(), 0);
}
std::size_t DevelopmentPhase::get_cur_player_index() const {
    return cur_player_index;
}
Player &DevelopmentPhase::get_cur_player() {
    return game.get_players()[game.get_cur_player_index()];
}
std::string DevelopmentPhase::get_name() const {
    return "DevelopmentPhase";
}
