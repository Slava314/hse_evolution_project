#ifndef EVOLUTION_PROJECT_INCLUDE_PROPERTIES_H_
#define EVOLUTION_PROJECT_INCLUDE_PROPERTIES_H_
#include <iostream>
#include <string>
#include <iostream>

std::string get_name(const int i);
std::string get_rus_name(const int i);

enum Properties {
    DEFAULT,
    FAT_TISSUE,
    BIG,
    STOMPER,
    SWIMMINGS,
    RUNNING,
    CARNIVOROUS,
    BURROWING,
    CAMOUFLAGE,
    SHARP_VISION,
    MIMICRY,
    TAIL_LOSS,
    POISONOUS,
    COMMUNICATION,
    HEBERNATION_ABILITY,
    SCAVENGER,
    SYMBIOSYS,
    PIRACY,
    COOPERATION,
    PARASITE
};

#endif  // EVOLUTION_PROJECT_INCLUDE_PROPERTIES_H_