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

using user::Request;
using user::Response;
using user::User;
using user::UserService;

Game::Game(const Settings &settings_, std::unique_ptr<user::UserService::Stub> stub)
    : settings(settings_) {
    if (stub_ == nullptr) {
        stub_ = user::UserService::NewStub(
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
    if(stub_ != nullptr) {
        ClientContext context;
        user::Request request;
        user::TotalPlayers response;

        settings.print_all();

        // TODO - this room id does not initialize the needed field

        grpc::ClientContext context_;
        user::Request request_;
        user::TotalPlayers response_;
        request_.set_room_id(settings.get_room_id());
        auto status_ = stub_->GetTotalPlayers(&context_, request_, &response_);

        request.set_room_id(settings.get_room_id());
        auto status = stub_->GetTotalPlayers(&context, request, &response);

        if (!status.ok()) {
            throw GameConnecting("Could not get total players in apply_settings, sadly");
        }

        settings.set_total_players(response.count());
        players.resize(settings.get_total());
        settings.get_players_names().resize(0);

        /// initialize vector of players with their names
        for (int i = 0; i < players.size(); ++i) {
            ClientContext context_;
            user::GetPlayerRequest request_;
            user::GetPlayerResponse response_;
            request_.set_player_id(i);
            request_.set_room_id(settings.get_room_id());
            auto status = stub_->GetPlayerName(&context_, request_, &response_);
            if (!status.ok()) {
                throw GameError("Could not get player name from server in apply_settings, sorry\n");
            }
            players[i].set_name(response_.name());
            settings.set_name_in_players_name(response_.name());
        }
    } else {
        players.resize(settings.get_quantity_of_players());
        Settings settings_for_game;
        settings_for_game.set_seed(rand());
        settings = settings_for_game;
    }

    deck = Deck(settings.get_seed(), settings.get_size_of_deck());
    deck.set_random_gen(settings.get_seed());
}

void Game::start_game(Settings settings_) {
    settings = settings_;
    settings.set_local_player(0);
    for (int i = 0; i < settings.get_quantity_of_players(); ++i) {
        players.emplace_back(settings.get_player_name(i));
    }
    // временное решение по генерации, пока нет настроек и больше карт

    constexpr int N = 9;
    std::vector<std::pair<Properties, int>> cards_info(N);
    cards_info[0] = {Properties::FAT_TISSUE, 8};
    cards_info[1] = {Properties::BIG, 8};
    cards_info[2] = {Properties::STOMPER, 8};
    cards_info[3] = {Properties::SWIMMINGS, 8};
    cards_info[4] = {Properties::RUNNING, 8};
    cards_info[5] = {Properties::CARNIVOROUS, 8};
    cards_info[6] = {Properties::BURROWING, 8};
    cards_info[7] = {Properties::CAMOUFLAGE, 8};
    cards_info[8] = {Properties::SHARP_VISION, 8};
    deck.generate_deck(cards_info);
    deck.set_cards_info();
    deck.generate_deck();
    phase = std::make_unique<DevelopmentPhase>(*this);
}

void Game::start_game() {
    apply_settings();
    deck.set_cards_info();
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

    settings.set_seed(random() % 100'000'000);

    user::Settings settings1;

    settings1.set_quantity_of_players(settings.get_quantity_of_players());
    settings1.set_size_of_deck(settings.get_size_of_deck());
    settings1.set_time_of_move(settings.get_time_of_move());
    settings1.set_local_player(settings.get_local_player());
    settings1.set_seed(settings.get_seed());
    settings1.set_total(settings.get_total());

    *create_room_request.mutable_settings() = settings1;

    auto status = stub_->CreateRoom(&context, create_room_request, &create_room_response);

    if (!status.ok()) {
        throw GameConnecting("Could not create room, sad");
    }

    settings.set_room_id(create_room_response.id());
    settings.print_all();
}

Game Game::join_room(const std::string &room_id, const std::string &player_name) {
    ClientContext context;
    JoinRoomRequest join_room_request;
    JoinRoomResponse join_room_response;

    join_room_request.set_room_name(room_id);
    join_room_request.set_player_name(player_name);

    auto stub_ = user::UserService::NewStub(  // check that it is valid stub
        grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    if (stub_ == nullptr) {
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
    game.settings.set_room_id(room_id);
    settings1.print_all();
    return game;
}

void Game::initialize_with_settings(const Settings &settings_) {
    settings = settings_;
    if (stub_ == nullptr) {
        stub_ = user::UserService::NewStub(  // check that it is valid stub
            grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    }
    phase = std::make_unique<DevelopmentPhase>(*this);
}

std::size_t Game::get_local_player_index() const {
    return settings.get_local_player();
}
void Game::set_end_game(int i) {
    end_of_game = i;
}
int Game::get_end_game() const {
    return end_of_game;
}
