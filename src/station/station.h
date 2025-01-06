#ifndef MINIMETRO_STATION_H
#define MINIMETRO_STATION_H

#include <string>
#include <vector>
#include <map>
#include "linkStation.h"

using namespace std;

class Station {
public:
    vector<int> lines;
    bool open, end;
    string name;
    vector<LinkStation> con;
    vector<string> comments;

    Station();

    Station(int line, string &name, bool end = false, bool open = true);

    bool operator<(const Station &oth) const;

    [[nodiscard]] int getTimeNearBy(const Station &to) const;

    [[nodiscard]] int getTimeNearBy(const string &staName) const;

    void showInfo() const;
};

extern map<string, Station> stations;

#endif //MINIMETRO_STATION_H
