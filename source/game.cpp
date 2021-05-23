#include "game.h"
#include <SFML/Graphics.hpp>
#include <utility>
#include "errors.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

using user::CreateRoomRequest;
using user::CreateRoomResponse;
using user::GetPlayerRequest;
using user::GetPlayerResponse;
using user::JoinRoomRequest;
using user::JoinRoomResponse;

using user::Error;
using user::Request;
using user::Response;
using user::Token;
using user::User;
using user::UserService;

Game::Game(const Settings &settings_, std::unique_ptr<user::UserService::Stub> stub)
    : settings(settings_) {
    if (stub_ == nullptr) {
        stub_ = user::UserService::NewStub(  // check that it is valid stub
            grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    } else {
        stub_ = std::move(stub);
    }
    phase = std::make_unique<DevelopmentPhase>(*this);
}

std::unique_ptr<Phase> const &Game::get_phase() const {
    return phase;
}

size_t Game::get_deck_size() {
    return deck.get_deck_size();
}

void Game::apply_settings() {
    deck = Deck(settings.get_seed(), settings.get_size_of_deck());
    players.resize(settings.get_total());
    deck.set_random_gen(settings.get_seed());
}

void Game::start_game() {
    apply_settings();
//    settings.set_local_player(0);
    deck.set_cards_info();

    for (int i = 0; i < settings.get_quantity_of_players(); ++i) {
        ClientContext context;
        GetPlayerRequest get_player_request;
        GetPlayerResponse get_player_response;

        get_player_request.set_player_id(i);
        get_player_request.set_room_id(settings.get_room_id());
        auto stream = stub_->GetPlayerName(&context, get_player_request, &get_player_response);
        std::string name = get_player_response.name();
        players.emplace_back(name);
        //---
        //        players.emplace_back("shershen0_" + std::to_string(i + 1) + "_player");
        //---
    }

    deck.generate_deck();
    phase = std::make_unique<DevelopmentPhase>(*this);
}

void Game::set_phase(std::unique_ptr<Phase> new_phase) {
    phase.swap(new_phase);
}

std::vector<Player> &Game::get_players() {
    return players;
}

std::vector<Game::PlayerCards> Game::get_players_cards_in_hands() {
    std::vector<Game::PlayerCards> tmp(players.size());
    for (auto pl : players) {
        tmp.push_back(pl.get_cards_in_hands());
    }
    return tmp;
}

std::vector<std::shared_ptr<Card>> Game::get_deck_cards() {
    return deck.get_deck_cards();
}

Deck &Game::get_deck() {
    return deck;
}
std::size_t Game::get_cur_player_index() const {
    return phase->get_cur_player_index();
}
Settings const &Game::get_settings() const {
    return settings;
}

void Game::create_room(const std::string &player_name_) {
    ClientContext context;
    CreateRoomRequest create_room_request;
    CreateRoomResponse create_room_response;

    create_room_request.set_player_name(player_name_);
    user::Settings settings1;


    settings1.set_quantity_of_players(settings.get_quantity_of_players());
    settings1.set_size_of_deck(settings.get_size_of_deck());
    settings1.set_time_of_move(settings.get_time_of_move());
    settings1.set_local_player(settings.get_local_player());
    settings1.set_seed(settings.get_seed());
    settings1.set_total(settings.get_total());
    //    does not have room id now - will get it from response
    *create_room_request.mutable_settings() = settings1;

    auto status = stub_->CreateRoom(&context, create_room_request, &create_room_response);

    if (!status.ok()) {
        throw GameConnecting("Could not create room, sad");
    }

    settings.set_room_id(create_room_response.id());
}

Game Game::join_room(const std::string &room_id, const std::string &player_name) {
    ClientContext context;
    JoinRoomRequest join_room_request;
    JoinRoomResponse join_room_response;

    //    join_room_request.set_room_name(&room_id);
    join_room_request.set_room_name(room_id);
    join_room_request.set_player_name(player_name);
    //    join_room_request.set_player_name(&player_name);
    auto stub_ = user::UserService::NewStub(  // check that it is valid stub
        grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    if(stub_ == nullptr){
        throw GameConnecting("Sorry, cannot join you to the room, our stub_ is nullptr");
    }

    auto status = stub_->JoinRoom(&context, join_room_request, &join_room_response);

    if (!status.ok()) {
        throw GameConnecting("Could not join room, sad");
    }

    Settings settings1{join_room_response.settings().quantity_of_players(),
                       join_room_response.settings().size_of_deck(),
                       join_room_response.settings().time_of_move(),
                       join_room_response.settings().local_player(),
                       join_room_response.settings().seed(),
                       join_room_response.settings().total(),
                       join_room_response.settings().room_id()};

    Game game(settings1, std::move(stub_));
    return game;
}
