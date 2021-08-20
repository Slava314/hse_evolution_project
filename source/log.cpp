#include "log.h"

std::vector<std::string> Log::get_actions() const {
    return actions;
}

void Log::add_action_new_animal(std::string player_name) {
    actions.push_back(player_name + " added new animal");
}

void Log::add_action_new_property(std::string player_name, Properties property) {
    actions.push_back(player_name + " added property " + get_name(property));
}

void Log::add_action_feeding(std::string player_name) {
    actions.push_back(player_name + " fed animal");
}

void Log::add_action_using_property(std::string player_name, Properties property) {
    actions.push_back(player_name + " used property " + get_name(property));
}

void Log::add_action_end_turn(std::string player_name) {
    actions.push_back(player_name + " ended turn");
}