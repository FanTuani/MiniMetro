#include "station.h"

Station::Station() {
    open = false;
    name = "";
}

Station::Station(int line, string &name, bool open) : open(open), name(name) {
    lines.push_back(line);
}

bool Station::operator<(const Station &oth) const {
    return false;
}

map<string, Station> stations;