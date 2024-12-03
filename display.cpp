#include <iostream>
#include <fstream>
#include "utils.h"
#include "display.h"
#include "station.h"
#include "navigation.h"

using namespace std;

void test() {

}

void displayMenu() {
    clear_screen();
    cout << "Welcome Qingdao Mini Metro\n";
    cout << "1. Show existing lines\n";
    cout << "2. Navigation\n";
    cout << "3. Exit\n";
    int op;
    cin >> op;
    switch (op) {
        case 1:
            showLines();
            break;
        case 2:
            displayNavigation();
            break;
        case 3:
            exit(0);
        case 4:
            test();
        default:
            return;
    }
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
        while (n--) {
            string name;
            ifs >> name;
            cout << name << ' ';
        }
        cout << "\n\n";
    }
    getchar();
    getchar();
}

