cmake_minimum_required(VERSION 3.27)
project(MiniMetro)

set(CMAKE_CXX_STANDARD 17)

add_executable(MiniMetro src/main.cpp
        src/core/display.cpp
        src/core/display.h
        src/utils.cpp
        src/utils.h
        src/core/navigation.cpp
        src/core/navigation.h
        src/station/station.h
        src/station/station.cpp
        src/station/linkStation.cpp
        src/station/linkStation.h
        src/userInteraction/admin.cpp
        src/userInteraction/admin.h
        src/userInteraction/user.h
        src/userInteraction/user.cpp
)