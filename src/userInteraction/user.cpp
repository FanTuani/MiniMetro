#include <iostream>
#include <map>
#include <vector>
#include "user.h"
#include "../station/station.h"
#include "../utils.h"
#include "../core/display.h"
#include "set"

using namespace std;

bool isUserLoggedIn = false;
string userLoginAcc;
const map<string, string> preAcc = {{"wjr", "123"}};

std::map<std::string, User> accountsUser;



void (*muteUserPtr)(const std::string&) = muteUser;
void (*unmuteUserPtr)(const std::string&) = unmuteUser;

void displayUserMenu() {
    userLoginMenu();
    if (!isUserLoggedIn) {
        return;
    }
    tag:
    clear_screen();
    cout << "User Menu\n";
    cout << "1. Navigation\n";
    cout << "2. Show existing lines\n";
    cout << "3. Search station info\n";
    cout << "4. Comment\n";
    cout << "5. Change password\n";
    cout << "6. Logout\n";
    cout << "7. return\n";
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
            commentMenu();
            break;
        case '5':
            userChange();
        break;
        case '6':
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
    goto tag;
}

void userLoginMenu() {
    if (isUserLoggedIn)
        return;
    clear_screen();
    cout << "User Login Menu\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. return\n";
    cout << "4. Exit\n";
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
        case '4':
            exit(0);
        default:
            return;
    }
}

void userLogin() {
    clear_screen();
    if (isUserLoggedIn) {
        cout << "You have logged in!\n";
        cout << "Account: " << userLoginAcc << '\n';
        getchar();
        return;
    }
    cout << "Log in your account\n";
    string account, password;
    cout << "Account: ";
    cin >> account;
    cout << "Password: ";
    cin >> password;
    getchar();
    if (accountsUser.find(account) != accountsUser.end() && accountsUser[account].password == password) {
        cout << "Login successfully!\n";
        userLoginAcc = account;
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
    if (password != rep || accountsUser.find(account) != accountsUser.end()) {
        cout << "REGISTER FAILED, DIFFERENT PASSWORD OR ACCOUNT ALREADY EXISTS\n";
        getchar();
        return;
    }
    accountsUser[account].password = password;
    cout << "Registered successfully\n";
    isUserLoggedIn = true;
    userLoginAcc = account;
    getchar();
}

void userChange() {
    clear_screen();
    string account, currentPassword, newpassword, rep;
    cout << "Enter your account: ";
    cin >> account;
    cout << "Enter your current password: ";
    cin >> currentPassword;
    cout << "Enter your new password: ";
    cin >> newpassword;
    cout << "Enter your new password again: ";
    cin >> rep;
    getchar();
    if (newpassword != rep) {
        cout << "PASSWORD CHANGE FAILED, DIFFERENT PASSWORDS ENTERED\n";
        getchar();
        return;
    }
    // 检查当前密码是否正确
    if (accountsUser.find(account) != accountsUser.end() && accountsUser[account].password == currentPassword) {
        // 更新密码
        accountsUser[account].password = newpassword;
        cout << "Password change successfully\n";
    } else {
        cout << "PASSWORD CHANGE FAILED, INCORRECT CURRENT PASSWORD\n";
    }
    getchar();
}

void commentMenu() {
    clear_screen();

    if (accountsUser[userLoginAcc].isMuted) {
        cout << "You have been muted and cannot use comment features.\n";
        getchar();
        getchar();
        return;
    }

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
    cout << "1. Add comment\n";
    cout << "2. Delete comment\n";
    cout << "3. Return\n";
    char op;
    cin >> op;
    getchar();

    switch (op) {
        case '1':
            displayCommentInteraction(name, 0);
            break;
        case '2':
            deleteComment();
            break;
        case '3':
            return;
    }
}

void muteUser(const std::string& username) {
    auto it = accountsUser.find(username);
    if (it != accountsUser.end()) {
        it->second.isMuted = true;
        std::cout << "User " << username << " has been muted.\n";
    } else {
        std::cout << "User not found.\n";
    }
    getchar();
    getchar();
}

void unmuteUser(const std::string& username) {
    auto it = accountsUser.find(username);
    if (it != accountsUser.end()) {
        it->second.isMuted = false;
        std::cout << "User " << username << " has been unmuted.\n";
    } else {
        std::cout << "User not found.\n";
    }
    getchar();
    getchar();
}