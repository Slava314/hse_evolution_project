#include "settings.h"

//std::string const &Settings::get_room_name() const {
//    return room_name;
//}
//int Settings::get_quantity_of_players() const {
//    return quantity_of_players;
//}
//int Settings::get_size_of_deck() const {
//    return size_of_deck;
//}
//int Settings::get_time_of_move() const {
//    return time_of_move;
//}
void Settings::set_local_player(int i) {
    local_player = i;
}

void Settings::set_values(std::string room_name_,
                          int quantity_of_players_,
                          int size_of_deck_,
                          int time_of_move_,
                          int local_player_) {
    room_name = room_name_;
    quantity_of_players = quantity_of_players_;
    size_of_deck = size_of_deck_;
    time_of_move = time_of_move_;
    local_player = local_player_ + 1;
}

std::string const Settings::get_room_name() const {
    return room_name;
}
int Settings::get_quantity_of_players() const {
    return quantity_of_players;
}
int Settings::get_size_of_deck() const {
    return size_of_deck;
}
int Settings::get_time_of_move()  const{
    return time_of_move;
}
int Settings::get_local_player() const {
    return local_player;
}

int Settings::get_seed() const{
    return seed;
}