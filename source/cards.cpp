//
// Created by Андрей Шеремеев on 03.03.2021.
//
#include "cards.h"
std::pair<Properties, int> Card::get_info() {
    return {property, extra_food};
}
