#ifndef EVOLUTION_PROJECT_INCLUDE_PROPERTIES_H_
#define EVOLUTION_PROJECT_INCLUDE_PROPERTIES_H_

#include <string>

std::string get_name(const int i);
std::string get_rus_name(const int i);

// ENUM(Properties, DEFAULT = 0, FAT_TISSUE, BIG, STOMPER);
// ENUM(RProp, ДЕФОЛТНЫЙ = 0, ЖИРОВОЙ_ЗАПАС, БОЛЬШОЙ, ТОПОТУН);

enum Properties { DEFAULT, FAT_TISSUE, BIG, STOMPER };


#endif  // EVOLUTION_PROJECT_INCLUDE_PROPERTIES_H_