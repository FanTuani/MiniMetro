#ifndef MINIMETRO_STATION_H
#define MINIMETRO_STATION_H

#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

class Station {
public:
    vector<int> lines;
    bool open;
    string name;
    vector<pair<Station, int> > con;

    Station();

    Station(int line, string &name, bool open = true);

    bool operator<(const Station &oth) const;
};

extern map<string, Station> stations;

#endif //MINIMETRO_STATION_H
