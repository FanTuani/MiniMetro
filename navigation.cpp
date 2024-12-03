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
        for (int i = 1; i <= n; i++) {
            string name;
            ifs >> name;
            if (stations.find(name) != stations.end()) {
                stations[name].lines.push_back(line);
            } else {
                stations[name] = Station(line, name);
            }
            if (i != 1) {
                stations[name].con.push_back(*last);
                last->con.push_back(stations[name]);
            }
            last = &stations[name];
        }
    }
}

map<string, bool> vis;
vector<string> route;
vector<vector<string> > ans;

void dfs(const string &now, const string &des) {
    if (vis.find(now) != vis.end() and vis[now]) {
        return;
    }
    vis[now] = true;
    route.push_back(now);
    if (now == des) {
        ans.push_back(route);
    } else {
        for (const auto &to: stations[now].con) {
            dfs(to.name, des);
        }
    }
    vis[now] = false;
    route.pop_back();
}

bool cmp(const vector<string> &a, const vector<string> &b) {
    return a.size() < b.size();
}

void navigate(const string &st, const string &des) {
    getLinesInfo();

    ans.clear();
    dfs(st, des);
    sort(ans.begin(), ans.end(), cmp);
    cout << '\n';
    for (int i = 1; i <= ans.size(); i++) {
        auto &rou = ans[i - 1];
        cout << "route " << i << ", including " << rou.size() << " stations on this route:\n";
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
