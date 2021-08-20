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

// TODO  делается дейтсвие, при этом гуй не знает какой игрок - для этого передается сообщенеи что
// именно произшло и какую функцию вызывать от каког игрока

void DevelopmentPhase::add_animal(const std::shared_ptr<Card> &card = nullptr,
                                  const std::shared_ptr<Animal> &new_animal = nullptr) {
    if (game.stub_ != nullptr) {
        if (card != nullptr and new_animal != nullptr) {
            grpc::ClientContext context;

            std::chrono::time_point deadline =
                std::chrono::system_clock::now() + std::chrono::milliseconds(30000);
            context.set_deadline(deadline);

            /// his turn to make move
            if (auto cur_player = game.get_cur_player_index();
                cur_player == game.get_settings().get_local_player()) {
                user::PlayAsAnimalAction request;
                user::PlayAsAnimalAction response;

                request.set_room_id(game.get_settings().get_room_id());
                request.set_player(cur_player);
                request.set_message("Player added new card on the board");

                auto status = game.stub_->AddCardOnTheBoard(&context, request, &response);
                if (status.ok()) {
                    /// evrth is good, make move, make a little ping, to wait for
                    /// other player's to ask server
                    game.get_players()[cur_player].put_card_as_animal(card, new_animal);
                    std::this_thread::sleep_for(250ms);
                } else {
                    // todo throw something?
                }
            }
        } else {
            grpc::Status status = grpc::Status::CANCELLED;
            while (!status.ok()) {
                grpc::ClientContext context;
                std::chrono::time_point deadline =
                    std::chrono::system_clock::now() + std::chrono::milliseconds(30000);
                context.set_deadline(deadline);
                user::Request request;
                user::Action response;

                auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(INTERVAL);
                status = game.stub_->GetDataAboutMove(&context, request, &response);
                if (status.ok() == 1) {
                    int player = response.player_id();
                    //                    std::shared_ptr<Animal>
                    //                    animal(game.get_players()[player]);
                    game.get_players()[player].put_card_as_animal(
                        std::make_shared<Animal>(game.get_players()[player]));
                    break;
                } else {
                    std::this_thread::sleep_until(x);
                    continue;
                }
            }
        }
    } else {
        assert(card.get() != nullptr);
        assert(new_animal.get() != nullptr);
        game.get_players()[cur_player_index].put_card_as_animal(card, new_animal);
    }
}

void DevelopmentPhase::parse_message(const std::string &str) {
    const std::string add_card("Player added new card on the board");
    if (str.compare(add_card) == true) {
        //вызвать нужную функцию, которая обратится к серверу и отрисует нужную карту
        add_animal();  //сам разберется кто?
    }
}

void DevelopmentPhase::run_phase(GameWindow &window, sf::Event event) {
    static int ans = -1;

    ans = get_view()->handle_event(window, event);
    if (game.stub_ != nullptr and ans == -1) {
        return;
    }

    if (game.stub_ != nullptr) {
        grpc::ClientContext context;
        user::Nothing request;
        user::Nothing response;
        request.set_player_id(game.get_local_player_index());
        auto status = game.stub_->AllPlayersGotMessage(&context, request, &response);

        if (!status.ok()) {
            return;
        }
    }

    if (game.get_deck_size() == 0 and get_cur_player().get_cards_in_hands().size() == 0) {
        ans = 2;
    }

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

DevelopmentPhase::DevelopmentPhase(::Game &game_) : game(game_), cur_player_index(0) {
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
 Game const &DevelopmentPhase::get_game() {
    return game;
}
