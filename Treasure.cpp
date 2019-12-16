//
// Created by root on 11/24/19.
//

#include "Treasure.h"

Treasure::Treasure(const Map_Window &map) : Beneficial_items(map) {
    value = 10;
}

Treasure::Treasure(const struct game *dataGame) : Beneficial_items(dataGame) {
    value = 10;
}
