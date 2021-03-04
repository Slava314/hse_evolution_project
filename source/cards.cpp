#include "cards.h"
std::pair<Properties::_enumerated, int> Card::get_info() {
    return {property, extra_food};
}
