cmake_minimum_required(VERSION 3.14)
project(game_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-lncurses -pthread")

add_executable(game_server main.cpp Main_Window.cpp Main_Window.h Map_Window.cpp Map_Window.h Beneficial_items.cpp Beneficial_items.h Treasure.cpp Treasure.h LargeTreasure.cpp LargeTreasure.h Coins.cpp Coins.h server_pthread.cpp server_pthread.h Character.cpp Character.h Point.cpp Point.h Beast.cpp Beast.h Player.cpp Player.h initColor.cpp initColor.h setNcurses.cpp setNcurses.h commonLibray.h commonObjects.h menageOfPlayer.cpp menageOfPlayer.h LeftTreasure.cpp LeftTreasure.h Encampment.cpp Encampment.h)