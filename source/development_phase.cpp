#include <cassert>
#include "phase.h"
#include "player.h"
#include "view.h"

std::unique_ptr<View> DevelopmentPhase::get_view() {
    return std::make_unique<DevelopmentPhaseView>(*this);
}

void DevelopmentPhase::set_next_phase() {
    game.set_phase(std::make_unique<FeedingPhase>(game));
}

void DevelopmentPhase::cards_delivery() {
    game.get_deck().cards_delivery(game.get_players());
}

// void DevelopmentPhase::cards_delivery() {
////        game.get_deck().cards_delivery(game.get_players());
//    //    grpc::ClientContext context;
//    //    user::GiveCardFromDeck give_card_from_deck;
//    //    user::Nothing nothing;
//    //    game.stub_->GiveCardFDeck(&context, give_card_from_deck, &nothing);
//    //
//    //    for (int i = 0; i < game.get_players().size(); ++i) {
//    //        auto player = game.get_players()[i];
//    //        int needed = game.get_deck().need_card(player);
//    //        give_card_from_deck.set_quantity(needed);
//    //
//    give_card_from_deck.mutable_player_and_room()->set_player_id(game.get_settings().get_local_player());
//    //
//    give_card_from_deck.mutable_player_and_room()->set_room_id(game.get_settings().get_room_id());
//    //        game.stub_->GiveCardFDeck(&context, give_card_from_deck, &nothing);
//    //
//    //    }
//    for (int i = 0; i < game.get_players().size(); i++) {
//        std::cout << "-----------------------" << std::endl;
//
//        std::cout << "GAME & in phase    " << &game << std::endl;
//        std::cout << "get-players PHASE  ---- " << &game.get_players() << std::endl;
//        std::cout << std::endl;
//
//        std::cout << "player eq = " << i << std::endl;
//
//        auto player = game.get_players()[i];
//        std::cout << "player address IN PHASE " << &player << std::endl;
//        if (i == game.get_settings().get_local_player()) {
//            game.get_deck().cards_delivery(player);
//            std::cout << std::endl;
//        } else {
//            int need = game.get_deck().need_card(player);
//            while (need--) {
//                game.get_deck().get_deck_cards().pop_back();
//            }
//        }
//        std::cout << "owning cards = " << player.get_cards_in_hands().size() << std::endl;
//        std::cout << "||||||||||||||||||||||||" << std::endl;
//
//    }
//
//}

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

void DevelopmentPhase::add_animal(const std::shared_ptr<Card> &card,
                                  std::shared_ptr<Animal> &new_animal) {
    //    assert(card.get() != nullptr);
    //    assert(new_animal.get() != nullptr);

    grpc::ClientContext context;

    std::chrono::time_point deadline =
        std::chrono::system_clock::now() + std::chrono::milliseconds(300);
    context.set_deadline(deadline);

    /// his turn to make move
    if (auto cur_player = game.get_cur_player_index();
        cur_player == game.get_settings().get_local_player()) {
        user::PlayAsAnimalAction request;
        user::PlayAsAnimalAction response;

        request.set_player(cur_player);
        auto status = game.stub_->AddCardOnTheBoard(&context, request, &response);
        if (status.ok()) {
            /// evrth is good, make move, make a little ping, to wait for
            /// other player's to ask server
            game.get_players()[cur_player].put_card_as_animal(card, new_animal);
            std::this_thread::sleep_for(250ms);
        } else {
            // throw something?
        }
    } else {
        /// ask server to get_message and update other player's animals on the board and then
        /// redraw them
        grpc::Status status = grpc::Status::CANCELLED;
        while (!status.ok()) {
            user::Nothing nothing;
            user::Action action;
            auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(INTERVAL);
            status = game.stub_->GetDataAboutMove(&context, nothing, &action);
            if (status.ok() == 1) {
                int player = action.player_id();
                auto l = action.mutable_play_animal();
                std::shared_ptr<Animal> animal;
                game.get_players()[l->player()].put_card_as_animal(animal);
                break;
            } else {
                std::this_thread::sleep_until(x);
                continue;
            }
        }
    }
}

void DevelopmentPhase::add_animal() {
    /*
     * если ход мой - делаю ход и говорю серверу - вот сделался новый ход
     * иначе - беру запрос от сервера и смотрю - кто походил и отрисовываю его уже
     */

//    if(game.get_cur_player_index() == )
    grpc::ClientContext context;

    std::chrono::time_point deadline =
        std::chrono::system_clock::now() + std::chrono::milliseconds(300);
    context.set_deadline(deadline);

    grpc::Status status = grpc::Status::CANCELLED;

    while (!status.ok()) {
        user::Nothing nothing;
        user::Action action;
        auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(INTERVAL);
        status = game.stub_->GetDataAboutMove(&context, nothing, &action);
        if (status.ok() == 1) {
            int player = action.player_id();
            auto l = action.mutable_play_animal();
            std::shared_ptr<Animal> animal;
            game.get_players()[l->player()].put_card_as_animal(animal);
            break;
        } else {
            std::this_thread::sleep_until(x);
            continue;
        }
    }
}


void DevelopmentPhase::parse_message(const std::string &str)  {
    const std::string add_card("Player added new card on the board");
    if(str.compare(add_card) == true){
        //вызвать нужную функцию, которая обратится к серверу и отрисует нужную карту
       add_animal(); //сам разберется кто?
    }
}
void DevelopmentPhase::run_phase(GameWindow &window, sf::Event event) {
//    grpc::ClientContext context;
//    user::Request request;
//    user::TotalPlayers response;
//    request.set_room_id(game.get_settings().get_room_id());
//    game.stub_->GetTotalPlayers(&context, request, &response);

    // TODO check auto end turn

    // TODO - придется парсить сообщение - какое действие нужно выполнить
    // he cant make any moves - should skip him

    int ans = get_view()->handle_event(window, event);

    //todo - ask server - is it my turn - if yes - make move and tell server, else ask for other's players move

    if (game.get_cur_player_index() != game.get_settings().get_local_player()) {
        /// ask server to get_message and update other player's animals on the board and then
        /// redraw them
        grpc::ClientContext context;
        grpc::Status status = grpc::Status::CANCELLED;
        std::string message_from_server;
        while (!status.ok()) {
            user::Nothing request;
            user::Message response;
            auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(INTERVAL);
            status = game.stub_->GetMessage(&context, request, &response);
            if (status.ok() == 1) {
                message_from_server = response.str();
                break;
            } else {
                std::this_thread::sleep_until(x);
                continue;
            }
        }
        parse_message(message_from_server); //will call the right function for each message (player's action)
    }

    if (game.get_deck_size() == 0 and get_cur_player().get_cards_in_hands().size() == 0) {
        ans = 2;
    }

    //TODO - обработать пропуск хода и всего такого

    if (ans != 0) {
        if (ans == 2) {
            end_turn[cur_player_index] = 1;
            sum += 1;
            if (sum == game.get_players().size()) {
                set_next_phase();
                return;
            }
        }
        cur_player_index = (cur_player_index + 1) % game.get_players().size();
        while (end_turn[cur_player_index] == 1) {
            cur_player_index = (cur_player_index + 1) % game.get_players().size();
        }
        window.change_player();
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
