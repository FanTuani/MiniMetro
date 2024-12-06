#include <iostream>
#include <set>
#include <vector>
#include "admin.h"
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
    cout << "1. Return\n";
    char op;
    cin >> op;
    getchar();
    switch (op) {
        case '1':
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
