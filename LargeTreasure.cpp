//
// Created by root on 11/24/19.
//

#include "LargeTreasure.h"

LargeTreasure::LargeTreasure(const Map_Window &map) : Beneficial_items(map) {
    value = 50;
}

LargeTreasure::LargeTreasure(const struct game *dataGame) : Beneficial_items(dataGame) {
    value = 50;
}
