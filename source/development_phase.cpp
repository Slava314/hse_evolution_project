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
    if (game.get_end_game() == 1) {
        game.set_end_game(2);
        return;
    }
    game.get_deck().cards_delivery(game.get_players());
    if (game.get_deck_size() == 0) {
        game.set_end_game(1);
    }
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

void DevelopmentPhase::add_animal(const std::shared_ptr<Card> &card = nullptr,
                                  const std::shared_ptr<Animal> &new_animal = nullptr) {
    //    assert(card.get() != nullptr);
    //    assert(new_animal.get() != nullptr);

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
        std::cout << "CAME TO ADD_ANIMAL() to another players --------------------- \n";

        grpc::ClientContext context;

        std::chrono::time_point deadline =
            std::chrono::system_clock::now() + std::chrono::milliseconds(3000);
        context.set_deadline(deadline);

        grpc::Status status = grpc::Status::CANCELLED;

        while (!status.ok()) {
            user::Request request;
            user::Action response;
            auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(INTERVAL);
            status = game.stub_->GetDataAboutMove(&context, request, &response);
            if (status.ok() == 1) {
                std::cout << "getting message from server in add_animal() = " << response.player_id()
                          << std::endl;
                int player = response.player_id();
                std::shared_ptr<Animal> animal;
                game.get_players()[player].put_card_as_animal(animal);
                break;
            } else {
                std::this_thread::sleep_until(x);
                continue;
            }
        }
        std::cout << "LEFT TO ADD_ANIMAL() to another animal --------------------- \n";
    }
}

//void DevelopmentPhase::add_animal() {
//    std::cout << "CAME TO ADD_ANIMAL() --------------------- \n";
//
//    grpc::ClientContext context;
//
//    std::chrono::time_point deadline =
//        std::chrono::system_clock::now() + std::chrono::milliseconds(3000);
//    context.set_deadline(deadline);
//
//    grpc::Status status = grpc::Status::CANCELLED;
//
//    while (!status.ok()) {
//        user::Request request;
//        user::Action response;
//        auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(INTERVAL);
//        status = game.stub_->GetDataAboutMove(&context, request, &response);
//        if (status.ok() == 1) {
//            std::cout << "getting message from server in add_animal() = " << response.player_id()
//                      << std::endl;
//            int player = response.player_id();
//            std::shared_ptr<Animal> animal;
//            game.get_players()[player].put_card_as_animal(animal);
//            break;
//        } else {
//            std::this_thread::sleep_until(x);
//            continue;
//        }
//    }
//    std::cout << "LEFT TO ADD_ANIMAL() --------------------- \n";
//}

// TODO TODO TODO TODO TODO TODO TODO
void DevelopmentPhase::parse_message(const std::string &str) {
    const std::string add_card("Player added new card on the board");
    if (str.compare(add_card) == true) {
        //вызвать нужную функцию, которая обратится к серверу и отрисует нужную карту
        add_animal();  //сам разберется кто?
        std::cout << "GETTIN MESSAGE FROM PARSE = " << add_card << std::endl;
    }
}
void DevelopmentPhase::run_phase(GameWindow &window, sf::Event event) {
    // TODO check auto end turn

    // TODO - придется парсить сообщение - какое действие нужно выполнить
    // he cant make any moves - should skip him


    static int ans = -1;
    auto f = [&]() { ans = get_view()->handle_event(window, event); };
    std::thread thread(f);
    while (ans == -1) {
        std::cout << ans;
        std::thread(f);
    }
    thread.join();

    std::cout << "game.get_cur_player_index() = " << game.get_cur_player_index() << std::endl;
    std::cout << "game.get_settings().get_local_player() = "
              << game.get_settings().get_local_player() << std::endl;

//    if (game.get_cur_player_index() != game.get_settings().get_local_player()) {
//        grpc::Status status = grpc::Status::CANCELLED;
//        std::string message_from_server;
//        auto end_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(30000ms);
//
//        while (!status.ok()) {
//            std::cout << "SENDING REQ TO SERVER\n";
//            auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(30ms);
//            grpc::ClientContext context;
//            user::Nothing request;
//            user::Message response;
//            status = game.stub_->GetMessage(&context, request, &response);
//            if (status.ok() and std::chrono::steady_clock::now() < end_time) {
//                std::cout << "I GOT A MESSAGE AND GETTING OUT OF RUN PHASE = " << response.str()
//                          << std::endl;
//                message_from_server = response.str();
//                break;
//            } else {
//                std::cout << status.error_message() << std::endl;
//                std::this_thread::sleep_until(x);
//            }
//        }
//        std::cout << "I AM NEXT TO PARSE-------------------------\n";
//        parse_message(message_from_server);  // will call the right function for each message
//                                             // (player's action)
//    }

    //has others read the message
    if (game.get_deck_size() == 0 and get_cur_player().get_cards_in_hands().size() == 0) {
        ans = 2;
    }

    // TODO - обработать пропуск хода и всего такого

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

DevelopmentPhase::DevelopmentPhase(::Game &game_) : game(game_), cur_player_index(0) {
    end_turn.resize(game.get_players().size(), 0);
}
std::size_t DevelopmentPhase::get_cur_player_index() const {
    return cur_player_index;
}
Player &DevelopmentPhase::get_cur_player() {
    return game.get_players()[game.get_cur_player_index()];
}
 Game const &DevelopmentPhase::get_game() {
    return game;
}
