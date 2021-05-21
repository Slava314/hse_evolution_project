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

//void Settings::set_values(int quantity_of_players_,
//                          int size_of_deck_,
//                          int time_of_move_,
//                          int local_player_) {
//    quantity_of_players = quantity_of_players_;
//    size_of_deck = size_of_deck_;
//    time_of_move = time_of_move_;
//    local_player = local_player_ + 1;
//}


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
int Settings::get_total() const {
    return total_players;
}
std::string Settings::get_room_id() const {
    return room_id;
}

void Settings::set_room_id(const std::string &id) {
    room_id = id;
}
