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
    // TODO - ask умеет ли гуй понимать, что другой пользователь надал именно на эту кнопку
    // answer - no
    assert(card.get() != nullptr);
    assert(new_animal.get() != nullptr);

    grpc::ClientContext context;
    user::AddCardOnTheBoardR request;
    user::AddCardOnTheBoardR response;
    std::chrono::time_point deadline = std::chrono::system_clock::now() +
        std::chrono::milliseconds(300);
    context.set_deadline(deadline);
    grpc::Status status;
    while (true) {
        auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(INTERVAL);
        status = game.stub_->AddCardOnTheBoard(&context, request, &response);
        if (status.ok() == 1) {
            break;
        }
        std::this_thread::sleep_until(x);
    }

    int player = response.player();

    //выкладывать карту на поле у конкретного игрока, если она у другого игрока
    //иначе добавить карту к себе
    if (player == cur_player_index) {
        game.get_players()[player].put_card_as_animal(card, new_animal);
    } else {
        //выкладывать карту на поле у конкретного игрока, если она у другого игрока
        game.get_players()[player].put_card_as_animal(new_animal);
    }
}

void DevelopmentPhase::run_phase(GameWindow &window, sf::Event event) {
    // TODO check auto end turn

    // he cant make any moves - should skip him

    int ans = get_view()->handle_event(window, event);
    if (game.get_deck_size() == 0 and get_cur_player().get_cards_in_hands().size() == 0) {
        ans = 2;
    }
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
