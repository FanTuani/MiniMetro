#ifndef MINIMETRO_LINKSTATION_H
#define MINIMETRO_LINKSTATION_H

#include "station.h"

using namespace std;

class LinkStation {
public:
    Station station;
    int time, line;

    LinkStation();

    LinkStation(Station station, int time, int line);
};

#endif //MINIMETRO_LINKSTATION_H
