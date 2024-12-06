#include <iostream>
#include <set>
#include <vector>
#include "admin.h"
#include "station.h"
#include "utils.h"

using namespace std;

bool isLoggedIn = false;
string loginAcc;
const vector<pair<string, string> > preAcc = {{"wjr", "123"}};
set<pair<string, string>> accounts;

void displayAdminMenu() {
    logInMenu();
    if (!isLoggedIn) {
        return;
    }
    clear_screen();
    cout << "Admin management\n";
    cout << "1. Station management\n";
    cout << "2. Comments management\n";
    cout << "3. Return\n";
    char op;
    cin >> op;
    getchar();
    switch (op) {
        case '1':
            stationManagement();
            break;
        case '2':
            commentsManagement();
            break;
        case '3':
            return;
    }
}

void logInMenu() {
    clear_screen();
    cout << "Login menu\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. Logout\n";
    cout << "4. Return\n";
    char op;
    cin >> op;
    getchar();
    switch (op) {
        case '1':
            adminLogIn();
            break;
        case '2':
            adminRegister();
            break;
        case '3':
            clear_screen();
            if (!isLoggedIn) {
                cout << "You have not logged in!\n";
            } else {
                isLoggedIn = false;
                cout << "Log out successfully\n";
            }
            getchar();
            logInMenu();
            break;
        default:
            return;
    }
}

void adminLogIn() {
    for (auto &acc: preAcc) {
        accounts.insert(acc);
    }
    clear_screen();
    if (isLoggedIn) {
        cout << "You have logged in!\n";
        cout << "Account: " << loginAcc << '\n';
        getchar();
        return;
    }
    cout << "Log in your ADMIN account\n";
    string account, password;
    cout << "Account: ";
    cin >> account;
    cout << "Password: ";
    cin >> password;
    getchar();
    if (accounts.find({account, password}) != accounts.end()) {
        cout << "Login successfully!\n";
        loginAcc = account;
        isLoggedIn = true;
        getchar();
        return;
    }
    cout << "LOGIN FAILED, NO SUCH ACCOUNT\n";
    getchar();
}

void adminRegister() {
    clear_screen();

    string account, password, rep;
    cout << "New Account: ";
    cin >> account;
    cout << "Password: ";
    cin >> password;
    cout << "Password again: ";
    cin >> rep;
    getchar();
    if (password != rep) {
        cout << "REGISTER FAILED, DIFFERENT PASSWORD\n";
        getchar();
        return;
    }
    accounts.insert({account, password});
    cout << "Registered successfully\n";
    getchar();
}

void stationManagement() {
    clear_screen();

    cout << "Station name: ";
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
    cout << "\n----- Management menu -----\n";
    cout << "1. Change state\n";
    cout << "2. Return\n";
    char op;
    cin >> op;
    getchar();
    switch (op) {
        case '1':
            clear_screen();
            if (station.open) {
                cout << "Station closed\n";
            } else {
                cout << "Station opened\n";
            }
            station.open = !station.open;
            getchar();
            break;
        default:
            return;
    }
}

void commentsManagement() {
    clear_screen();

    cout << "Station name: ";
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
    cout << "\n----- Management menu -----\n";
    cout << "1. Delete comment\n";
    cout << "2. Return\n";
    char op;
    cin >> op;
    getchar();

    switch (op) {
        case '1':
            clear_screen();
            cout << "Select comment to be deleted\n";
            for (int i = 0; i < station.comments.size(); i++) {
                cout << i + 1 << ": - " << station.comments[i] << '\n';
            }
            int num;
            cin >> num;
            getchar();
            num--;
            if (num < 0 or num >= station.comments.size()) {
                cout << "INVALID OPERATION\n";
                getchar();
                return;
            }
            station.comments.erase(station.comments.begin() + num);
            cout << "Delete successfully\n";
            getchar();
            break;
        default:
            return;
    }
}