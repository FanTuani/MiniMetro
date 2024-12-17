#include <iostream>
#include <set>
#include <vector>
#include "user.h"
#include "station.h"
#include "utils.h"
#include "display.h"

using namespace std;

bool isUserLoggedIn = false;
string UserLoginAcc;
const vector<pair<string, string> > preAcc = {{"wjr", "123"}};
set<pair<string, string>> accountsUser;

void displayUserMenu() {
    userLoginMenu();
    if (!isUserLoggedIn) {
        return;
    }
    clear_screen();
    cout << "User Management\n";
    cout << "1. Navigation\n";
    cout << "2. Show existing lines\n";
    cout << "3. Search station info\n";
    cout << "4. Add comments\n";
    cout << "5. Exit\n";
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
            displayCommentInteraction();
        break;
        default:
            return;
    }
}
void userLoginMenu() {
    clear_screen();
    cout << "User Login Menu\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. Logout\n";
    cout << "4. Return\n";
    char op;
    cin >> op;
    getchar();
    switch (op) {
        case '1':
            userLogin();
        break;
        case '2':
            userRegister();
        break;
        case '3':
            clear_screen();
        if (!isUserLoggedIn) {
            cout << "You have not logged in!\n";
        } else {
            isUserLoggedIn = false;
            cout << "Log out successfully\n";
        }
        getchar();
            userLoginMenu();
        break;
        default:
            return;
    }
}
void userLogin() {
    for (auto &acc: preAcc) {
        accountsUser.insert(acc);
    }
    clear_screen();
    if (isUserLoggedIn) {
        cout << "You have logged in!\n";
        cout << "Account: " << UserLoginAcc << '\n';
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
    if (accountsUser.find({account, password}) != accountsUser.end()) {
        cout << "Login successfully!\n";
        UserLoginAcc = account;
        isUserLoggedIn = true;
        getchar();
        return;
    }
    cout << "LOGIN FAILED, NO SUCH ACCOUNT\n";
    getchar();
}

void userRegister() {
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
    accountsUser.insert({account, password});
    cout << "Registered successfully\n";
    getchar();
}