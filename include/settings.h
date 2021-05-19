#ifndef EVOLUTION_PROJECT_INCLUDE_SETTINGS_H_
#define EVOLUTION_PROJECT_INCLUDE_SETTINGS_H_

#include <string>

struct Settings {
    void set_local_player(int i);

public:
    Settings() = default;
    Settings(std::string room_name_, int quantity_of_players_, int size_of_deck_, int time_of_move_)
        : room_name(std::move(room_name_)),
          quantity_of_players(quantity_of_players_),
          size_of_deck(size_of_deck_),
          time_of_move(time_of_move_) {
    }

    Settings(std::string room_name_,
             int quantity_of_players_,
             int size_of_deck_,
             int time_of_move_,
             int local_player_)
        : room_name(std::move(room_name_)),
          quantity_of_players(quantity_of_players_),
          size_of_deck(size_of_deck_),
          time_of_move(time_of_move_),
          local_player(local_player_) {
    }

    void set_values(std::string room_name_,
                    int quantity_of_players_,
                    int size_of_deck_,
                    int time_of_move_,
                    int local_player_);

    const std::string get_room_name() const;
    int get_quantity_of_players() const;
    int get_size_of_deck() const;
    int get_time_of_move() const;
    int get_local_player() const;
    int get_seed() const;

private:
    std::string room_name;
    int quantity_of_players;
    int size_of_deck;
    int time_of_move;
    int local_player = 0;
    int seed = 0;
};

#endif  // EVOLUTION_PROJECT_INCLUDE_SETTINGS_H_
