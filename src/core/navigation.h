#ifndef MINIMETRO_NAVIGATION_H
#define MINIMETRO_NAVIGATION_H

#include "../station/station.h"

void getLinesInfo();

void navigate(const string &st, const string &des);

int calculateRouteTime(const vector<pair<string, int> > &rou);

int calculateRouteTransfer(const vector<pair<string, int> > &rou);

bool timeCmp(const vector<pair<string, int> > &a, const vector<pair<string, int> > &b);

bool transferCmp(const vector<pair<string, int> > &a, const vector<pair<string, int> > &b);

bool stationCmp(const vector<pair<string, int> > &a, const vector<pair<string, int> > &b);

void printRouteInfo(const vector<pair<string, int> > &rou);

#endif //MINIMETRO_NAVIGATION_H
