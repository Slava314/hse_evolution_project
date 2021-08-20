#ifndef EVOLUTION_PROJECT_LOG_H
#define EVOLUTION_PROJECT_LOG_H
#include <vector>
#include <string>
#include "properties.h"


struct Log {
private:
    std::vector<std::string> actions;
public:
    Log() = default;
    std::vector<std::string> get_actions() const;
    void add_action_new_animal(std::string player_name);
    void add_action_new_property(std::string player_name, Properties property);
    void add_action_feeding(std::string player_name);
    void add_action_using_property(std::string player_name, Properties property);
    void add_action_end_turn(std::string player_name);
};

#endif  // EVOLUTION_PROJECT_LOG_H
