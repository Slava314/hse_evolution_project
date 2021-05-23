#ifndef EVOLUTION_PROJECT_INCLUDE_GAME_H_
#define EVOLUTION_PROJECT_INCLUDE_GAME_H_
#include <grpc++/grpc++.h>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/server_context.h>
#include <memory>
#include <vector>
#include "deck.h"
#include "phase.h"
#include "player.h"
#include "server.grpc.pb.h"
#include "settings.h"

class Game {
public:
    using PlayerCards = std::vector<std::shared_ptr<Card>>;

    explicit Game(const Settings &settings_, std::unique_ptr<user::UserService::Stub> stub = nullptr);
    Game(Game &&game) = default;

    void create_room(const std::string &player_name_);
    static Game join_room(const std::string &room_id,const  std::string &player_name);
    void start_game();
    [[nodiscard]] std::unique_ptr<Phase> const &get_phase() const;
    void set_phase(std::unique_ptr<Phase> new_phase);

    std::vector<Player> &get_players();
    std::size_t get_cur_player_index() const;
    std::vector<PlayerCards> get_players_cards_in_hands();
    std::vector<std::shared_ptr<Card>> get_deck_cards();
    Deck &get_deck();
    size_t get_deck_size();
    Settings const &get_settings() const;

    std::unique_ptr<user::UserService::Stub> stub_;
private:
    Game() = default;
    void apply_settings();

private:
    Deck deck;
    Settings settings;
    std::unique_ptr<Phase> phase;
    std::vector<Player> players;
    std::string player_name;
    std::string uniq_room_id;
    //    user::UserService::Stub stub_;
};

#endif  // EVOLUTION_PROJECT_INCLUDE_GAME_H_