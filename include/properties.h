#ifndef EVOLUTION_PROJECT_INCLUDE_PROPERTIES_H_
#define EVOLUTION_PROJECT_INCLUDE_PROPERTIES_H_

#include <string>
#include <iostream>

std::string get_name(const int i);
std::string get_rus_name(const int i);

// ENUM(Properties, DEFAULT = 0, FAT_TISSUE, BIG, STOMPER);
// ENUM(RProp, ДЕФОЛТНЫЙ = 0, ЖИРОВОЙ_ЗАПАС, БОЛЬШОЙ, ТОПОТУН);

enum Properties {
    DEFAULT,
    FAT_TISSUE,
    BIG,
    STOMPER,
    SWIMMINGS,
    RUNNING,
    MIMICRY,
    POISONOUS,
    TAIL_LOSS,
    COMMUNICATION,
    HEBERNATION_ABILITY,
    SCAVENGER,
    SYMBIOSYS,
    PIRACY,
    COOPERATION,
    BURROWING,
    CAMOUFLAGE,
    SHARP_VISION,
    PARASITE
};

#endif  // EVOLUTION_PROJECT_INCLUDE_PROPERTIES_H_