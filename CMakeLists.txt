cmake_minimum_required(VERSION 3.27)
project(MiniMetro)

set(CMAKE_CXX_STANDARD 17)

add_executable(MiniMetro main.cpp
        display.cpp
        display.h
        utils.cpp
        utils.h
        navigation.cpp
        navigation.h
        station.h
        station.cpp)