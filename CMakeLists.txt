cmake_minimum_required(VERSION 3.27)
project(MiniMetro)

set(CMAKE_CXX_STANDARD 17)

add_executable(MiniMetro src/main.cpp
        src/display.cpp
        src/display.h
        src/utils.cpp
        src/utils.h
        src/navigation.cpp
        src/navigation.h
        src/station.h
        src/station.cpp
        src/linkStation.cpp
        src/linkStation.h
)