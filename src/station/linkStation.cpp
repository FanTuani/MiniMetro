#include "linkStation.h"

#include <utility>

LinkStation::LinkStation(Station &station) : station(station) {
    time = line = 0;
}

LinkStation::LinkStation(Station &station, int time, int line) :
        station(station), time(time), line(line) {}