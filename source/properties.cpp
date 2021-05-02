#include "properties.h"

[[maybe_unused]] std::string get_name(const int i) {
    if (i == 0)
        return "DEFAULT";
    if (i == 1)
        return "FAT TISSUE";
    if (i == 2)
        return "BIG";
    if (i == 3)
        return "STOMPER";
    return "NOT VALID";
}

[[maybe_unused]] std::string get_rus_name(const int i) {
    if (i == 0)
        return "ДЕФОЛТНЫЙ";
    if (i == 1)
        return "ЖИРОВОЙ ЗАПАС";
    if (i == 2)
        return "БОЛЬШОЙ";
    if (i == 3)
        return "ТОПОТУН";
    return "NOT VALID";
}