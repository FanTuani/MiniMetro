#include "linkStation.h"

LinkStation::LinkStation() {
    time = line = 0;
}

LinkStation::LinkStation(const Station &station, int time, int line) : station(station), time(time), line(line) {}