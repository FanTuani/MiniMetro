#include "navigation.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>

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
            if (stations.find(name) != stations.end()) {
                stations[name].lines.push_back(line);
            } else {
                stations[name] = Station(line, name);
            }
            if (i != 1) {
                stations[name].con.emplace_back(*last, w);
                last->con.emplace_back(stations[name], w);
            }
            if (i != n) {
                ifs >> w;
            }
            last = &stations[name];
        }
    }
}

map<string, bool> vis;
vector<string> route;
vector<pair<vector<string>, int> > ans;

void dfs(const string &now, const string &des, int time = 0) {
    if (vis.find(now) != vis.end() and vis[now]) {
        return;
    }
    vis[now] = true;
    route.push_back(now);
    if (now == des) {
        ans.emplace_back(route, time);
    } else {
        for (const auto &[to, w]: stations[now].con) {
            dfs(to.name, des, time + w);
        }
    }
    vis[now] = false;
    route.pop_back();
}

bool cmp(const pair<vector<string>, int> &a, const pair<vector<string>, int> &b) {
    return a.second < b.second;
}

void navigate(const string &st, const string &des) {
    getLinesInfo();

    ans.clear();
    dfs(st, des);
    sort(ans.begin(), ans.end(), cmp);
    cout << '\n';
    for (int i = 1; i <= min((int) ans.size(), 3); i++) {
        auto &[rou, time] = ans[i - 1];
        cout << "route " << i << ", including " << rou.size() << " stations on this route, ";
        int hr = time / 60, mi = time % 60;
        if (mi <= 40) {
            mi *= 1.4;
        } else if (mi < 50) {
            mi *= 1.2;
        }
        if (hr > 0) {
            cout << "arrive within " << hr << "h " << mi << "min:\n";
        } else {
            cout << "arrive within " << mi << "min:\n";
        }
        for (int j = 0; j < rou.size(); j++) {
            if (j) {
                cout << " => ";
            }
            if (j - 2 >= 0 and stations[rou[j]].lines[0] != stations[rou[j - 2]].lines[0]
                and stations[rou[j - 1]].lines.size() > 1) {
                cout << "Transfer to Line [" << stations[rou[j]].lines[0] << "]\n";
            }
            cout << rou[j];
        }
        cout << "\n\n";
    }

    getchar();
    getchar();
}
