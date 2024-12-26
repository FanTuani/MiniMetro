#include "navigation.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>
#include "../station/linkStation.h"

using namespace std;

void getLinesInfo() {
    stations.clear();
    ifstream ifs;
    ifs.open("lines.txt", ios::in);
    if (!ifs) {
        return;
    }
    int line, n = 0;
    while (ifs >> line) {
        ifs >> n;
        Station *last;
        int w;
        for (int i = 1; i <= n; i++) {
            string name;
            ifs >> name;
            bool end = i == 1 or i == n;
            if (stations.find(name) != stations.end()) {
                stations[name].lines.push_back(line);
            } else {
                stations[name] = Station(line, name, end);
            }
            if (i != 1) {
                stations[name].con.emplace_back(stations[last->name], w, line);
                last->con.emplace_back(stations[name], w, line);
            }
            if (i != n) {
                ifs >> w;
            }
            last = &stations[name];
        }
    }
}

map<string, bool> vis;
vector<pair<string, int> > route;
vector<vector<pair<string, int> > > ans;

void dfs(const string &now, const string &des, int time = 0) {
    vis[now] = true;
    if (now == des) {
        ans.emplace_back(route);
    } else {
        for (const auto &to: stations[now].con) {
            if (vis.find(to.station.name) != vis.end() and vis[to.station.name]) {
                continue;
            }
            route.emplace_back(to.station.name, to.line);
            vis[to.station.name] = true;
            dfs(to.station.name, des, time + to.time);
            vis[to.station.name] = false;
            route.pop_back();
        }
    }
}

int calculateRouteTime(const vector<pair<string, int> > &rou) {
    int res = 0;
    for (int i = 0; i < rou.size() - 1; i++) {
        auto &[name, line] = rou[i];
        res += stations[name].getTimeNearBy(rou[i + 1].first);
    }
    return res + calculateRouteTransfer(rou) * 3;
}

int calculateRouteTransfer(const vector<pair<string, int> > &rou) {
    int res = 0;
    for (int i = 0; i < rou.size(); i++) {
        auto &[staName, line] = rou[i];
        if (i > 1 and line != rou[i - 1].second) {
            res++;
        }
    }
    return res;
}

bool timeCmp(const vector<pair<string, int> > &a, const vector<pair<string, int> > &b) {
    if (calculateRouteTime(a) == calculateRouteTime(b)) {
        if (calculateRouteTransfer(a) == calculateRouteTransfer(b)) {
            return a.size() < b.size();
        }
        return calculateRouteTransfer(a) < calculateRouteTransfer(b);
    }
    return calculateRouteTime(a) < calculateRouteTime(b);
}

bool transferCmp(const vector<pair<string, int> > &a, const vector<pair<string, int> > &b) {
    if (calculateRouteTransfer(a) == calculateRouteTransfer(b)) {
        if (calculateRouteTime(a) == calculateRouteTime(b)) {
            return a.size() < b.size();
        }
        return calculateRouteTime(a) < calculateRouteTime(b);
    }
    return calculateRouteTransfer(a) < calculateRouteTransfer(b);
}

bool stationCmp(const vector<pair<string, int> > &a, const vector<pair<string, int> > &b) {
    if (a.size() == b.size()) {
        if (calculateRouteTime(a) == calculateRouteTime(b)) {
            return calculateRouteTransfer(a) < calculateRouteTransfer(b);
        }
        return calculateRouteTime(a) < calculateRouteTime(b);
    }
    return a.size() < b.size();
}

void printRouteInfo(const vector<pair<string, int> > &rou) {
    cout << "including " << rou.size() << " stations and ";
    cout << calculateRouteTransfer(rou) << " transfers. ";
    int time = calculateRouteTime(rou);
    int hr = time / 60, mi = time % 60;
//    mi = (int) (mi * (1.0 + (60.0 - mi) / 2.0 / 60.0));
    if (hr > 0) {
        cout << "Travel time: " << hr << "h " << mi << "min:\n";
    } else {
        cout << "Travel time: " << mi << "min:\n";
    }
    cout << "- Line [" << rou[1].second << "]: ";
    int intervalTime = 0;
    for (int j = 0; j < rou.size(); j++) {
        auto &[staName, line] = rou[j];
        if (j) {
            cout << " => ";
            intervalTime += stations[staName].getTimeNearBy(rou[j - 1].first);
        }
        if (j > 1 and line != rou[j - 1].second) {
            cout << "Transfer to Line [" << line << "] (total time: " << intervalTime << "min)\n";
            cout << "- Line [" << line << "]: ";
            intervalTime = 0;
        }
        cout << staName;
    }
    cout << " (total time: " << intervalTime << "min)";
    cout << "\n\n";
}

void navigate(const string &st, const string &des) {
    ans.clear();
    route.clear();
    route.emplace_back(st, 0);
    dfs(st, des);

    cout << '\n';
    vector<vector<pair<string, int> > > out;
    bool outed[3] = {false, false, false};
    string tag[3] = {"[Fastest travel time] ", "[Fewest transfers] ", "[Fewest stations] "};

    sort(ans.begin(), ans.end(), timeCmp);
    out.push_back(ans[0]);
    sort(ans.begin(), ans.end(), transferCmp);
    out.push_back(ans[0]);
    sort(ans.begin(), ans.end(), stationCmp);
    out.push_back(ans[0]);

    int routeCnt = 1;
    for (int i = 0; i < 3; i++) {
        if (outed[i]) continue;
        cout << "Route " << routeCnt++ << ": ";
        cout << tag[i];
        for (int j = i + 1; j < 3; j++) {
            if (out[j] == out[i]) {
                cout << tag[j];
                outed[j] = true;
            }
        }
        cout << "\n";
        printRouteInfo(out[i]);
    }

    getchar();
    getchar();
}
