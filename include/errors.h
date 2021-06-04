#ifndef EVOLUTION_PROJECT_INCLUDE_ERRORS_H_
#define EVOLUTION_PROJECT_INCLUDE_ERRORS_H_

#include <string>

struct GameError : public std::runtime_error{
    explicit GameError(const std::string &str) : std::runtime_error(str){

    }
};


struct GameConnecting : GameError{
    explicit GameConnecting(const std::string &str) : GameError(str){

    }
};


#endif  // EVOLUTION_PROJECT_INCLUDE_ERRORS_H_
