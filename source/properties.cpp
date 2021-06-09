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
    if (i == 4)
        return "SWIMMINGS";
    if (i == 5)
        return "RUNNING";
    if (i == 6)
        return "CARNIVOROUS";
    if (i == 7)
        return "BURROWING";
    if (i == 8)
        return "CAMOUFLAGE";
    if (i == 9)
        return "SHARP_VISION";
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