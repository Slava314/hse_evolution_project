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
#include "bot.h"
#include "deck.h"
#include "phase.h"
#include "player.h"
#include "server.grpc.pb.h"
#include "settings.h"
#include "log.h"

class Game {
public:
    using PlayerCards = std::vector<std::shared_ptr<Card>>;

    explicit Game(const Settings &settings_,
                  std::unique_ptr<user::UserService::Stub> stub = nullptr);
    Game(Game &&game) = default;
    Game() = default;

    void initialize_with_settings(const Settings &settings);

    void create_room(const std::string &player_name_);
    static Game join_room(const std::string &room_id, const std::string &player_name);
    void start_game();
    void start_game(Settings settings_);
    [[nodiscard]] std::unique_ptr<Phase> const &get_phase() const;
    void set_phase(std::unique_ptr<Phase> new_phase);

    std::vector<Player> &get_players();
    std::size_t get_cur_player_index() const;
    std::vector<PlayerCards> get_players_cards_in_hands();
    std::vector<std::shared_ptr<Card>> get_deck_cards();
    Deck &get_deck();
    size_t get_deck_size();
    Settings const &get_settings() const;
    std::size_t get_local_player_index() const;
    void set_end_game(int i);
    int get_end_game() const;
    void set_players_ended_turn(int value);
    int get_players_ended_turn() const;
    std::unique_ptr<Bot> const &get_bot() const;
    std::unique_ptr<Log> const &get_log() const;

    bool send_request_to_server(std::function<bool(void)> func, unsigned int interval);

    std::unique_ptr<user::UserService::Stub> stub_ = nullptr;
    //    Game() = default;
private:
    void apply_settings();
    Deck deck;
    Settings settings;
    std::unique_ptr<Phase> phase;
    std::vector<Player> players;
    std::string player_name;
    std::string uniq_room_id;
    //    user::UserService::Stub stub_;
    int end_of_game = 0;
    int players_ended_turn = 0;
    std::unique_ptr<Bot> bot = std::make_unique<Bot>();
    std::unique_ptr<Log> log = std::make_unique<Log>();
};

#endif  // EVOLUTION_PROJECT_INCLUDE_GAME_H_