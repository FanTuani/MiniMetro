#include "station.h"
#include "linkStation.h"

Station::Station() {
    open = end = false;
    name = "";
}

Station::Station(int line, string &name, bool end, bool open) : end(end), open(open), name(name) {
    lines.push_back(line);
}

bool Station::operator<(const Station &oth) const {
    return false;
}

int Station::getTimeNearBy(const Station &to) const {
    for (auto &sta: con) {
        if (sta.station.name == to.name) {
            return sta.time;
        }
    }
    return 0;
}

int Station::getTimeNearBy(const string &staName) const {
    if (stations.find(staName) == stations.end()) return 0;
    return getTimeNearBy(stations[staName]);
}

map<string, Station> stations;