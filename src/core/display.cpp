#include <iostream>
#include <fstream>
#include "../utils.h"
#include "display.h"
#include "../station/station.h"
#include "navigation.h"
#include "../userInteraction/admin.h"
#include "../userInteraction/user.h"

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

void displayCommentInteraction(string &name,int flag) {
    clear_screen();

    if (stations.find(name) == stations.end()) {
        cout << "INVALID STATION NAME\n";
        getchar();
        return;
    }
    cout << "Enter your comment: \n- ";
    string comment,Admin;
    if (flag)
    Admin = "Admin: ";
    getline(cin, comment);
    if (comment.empty()) {
        cout << "COMMENT CANNOT BE VOID\n";
        getchar();
        return;
    }
    comment  = Admin + comment;
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

void deleteComment() {
    clear_screen();

    cout << "Station name to delete a comment: ";
    string name;
    cin >> name;
    getchar();
    if (stations.find(name) == stations.end()) {
        cout << "INVALID STATION NAME\n";
        getchar();
        return;
    }
    Station &station = stations[name];
    clear_screen();
    station.showInfo();
    cout << "\n----- Select Comment to Delete -----\n";
    cout << "Comment selection: ";
    vector<string> comments = station.comments;
    int selection = 0;
    for (const auto &comment: comments) {
        cout << selection + 1 << ": " << comment << '\n';
        selection++;
    }
    cout << "Enter the number of the comment to delete: ";
    int choice;
    cin >> choice;
    getchar();
    if (choice < 1 || choice > static_cast<int>(comments.size())) {
        cout << "INVALID COMMENT SELECTION\n";
        return;
    }
    choice--; // Adjust for 0-based indexing
    station.comments.erase(station.comments.begin() + choice);
    cout << "Comment deleted successfully.\n";
    getchar();
}
