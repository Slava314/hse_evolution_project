#ifndef EVOLUTION_PROJECT_INCLUDE_SETTINGS_H_
#define EVOLUTION_PROJECT_INCLUDE_SETTINGS_H_

#include <string>
#include <vector>

class Settings {
public:

    Settings() = default;

    //TODO - resize player_names with valid quantity
    // constructor for window_settings
    Settings(const std::string &room_name_,
             const int &quantity_of_players_,
             const int &quantity_of_bots_,
             const int &size_deck_,
             const int &time_)
        : quantity_of_players(quantity_of_players_), quantity_of_bots(quantity_of_bots_), size_of_deck(size_deck_), time_of_move(time_), seed(random()), total_players(1) {
        players_names.resize(quantity_of_players);
    }

    Settings(int quantity_of_players_,
             int size_deck_,
             int time_,
             int local_,
             int seed_,
             int total_,
             std::string room_id_)
        : quantity_of_players(quantity_of_players_),
          size_of_deck(size_deck_),
          time_of_move(time_),
          local_player(local_),
          seed(std::move(seed_)),
          total_players(total_),
          room_id(room_id_) {
    }

    int get_quantity_of_players() const;
    int get_quantity_of_bots() const;
    int get_size_of_deck() const;
    int get_time_of_move() const;
    int get_local_player() const;
    int get_seed() const;
    int get_total() const;
    std::string get_room_id() const;
    std::vector<std::string> &get_players_names();

    void set_player_name(const std::string &name, std::size_t ind);
    const std::string &get_player_name(std::size_t ind) const;
    void set_name_in_players_name(const std::string &str);
    void set_room_id(const std::string &id);
    void set_total_players(int count);
    void set_seed(int rand);
    void set_local_player(int i);

    void print_all() const;
private:
    int quantity_of_players;
    int quantity_of_bots;
    int size_of_deck;
    int time_of_move;
    int local_player = 0;
    int seed = rand();
    int total_players;
    std::vector<std::string> players_names;
    std::string room_id;
};

#endif  // EVOLUTION_PROJECT_INCLUDE_SETTINGS_H_
