#include "settings.h"

std::string const &Settings::get_room_name() const {
    return room_name;
}
int Settings::get_quantity_of_players() const {
    return quantity_of_players;
}
int Settings::get_size_of_deck() const {
    return size_of_deck;
}
int Settings::get_time_of_move() const {
    return time_of_move;
}
void Settings::set_local_player(int i) {
    local_player = i;
}
void Settings::set_player_name(const std::string &name, std::size_t ind) {
    players_names[ind] = name;
}
const std::string &Settings::get_player_name(std::size_t ind) const {
    return players_names[ind];
}
std::size_t Settings::get_local_player() const {
    return local_player;
}
