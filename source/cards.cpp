#include "cards.h"
std::pair<Properties, int> Card::get_info() {
    return {property, extra_food};
}
