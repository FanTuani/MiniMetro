#include <iostream>
#include "station.h"
#include "linkStation.h"

using namespace std;

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

void Station::showInfo() const {
    cout << "Station name: " << name;
    for (int line: lines) {
        cout << '[' << line << "]";
    }
    cout << "\nStation state: " << (open ? "opening" : "closing");
    cout << "\nConnected station" << (con.size() > 1 ? "s: " : ": ");
    for (auto &[sta, w, l]: con) {
        cout << sta.name;
        for (int line: sta.lines) {
            cout << '[' << line << "]";
        }
        cout << ' ';
    }
    cout << '\n';
    cout << "Station comments: ";
    if (comments.empty()) {
        cout << "none";
    }
    cout << '\n';
    for (auto &comment: comments) {
        cout << "- " << comment << '\n';
    }
}

map<string, Station> stations;