#include "linkStation.h"

#include <utility>

LinkStation::LinkStation() {
    time = line = 0;
}

LinkStation::LinkStation(Station station, int time, int line) :
        station(std::move(station)), time(time), line(line) {}