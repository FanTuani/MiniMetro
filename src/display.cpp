#include <iostream>
#include <fstream>
#include "utils.h"
#include "display.h"
#include "station.h"
#include "navigation.h"
#include "linkStation.h"
#include "admin.h"
#include "user.h"

using namespace std;

void displayMenu() {
    clear_screen();
    cout << "Welcome Qingdao Mini Metro\n";
    cout << "1. User menu\n";
    cout << "2. Admin menu\n";
    cout << "3. Exit\n";
    int op;
    cin >> op;
    switch (op) {
        case 1:
            displayUserMenu();
            break;
        case 2:
            displayAdminMenu();
            break;
        case 3:
            exit(0);
        default:
            return;
    }
}

void displayCommentInteraction() {
    clear_screen();

    cout << "Station name to comment: ";
    string name;
    cin >> name;
    getchar();
    if (stations.find(name) == stations.end()) {
        cout << "INVALID STATION NAME\n";
        getchar();
        return;
    }
    cout << "Enter your comment: \n- ";
    string comment;
    getline(cin, comment);
    if (comment.empty()) {
        cout << "COMMENT CANNOT BE VOID\n";
        getchar();
        return;
    }
    stations[name].comments.push_back(comment);
    cout << "Comment has been recorded, press ENTER to continue...\n";
    getchar();
}

void displayStationInfo() {
    clear_screen();
    cout << "Station name: ";
    string name;
    cin >> name;
    if (stations.find(name) == stations.end()) {
        cout << "NO SUCH STATION\n";
        getchar();
        getchar();
        return;
    }
    clear_screen();
    Station &station = stations[name];
    station.showInfo();
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

