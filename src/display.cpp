#include <iostream>
#include <fstream>
#include "utils.h"
#include "display.h"
#include "station.h"
#include "navigation.h"

void displayStationInfo();

using namespace std;

void test() {

}

void displayMenu() {
    clear_screen();
    cout << "Welcome Qingdao Mini Metro\n";
    cout << "1. Navigation\n";
    cout << "2. Show existing lines\n";
    cout << "3. Search station info\n";
    cout << "4. Exit\n";
    int op;
    cin >> op;
    switch (op) {
        case 1:
            displayNavigation();
            break;
        case 2:
            showLines();
            break;
        case 3:
            displayStationInfo();
            break;
        case 4:
            exit(0);
        case 5:
            test();
        default:
            return;
    }
}

void displayStationInfo() {
    clear_screen();
    cout << "station name:\n";
    string name;
    cin >> name;
    getLinesInfo();
    if (stations.find(name) == stations.end()) {
        cout << "NO SUCH STATION\n";
        getchar();
        getchar();
        return;
    }
    cout << '\n';
    Station &station = stations[name];
    cout << "Station name: " << name;
    for (int line: station.lines) {
        cout << '[' << line << "]";
    }
    cout << "\nStation state: " << (station.open ? "opening" : "closing");
    cout << "\nConnected station" << (station.con.size() > 1 ? "s: " : ": ");
    for (auto &[sta, w]: station.con) {
        cout << sta.name;
        for (int line: sta.lines) {
            cout << '[' << line << "]";
        }
        cout << ' ';
    }
    cout << '\n';
    getchar();
    getchar();
}

void displayNavigation() {
    clear_screen();
    string start, destination;
    cout << "Start station: ";
    cin >> start;
    cout << "Destination: ";
    cin >> destination;
    getLinesInfo();
    if (stations.find(start) == stations.end() or stations.find(destination) == stations.end()) {
        cout << "INVALID STATION NAME\n";
        getchar();
        getchar();
        return;
    }
    navigate(start, destination);
}

void showLines() {
    clear_screen();
    cout << "Lines:\n\n";
    ifstream ifs;
    ifs.open("lines.txt", ios::in);
    if (!ifs) {
        cerr << "CANNOT OPEN FILE lines.txt\n";
        return;
    }
    int line, n = 0;
    while (ifs >> line) {
        cout << "Line " << line << ": ";
        ifs >> n;
        for (int i = 1; i <= n; i++) {
            string name;
            ifs >> name;
            cout << name << ' ';
            if (i != n) {
                int w;
                ifs >> w;
            }
        }
        cout << "\n\n";
    }
    getchar();
    getchar();
}

