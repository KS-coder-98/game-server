//
// Created by root on 11/24/19.
//

#include "Coins.h"

Coins::Coins(const Map_Window &map) : Beneficial_items(map) {
    value = 1;
}

Coins::Coins(const struct game *dataGame) : Beneficial_items(dataGame) {
    value = 1;
}
