#ifndef MINIMETRO_LINKSTATION_H
#define MINIMETRO_LINKSTATION_H

using namespace std;

class Station;

class LinkStation {
public:
    Station &station;
    int time, line;

    explicit LinkStation(Station &station);

    LinkStation(Station &station, int time, int line);
};

#endif //MINIMETRO_LINKSTATION_H
