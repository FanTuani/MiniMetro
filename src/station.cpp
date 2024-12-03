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

map<string, Station> stations;