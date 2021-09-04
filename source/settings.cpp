#include "settings.h"
#include <iostream>

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

void Settings::print_all()const {
    std::cout << "----------------print all ------------------\n";
    std::cout << "quantity of players = " << quantity_of_players <<std::endl;
    std::cout << "size_of_deck = " << size_of_deck <<std::endl;
    std::cout << "time of move = " << time_of_move <<std::endl;
    std::cout << "local_player = " << local_player <<std::endl;
    std::cout << "seed = " << seed <<std::endl;
    std::cout << "total = " << total_players << std::endl;
    std::cout << "room id = " << room_id << std::endl;
    std::cout << "----------------print all ------------------\n";

}

int Settings::get_quantity_of_players() const {
    return quantity_of_players;
}
int Settings::get_quantity_of_bots() const {
    return quantity_of_bots;
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
void Settings::set_player_name(const std::string &name, std::size_t ind) {
    players_names[ind] = name;
}
void Settings::set_name_in_players_name(const std::string &str){
    players_names.push_back(str);
}
const std::string &Settings::get_player_name(std::size_t ind) const {
    return players_names[ind];
}

void Settings::set_total_players(int count) {
    total_players = count;
}

std::vector<std::string> &Settings::get_players_names(){
    return players_names;
}

void Settings::set_seed(int rand) {
    seed = rand;
}
